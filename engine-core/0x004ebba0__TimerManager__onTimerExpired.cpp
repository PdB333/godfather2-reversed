// FUNC_NAME: TimerManager::onTimerExpired
void __fastcall TimerManager::onTimerExpired(TimerParam* param)
{
    // param is a small struct: [type (int) +0x00, object (void*) +0x04]
    // The function is called when a timer's age reaches zero or is triggered.
    if (param->type == 1 && param->object != 0) {
        TimerObject* obj = static_cast<TimerObject*>(param->object);
        // obj->age at +0x14 (short), obj->slotIndex at +0x16 (short)
        obj->age -= 1;
        if (obj->age < 1) {
            // Only process if the timer's slot index matches the current global timer count
            if (obj->slotIndex == g_timerCount) {
                g_timerCount--;
                if (g_timerCount >= 0) {
                    // g_timerArray is base of an array of TimerSlot entries (0x20 bytes each)
                    // TimerSlot has a short lifeFlag at +0x04
                    short* pLifeFlag = (short*)((int)&g_timerArray + g_timerCount * 0x20 + 4);
                    int idx = g_timerCount;
                    do {
                        if (*pLifeFlag > 0) {
                            return; // Another timer in a lower slot is still active
                        }
                        idx--;
                        pLifeFlag -= 0x10; // Move to previous slot (0x20 bytes back in pointer arithmetic)
                    } while (idx >= 0);
                    // If all remaining slots have lifeFlag <= 0, the timeline is fully expired.
                }
            }
        }
    }
}

// Data referenced:
// DAT_010c2328 -> int g_timerCount (index of last allocated timer slot)
// DAT_011947f8 -> char g_timerArray[] (array of struct TimerSlot { short lifeFlag; // +0x04, ...});