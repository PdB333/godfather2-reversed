// FUNC_NAME: Presentation::updateSkipTimer
void __thiscall Presentation::updateSkipTimer(Presentation* this) {
    int timer;
    int globalStatePtr;
    float elapsedTime;

    if (this->m_skipTimer != 0) {
        timer = this->m_skipTimer - 1;
        this->m_skipTimer = timer;
        globalStatePtr = DAT_0112dba8; // +0x20: fade color, +0x24: fade duration
        if (timer == 0) {
            // Skip timer expired
            if (DAT_0112dcc8 > 0.0f) {
                *(int*)(DAT_0112dba8 + 0x20) = DAT_0112dcc4; // set fade color
                *(float*)(globalStatePtr + 0x24) = DAT_0112dcc8; // set fade duration
            }
            DAT_0112dcc4 = 0;          // reset fade color
            DAT_0112dcc8 = 0.0f;       // reset fade duration

            if (this->m_timeSource != 0) {
                // Virtual call to get elapsed time from time source
                // This is a __thiscall via vtable at +0x54 (index 21)
                elapsedTime = (this->m_timeSource->vtable->getElapsedTime)();

                globalStatePtr = DAT_01223394; // pointer to input/skip state
                if (elapsedTime < DAT_00d5ef70 && *(char*)(DAT_01223394 + 0x24) != '\0') {
                    // Skip button pressed and within time threshold
                    *(int*)(DAT_01223394 + 0x40) = 0;                       // skip action = none
                    *(int*)(globalStatePtr + 0x2c) = _DAT_00d5780c;        // target state
                    *(int*)(globalStatePtr + 0x28) = 1;                    // skip enabled
                    *(char*)(globalStatePtr + 0x25) = 0;                   // skip flag cleared
                }
            }
            DAT_012055a1 = 0;  // global flag 1
            DAT_012055a2 = 0;  // global flag 2

            if (DAT_011298d4 != 0) {
                // Stop skip audio if present
                FUN_00815060(this->m_skipAudio);
            }
            this->m_skipAudio = 0;

            FUN_00409d80(5);          // set fade type to 5
            FUN_00409d70(1.0f);       // set fade speed to 1.0
        }

        // Continue cinematic updates
        FUN_00843a50(); // update cinematic audio
        FUN_00842fb0(); // update cinematic video
        FUN_00447c00(); // update input handler

        if ((this->m_flags & 0x1000) != 0) {
            this->m_flags &= ~0x1000;
            FUN_0093a2f0(); // stop additional effect
        }

        FUN_0081dd80(1);  // enable blur/postprocess?
        FUN_0081de30();   // update effect

        if ((this->m_flags & 0x2000) != 0) {
            FUN_008c6df0(); // stop another effect
            this->m_flags &= ~0x2000;
        }

        FUN_00843110();   // update transition state

        if (this->m_callBackPtr != 0) {
            FUN_00846300(); // call skip callback
            this->m_callBackPtr = 0;
        }

        this->m_skipActive = 0; // mark skip as inactive
    }
}