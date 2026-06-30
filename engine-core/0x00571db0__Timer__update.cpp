// FUNC_NAME: Timer::update
void Timer::update()
{
    int *thisPtr = reinterpret_cast<int*>(this);
    if (thisPtr[0x44 / 4] != 0) { // +0x44: timerState (int)
        if (thisPtr[0x44 / 4] < 1) { // negative state: countdown mode
            // Compute a value: threshold - (counter * speed)
            float temp = DAT_00e2b1a4 - (float)thisPtr[0x45 / 4] * _DAT_00e446b8;
            if (temp > 0.0f) {
                double result = (double)(temp * DAT_00e2a850);
                FUN_00b99fcb(); // some effect (audio?)
                temp = (float)result;
            }
            if (temp <= 0.0f) {
                // Timer expired: reset state and call callback
                void (**vtable)() = *(void (***)())(this);
                thisPtr[0x44 / 4] = 0;
                *(uint8_t*)((int)this + 0x121) = 0; // +0x121: some flag
                (*vtable[1])(); // virtual callback at vtable+4
            }
        } else { // positive state: progress mode
            if ((float)thisPtr[0x46 / 4] == 0.0f) { // +0x46: max value
                thisPtr[0x44 / 4] = 0;
                return;
            }
            float ratio = (float)thisPtr[0x45 / 4] / (float)thisPtr[0x46 / 4];
            if (ratio < DAT_00e2b1a4) {
                double result = (double)(ratio * DAT_00e2a850);
                FUN_00b99fcb();
                ratio = (float)result;
            }
            if (DAT_00e2b1a4 <= ratio) {
                thisPtr[0x44 / 4] = 0;
                return;
            }
        }
    }
}