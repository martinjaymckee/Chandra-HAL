# Introduction
This document provides just a very rough list of documentation that should be completed for the Chandra-HAL library.  As tasks are completed, the hope is to
add further sub-projects to the list so that this does not need to remain at an extremely high level.  Overall, however, this is not documentation in itself and,
rather, a place to drop ideas so they don't get forgotten.

# Tasks
1. Figure out an approach to create API documentation -- possibly Doxygen.  Begin with highest level drivers, etc.
2. Document porting steps for each library component in a porting document.  Specifically, document what is directly hardware dependent.  This can simply be a table.
3. Document Chandra library architecture:
    1. Core
        - Meta
        - Datatypes
        - Collections
        - Utilities
        - Units (Generated)
        - Math
    2. HAL (hardware dependent)
        - IO
        - Comm
        - Timing
        - Events (Some of this is likely to be HW dependent, but not all)
        - Drivers (Does this belong here, or should this go to a higher level that is not HW dependent?)
    3. Control
        - PID
        - Kalman
        - FIR
        - IIR
    4. Aero
        - Rocket Events
        - Airplane Events
        - Inertial Navigation (Does this belong there???)
        - Aerodynamics
    5. AI
    6. ???
4. Create a "cookbook" of code snippets for all libraries at least at the HAL level and higher.
