// FUNC_NAME: InputManager::processProfiledInputEvent
#include <windows.h>

// Forward declaration of the actual event handler
void InputManager::handleInputEvent(void* param1, void* param2, void* param4, void* param5, 
                                    unsigned short param6, unsigned short param7, bool flag);

// Global profiling counters (low and high parts of accumulated performance counter ticks)
extern unsigned int g_inputProfilerTotalTimeLow;   // _DAT_01205950
extern unsigned int g_inputProfilerTotalTimeHigh;  // _DAT_01205954

// This function wraps the input event handler with performance profiling.
// It is only active when the input manager is in a specific state (mode 2 or 3).
// The event types are filtered: certain key/button codes (0x1E-0x22) are allowed,
// and for a subset of those plus some numeric codes a special flag is passed to the handler.
void __thiscall InputManager::processProfiledInputEvent(InputManager* this,
                                                        void* param1, void* param2,
                                                        int eventType,
                                                        void* param4, void* param5,
                                                        unsigned short param6,
                                                        unsigned short param7)
{
    LARGE_INTEGER startTime, endTime;
    bool isSpecial;

    QueryPerformanceCounter(&startTime);

    // Only profile when the input manager is in state 2 or 3 (e.g., active/connected)
    if (this->state == 2 || this->state == 3) {
        switch (eventType) {
            case 0x1E: // Keyboard 'A' or controller button?
            case 0x1F: // 'S'
            case 0x20: // 'D'
            case 0x21: // 'F'
            case 0x22: // 'G'
                break;
            default:
                goto skipProfiling; // Unsupported event type – skip profiling
        }

        // Determine whether this event should be flagged as "special"
        // (these event codes likely correspond to movement/action inputs)
        isSpecial = (eventType == 0x20 || eventType == 0x21 || eventType == 0x1F ||
                     eventType == 5 || eventType == 4 ||
                     eventType == 3 || eventType == 7);

        // Call the actual input event handler with the special flag
        handleInputEvent(param1, param2, param4, param5, param6, param7, isSpecial);

        // Measure elapsed time and add to global profiling accumulator
        QueryPerformanceCounter(&endTime);
        unsigned int lowDiff = endTime.LowPart - startTime.LowPart;
        bool carry = CARRY4(g_inputProfilerTotalTimeLow, lowDiff);   // carry from low part addition
        g_inputProfilerTotalTimeLow += lowDiff;
        g_inputProfilerTotalTimeHigh += (endTime.HighPart - startTime.HighPart)
                                      - (endTime.LowPart < startTime.LowPart)
                                      + (uint)carry;
    }

skipProfiling:
    return;
}