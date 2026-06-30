// FUNC_NAME: CoreEngine::runMainLoop

void CoreEngine::runMainLoop(void)
{
    // Static initialization guard: ensure one-time init
    if ((g_initialized & 1) == 0) {
        g_initialized |= 1;
        CoreEngine::initSubsystem();   // FUN_00484b10 - likely initializes engine subsystems
        _atexit((_func_4879*)cleanupFunction);  // register cleanup at exit
    }

    do {
        // Check the type field (+0x00) of the current task/event object
        if (this->type == 1) {
            // Type 1: wait until condition is met (field[4] == field[3])
            bool equal = (this->compareValue == this->expectedValue); // +0x10 compared with +0x0C
            if (equal) {
                return;
            }
        }
        else if (this->type == 2) {
            // Type 2: execute a callback function pointed by field[4] (+0x10)
            int result = (*(code*)this->callback)(this->callbackArg, 0, 0); // +0x1C is arg
            if (result == 0) {
                return;
            }
        }

        // Fetch current time (likely high-/low-part) and compute delta
        uint timeLow, timeHigh, timeMid, timeOther;
        int timeRetrieved = FUN_0056ad40(&timeLow, &timeHigh, &timeMid, &timeOther);
        if (timeRetrieved != 0) {
            g_gameTimeLow = timeLow;
            g_gameTimeHigh = timeHigh;
            g_gameTimeMid = timeMid;
            g_gameTimeOther = timeOther;
            g_timeDelta = FUN_0056acb0();  // get time delta since last frame
        }

        // Yield or update subsystems
        CoreEngine::update();  // FUN_00483ca0
    } while (true);
}