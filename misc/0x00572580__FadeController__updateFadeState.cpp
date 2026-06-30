// FUNC_NAME: FadeController::updateFadeState
// Address: 0x00572580
// __thiscall member function of a fade/timer controller

void FadeController::updateFadeState()
{
    // +0x121: bool m_bDone (or m_bComplete)
    if (*(char*)(this + 0x121) == '\0') 
    {
        // +0x110: int m_iState (0 = idle, 1 = fading, -1 = done)
        if (*(int*)(this + 0x110) == 1) 
        {
            // +0x114: float m_fCurrent (timer/counter)
            // +0x118: float m_fTarget (duration/threshold)
            if (*(float*)(this + 0x114) < *(float*)(this + 0x118)) 
            {
                // Exponential fade calculation
                // DAT_00e2b1a4 and DAT_00e2cb90 are global constants (likely max value and speed factor)
                *(float*)(this + 0x114) = 
                    (DAT_00e2b1a4 - *(float*)(this + 0x114) / *(float*)(this + 0x118)) * DAT_00e2cb90;
                *(int*)(this + 0x110) = -1;    // mark state as done
                *(char*)(this + 0x121) = 1;     // set complete flag
                return;
            }
        }
        // No active fade or target reached
        *(float*)(this + 0x114) = 0.0f;      // reset current
        *(int*)(this + 0x110) = -1;          // reset state to done
        *(char*)(this + 0x121) = 1;          // mark complete
    }
    // else already done, do nothing
}