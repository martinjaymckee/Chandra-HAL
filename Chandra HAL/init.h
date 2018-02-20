#ifndef CHANDRA_INIT_H
#define CHANDRA_INIT_H

#include <chip.h>

namespace chandra
{
class Chandra
{
    public:
        // TODO: THIS SHOULD PROBABLY HAVE THE OPTION OF
        static void init() {
            // TODO: THIS IS *ONLY* VALID FOR AN LPC824 RUNNING AT 60MHZ ON THE MAIN CLOCK
            SystemCoreClockUpdate();
            LPC_SYSCON->SYSAHBCLKDIV = 2; // THIS IS UNNECESSARY FOR MAIN CLOCK <= 30MHZ
            chandra::chrono::timestamp_clock::init();
        }
};
} /*namespace chandra*/

#endif // CHANDRA_INIT_H

