#Testing
The bulk of general Chandra-HAL testing is done on the PC using the Catch2 test framework.  Meanwhile, the tests are built using CMake.  This allows the tests to be run cross platform.  The core Chandra libraries - including the matrix libraries, data structures, and units -- are able to be tested with minimal assistance.  Hardware related libraries such as the drivers libraries, communication interfaces (SPI, I2C, and USART), system timer, gpio, etc. are not testable on the PC and are not, therefore, covered by the general tests.

* Matrix Operations
* Matrix/Vector Operations
* Dimensions / Dimensional Analysis
* Units / Unit conversions
* Quantities
* Quantities in Matricies
