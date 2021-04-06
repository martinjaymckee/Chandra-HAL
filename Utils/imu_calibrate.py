#
# Python Standard Library Imports
#
import datetime
import math
import random
import sys


#
# Third-Party Library Imports
#
#   Dependencies:
#       matplotlib
#       numpy
#       PySerial
#       PyQt5
#       seaborn
#
import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.backends.backend_qt5agg as mpl_backends  #import FigureCanvasQTAgg
import matplotlib.figure
import numpy as np
from PyQt5 import QtCore
from PyQt5 import QtGui
from PyQt5 import QtWidgets
import seaborn as sns
import serial
import serial.tools
import serial.tools.list_ports


#
# State Types
#
class IMUData:
    def __init__(self, ts=[], accelerometer=[], gyroscope=[], magnetometer=[]):
        self.__ts = ts
        self.__accelerometer = accelerometer
        self.__gyroscope = gyroscope
        self.__magnetometer = magnetometer

    @property
    def ts(self):
        return self.__ts

    @property
    def accelerometer(self):
        return self.__accelerometer

    @property
    def gyroscope(self):
        return self.__gyroscope

    @property
    def magnetometer(self):
        return self.__magnetometer

    def enqueue(self, t, a, g, m):
        assert (len(self.__ts) > 0) and (t > self.__ts[-1]), 'Next time ({}) is less than the last ({})'.format(t, self.__ts[-1])
        self.__ts.append(t)
        self.__accelerometer.append(a)
        self.__gyroscope.append(g)
        self.__magnetometer.append(m)

    def dataInLastT(self, t):
        ts = []
        accelerometer = []
        gyroscope = []
        magnetometer = []
        if len(self.__ts) > 0:
            dts = self.__ts[-1] - np.array(self.__ts)
            N = len(self.__ts)
            print(dts)
            for idx, dt in enumerate(reversed(dts)):
                if dt > t:
                    N = idx
                    break
            ts = self.__ts[-N:]
            accelerometer = self.__accelerometer[-N:]
            gyroscope = self.__gyroscope[-N:]
            magnetometer = self.__magnetometer[-N:]
        return IMUData(ts, accelerometer, gyroscope, magnetometer)
#
# Compound Widgets
#
class VectorDisplay(QtWidgets.QGroupBox):
    vectorChanged = QtCore.pyqtSignal(np.ndarray)

    def __init__(self, title, fmt='{:0.4f}', units=None, parent=None):
        super().__init__(title, parent=parent)
        self.__fmt = fmt
        self.__units = units
        layout = QtWidgets.QGridLayout()
        self.__values = []
        for row, name in enumerate(('x', 'y', 'z')):
            layout.addWidget(QtWidgets.QLabel(name), row, 0)
            value_edit = QtWidgets.QLineEdit(self.__fmt.format(0))
            value_edit.setStyleSheet("QLineEdit:read-only{background: palette(Window);}")
            value_edit.textChanged.connect(self.__send_vector_signal)
            layout.addWidget(value_edit, row, 1)
            self.__values.append(value_edit)
            if units is not None:
                layout.addWidget(QtWidgets.QLabel(units), row, 2)
        self.setLayout(layout)
        self.setVisible(True)
        self.statistics(means=[0, 0, 0], sds=[1, 1, 2])

    @property
    def data(self):
        try:
            x = float(self.__values[0].text())
            y = float(self.__values[1].text())
            z = float(self.__values[2].text())
        except Exception as e:
            raise e
        return np.array([x, y, z])

    @data.setter
    def data(self, _val):
        try:
            _val = [float(v) for v in _val]
            self.__values[0].setText(self.__fmt.format(_val[0]))
            self.__values[1].setText(self.__fmt.format(_val[1]))
            self.__values[2].setText(self.__fmt.format(_val[2]))
            return _val
        except Exception as e:
            raise e
        return None

    def setReadOnly(self, editable):
        for v in self.__values:
            v.setReadOnly(editable)
            # v.setEnabled(editable)

    def statistics(self, means=None, sds=None):
        try:
            for row in range(3):
                tooltip = ''
                if means is not None:
                    tooltip += 'mean = {}'.format(self.__fmt.format(means[row]))
                    tooltip += '' if self.__units is None else ' ' + self.__units
                if sds is not None:
                    if len(tooltip) > 0:
                        tooltip += '\n'
                    tooltip += 's.d. = {}'.format(self.__fmt.format(sds[row]))
                    tooltip += '' if self.__units is None else ' ' + self.__units
                self.__values[row].setToolTip(tooltip)
        except Exception as e:
            raise e

    def __send_vector_signal(self, _):
        self.vectorChanged.emit(self.data)


class PlotCanvas(mpl_backends.FigureCanvasQTAgg):
    def __init__(self, subplots=1, parent=None, width=5, height=4, dpi=100):
        self.__fig = mpl.figure.Figure(figsize=(width, height), dpi=dpi)
        self.__axs = []
        # TODO: ADD ABILITY TO SHARE THE X AXIS
        for idx in range(subplots):
            ax = self.__fig.add_subplot(subplots, 1, int(idx+1))
            self.__axs.append(ax)
        self.__fig.tight_layout()
        super(PlotCanvas, self).__init__(self.__fig)

    def plot(self, xs, ys):
        yss = []
        for _ in range(len(self.__axs)):
            yss.append(list())
        for y in ys:
            for idx, yi in enumerate(y):
                yss[idx].append(yi)
        for idx in range(len(yss)):
            self.__axs[idx].plot(xs, yss[idx])


class ActivityButton(QtWidgets.QPushButton):
    def __init__(self, inactive_title, active_title, parent=None):
        super().__init__(inactive_title, parent=parent)
        self.__is_active = False
        self.__inactive_title = inactive_title
        self.__active_title = active_title
        self.activate(False)

    @property
    def active(self): return self.__is_active

    @QtCore.pyqtSlot()
    def activate(self, _activate):
        self.__is_active = _activate
        if self.__is_active:
            self.setText(self.__active_title)
            self.setStyleSheet("QPushButton{background: green;}")
        else:
            self.setText(self.__inactive_title)
            self.setStyleSheet("QPushButton{background: red;}")


#
# IMU Calibration Sources
#
class VirtualIMUSource:
    def __init__(self):
        self.__fs = 100
        self.__t_last = None
        self.__g = 9.80665
        self.__m_max = 5.5
        self.__a_sd = np.array([1e-3, 1e-3, 1e-3])
        self.__g_sd = np.array([1e-3, 1e-3, 1e-3])
        self.__m_sd = np.array([1e-3, 1e-3, 1e-3])
        self.__a_b = np.array([0, 0, 0])
        self.__g_b = np.array([0, 0, 0])
        self.__m_b = np.array([0, 0, 0])
        self.__config = QtWidgets.QLabel("<h1>Config</h1>")

    @property
    def name(self):
        return 'Virtual'

    @property
    def description(self):
        return 'A simulated IMU source which provides acceleration, gyroscope and magnetometer.  The output is based on the reference direction and noise/offset configuration.'

    @property
    def configWidget(self):
        return self.__config

    def connect(self):
        return True, 'Ok'

    def disconnect(self):
        return True, 'Ok'

    def referenceOrientation(self, q):
        return True

    def updateData(self, data):
        t = datetime.datetime.now()
        # Append new data here....
        return True


class SerialIMUSource:
    def __init__(self, data):
        self.__data = data
        self.__port = data.device
        self.__config = QtWidgets.QWidget()

    def __str__(self, prefix=''):
        return '{}Device: {}\n{}Product: {}\n{}Location: {}\n'.format(prefix, self.__data.device, prefix, self.__data.description, prefix, self.__data.location)

    @property
    def name(self):
        return 'Serial Source'

    @property
    def description(self):
        return 'UNDEFINED'

    @property
    def configWidget(self):
        return self.__config

    def connect(self):
        return False, 'Serial source connection is unimplemented'

    def disconnect(self):
        return True, 'Ok'

    def referenceOrientation(self, q):
        return False

    def updateData(self, data):
        # Append new data here....
        return True

#
# UI Components and Definition
#
class CalibrationControlPanel(QtWidgets.QGroupBox):
    def __init__(self, parent=None):
        super().__init__('Calibration Control', parent=parent)
        layout = QtWidgets.QVBoxLayout()
        self.__source_group = QtWidgets.QGroupBox('Data Source')
        self.__source_layout = QtWidgets.QGridLayout()
        self.__sources = QtWidgets.QComboBox()
        self.__sources.currentIndexChanged.connect(self.__set_active_source)
        self.__source_update_button = QtWidgets.QPushButton('Update')
        self.__source_update_button.clicked.connect(self.__update_sources)
        self.__source_layout.addWidget(QtWidgets.QLabel('Source'), 0, 0)
        self.__source_layout.addWidget(self.__sources, 0, 1)
        self.__source_layout.addWidget(self.__source_update_button, 0, 2)
        self.__source_connect_button = ActivityButton('Disconnected (Click to Connect)', 'Connected (Click to Disconnect)')
        self.__source_connect_button.clicked.connect(self.__process_connect_button)
        self.__source_layout.addWidget(self.__source_connect_button, 1, 0, 1, 3)
        self.__source_layout.addWidget(QtWidgets.QWidget(), 2, 0, 1, 3)
        self.__source_layout.addWidget(QtWidgets.QLabel('<h1>Source Description</h1>'), 3, 0, 1, 3)
        self.__source_group.setLayout(self.__source_layout)
        layout.addWidget(self.__source_group)
        self.__calibration_group = QtWidgets.QGroupBox('Calibration')
        self.__calibration_button_group = QtWidgets.QButtonGroup()
        calibration_layout = QtWidgets.QVBoxLayout()
        self.__calibrate_orthagonal_cubic = QtWidgets.QRadioButton('Orthagonal Cubic')
        self.__calibrate_orthagonal_cubic.setToolTip('Six orientations on the faces of a cube')
        self.__calibrate_orthagonal_cubic.setChecked(True)
        self.__calibration_button_group.addButton(self.__calibrate_orthagonal_cubic)
        calibration_layout.addWidget(self.__calibrate_orthagonal_cubic)
        self.__calibrate_octohedral_cubic = QtWidgets.QRadioButton('Octohedral Cubic')
        self.__calibrate_octohedral_cubic.setToolTip('Eight orientations on the corners of a cube')
        self.__calibration_button_group.addButton(self.__calibrate_octohedral_cubic)
        calibration_layout.addWidget(self.__calibrate_octohedral_cubic)
        self.__calibration_group.setLayout(calibration_layout)
        layout.addWidget(self.__calibration_group)
        layout.addStretch(2)
        self.setLayout(layout)
        self.__active_source = None
        self.__virtual_source = VirtualIMUSource()
        self.__update_sources()

    @property
    def source(self):
        return self.__active_source

    def __update_sources(self):
        selected_source = self.__sources.currentText()
        self.__sources.clear()
        for port in serial.tools.list_ports.comports():
            self.__sources.addItem(port.name, port)
        self.__sources.addItem('* Virtual', None)
        idx = self.__sources.findText(selected_source)
        if not idx == -1:
            self.__sources.setCurrentIndex(idx)
        else:
            idx = self.__sources.count() - 1
            self.__sources.setCurrentIndex(idx)
            self.__set_active_source(idx)

    def __set_active_source(self, idx):
        if self.__active_source is not None:
            self.__active_source.disconnect()
            self.__source_connect_button.activate(False)
        if idx == (self.__sources.count() - 1):
            self.__active_source = self.__virtual_source
        else:
            self.__active_source = SerialIMUSource(self.__sources.currentData())
        self.__source_layout.addWidget(self.__active_source.configWidget, 2, 0, 1, 3)
        self.__connect_to_active_source()

    def __connect_to_active_source(self):
        connect_success, msg = self.__active_source.connect()
        self.__source_connect_button.activate(connect_success)
        if not connect_success:
            dialog = QtWidgets.QMessageBox(self)
            dialog.setIcon(QtWidgets.QMessageBox.Information)
            dialog.setWindowTitle("Connection Error")
            dialog.setText(msg)
            dialog.setDetailedText('Source Details:\n{}'.format(self.__active_source.__str__('  ')))
            dialog.exec_()

    def __process_connect_button(self):
        if self.__source_connect_button.active:
            success, msg = self.__active_source.disconnect()
            self.__source_connect_button.activate(not success)
        else:
            self.__connect_to_active_source()


class CalibrationProcessTab(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super().__init__(parent=parent)
        layout = QtWidgets.QVBoxLayout()
        layout.addWidget(QtWidgets.QLabel('<h1>Do Calibration Stuff!</h1>'))
        self.setLayout(layout)


class RawIMUValueTab(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super().__init__(parent=parent)
        vector_layout = QtWidgets.QHBoxLayout()
        self.__accelerometer = VectorDisplay('Accelerometer', units='m-s<sup>-2</sup>')
        self.__accelerometer.setReadOnly(True)
        self.__gyroscope = VectorDisplay('Gyroscope', units='rad-s<sup>-1</sup>')
        self.__gyroscope.setReadOnly(True)
        self.__magnetometer = VectorDisplay('Magnetometer', units='gauss')
        self.__magnetometer.setReadOnly(True)
        vector_layout.addWidget(self.__accelerometer)
        vector_layout.addWidget(self.__gyroscope)
        vector_layout.addWidget(self.__magnetometer)
        layout = QtWidgets.QVBoxLayout()
        layout.addLayout(vector_layout)
        self.__plot_window = PlotCanvas(subplots=3)
        layout.addWidget(self.__plot_window)
        layout.setStretchFactor(self.__plot_window, 1)
        self.__plot_control = QtWidgets.QGroupBox('Plot Control')
        plot_control_layout = QtWidgets.QGridLayout()
        self.__plot_accelerometer = QtWidgets.QRadioButton('Accelerometer')
        self.__plot_accelerometer.setChecked(True)
        self.__plot_gyroscope = QtWidgets.QRadioButton('Gyroscope')
        self.__plot_magnetometer = QtWidgets.QRadioButton('Magnetometer')
        plot_control_layout.addWidget(self.__plot_accelerometer, 0, 0)
        plot_control_layout.addWidget(self.__plot_gyroscope, 0, 1)
        plot_control_layout.addWidget(self.__plot_magnetometer, 0, 2)
        self.__plot_history = QtWidgets.QDoubleSpinBox()
        self.__plot_history.setMinimum(0.5)
        self.__plot_history.setMaximum(30.0)
        self.__plot_history.setSingleStep(0.25)
        self.__plot_history.setValue(5.0)
        plot_control_layout.addWidget(QtWidgets.QLabel('Plot History'), 1, 0)
        plot_control_layout.addWidget(self.__plot_history, 1, 1)
        self.__plot_control.setLayout(plot_control_layout)
        layout.addWidget(self.__plot_control)
        self.setLayout(layout)

        # HACK: FAKE DATA TO PLAY WITH
        def dummyRandomVector(v, sd, bias=[0, 0, 0]):
            new_v = []
            for vi, bi in zip(v, bias):
                new_v.append(random.gauss(vi+bi, sd))
            return np.array(new_v)
        ts = list(np.linspace(0, 10, 1000))
        accelerometer = []
        gyroscope = []
        magnetometer = []
        sd_a = 7e-2
        b_a = dummyRandomVector([0, 0, 0], 1e-3)
        sd_g = 2e-3
        b_g = dummyRandomVector([0, 0, 0], 5e-2)
        sd_m = 1e-2
        b_m = dummyRandomVector([0, 0, 0], 1e-1)
        for t in ts:
            accelerometer.append(dummyRandomVector([0, 0, 9.80665], sd_a, b_a))
            gyroscope.append(dummyRandomVector([0, 0, 0], sd_g, b_g))
            magnetometer.append(dummyRandomVector([1.0, -0.15, 0.1], sd_m, b_m))
        self.__imu_data = IMUData(ts, accelerometer, gyroscope, magnetometer)

        data = self.__imu_data.dataInLastT(2.5)
        self.__plot_window.plot(np.array(data.ts) - data.ts[-1], data.accelerometer)


class CalibrationUI(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super().__init__(parent=parent)
        layout = QtWidgets.QHBoxLayout()
        self.__control_panel = CalibrationControlPanel()
        self.__tab_view = QtWidgets.QTabWidget()
        self.__tab_view.addTab(RawIMUValueTab(), 'Raw Vectors')
        self.__tab_view.addTab(CalibrationProcessTab(), 'Calibration')
        layout.addWidget(self.__control_panel)
        layout.addWidget(self.__tab_view)
        self.setLayout(layout)


def main():
    # 2. Create an instance of QApplication
    app = QtWidgets.QApplication(sys.argv)

    # 3. Create an instance of your application's GUI
    window = QtWidgets.QMainWindow()
    window.setWindowTitle('IMU Calibration')
    window.setCentralWidget(CalibrationUI())

    # 4. Show your application's GUI
    window.show()
    # window.showMaximized()

    return app.exec_()


if __name__ == '__main__':
    success = main()
    # 5. Run your application's event loop (or main loop)
    sys.exit(success)
