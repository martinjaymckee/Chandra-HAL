# Chandra-HAL
A C++14, header-only library, designed for use in microcontroller projects targeting robotics, signal-processing, control systems and other related - deeply embedded - systems.  Chandra, in the wider sense, is viewed as being an all inclusive set of libraries
which will provide support for a wide range of projects with hardware-rich, real-time, requirements.  Chandra HAL, specifically, is the component which will act as the core functionality and the hardware abstraction layer (HAL).  Other Chandra components will
then layer on top of the HAL as required.

Currently, Chandra HAL contains some basic hardware interface functionality: ADC, GPIO, SPI, Accelerometer/IMU, etc.  Drivers have been written for a few specific devices, however, there is currently a need to add *many* more drivers to take advantage of the 
available interface design.  In addition to the direct hardware connection, Chandra HAL provides several support options which are especially useful.  First, there is a units/quantities system which does efficient conversion between units and error checking (assignment
and arithmetic of quantities is checked at compile time).  The design of sensor drivers is such that they return quantities with attached units rather than bare numbers.  Of course, it is possible to extract a unitless number with no run-time overhead (and reduced 
safety) but the library supports the programmer's ability to write intrensically correct code whenever possible.  A second non-hardware based feature that Chandra HAL provides is a small set of linear algebra operations.  Matricies for storage and arithmetic are
supported.  The matricies may be based on any arithmetic datatype, including quantities.  Quaternions, also, are provided.

Chandra HAL is very much a work in progress.  At some point, a road map may end up in this spot.  As it stands, however, the library is serving its purpose quite well in a couple of projects which I will get up onto GitHub when they have reached beyond the point
of being fragile test devices.  Much to do! 
