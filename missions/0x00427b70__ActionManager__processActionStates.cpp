// FUNC_NAME: ActionManager::processActionStates
// Address: 0x00427b70
// Role: Processes action state machines for up to 512 actions (0x10-byte struct each).
// Each entry contains: state (0x00), retryCount (0x04), object pointer (0x08), timerValue (0x0C).
// Virtual function at vtable+0x1c is called to check action completion.
// If check returns 0, timer is reset to 0x10 and state becomes 2.
// If check returns 1, state becomes 2 (no timer reset).
// If check returns other (2), retryCount is incremented; if >2, emergency handler is called.

struct ActionEntry {
    int state;          // +0x00: 0=idle, 1=pending, 2=done
    int retryCount;     // +0x04: number of retries
    void* object;       // +0x08: pointer to object with vtable
    int timerValue;     // +0x0C: timer / parameter
};

// Global array of 512 action entries (0x2000 bytes / 0x10)
extern ActionEntry g_actionEntries[512];

// Forward declaration of emergency function called on excessive retries
void FUN_00427b00(void);

void ActionManager::processActionStates(void) {
    for (int i = 0; i < 512; ++i) {
        ActionEntry& entry = g_actionEntries[i];
        if (entry.state == 1) {  // pending
            // Virtual call at vtable+0x1c (method offset 0x1c / 4 = 7)
            typedef int (__thiscall* CheckFunc)(void* obj, int* timer, int param3, int param4);
            CheckFunc check = (CheckFunc)(*((int*)entry.object + 7));
            int result = check(entry.object, &entry.timerValue, 4, 0);

            // Map result to internal code: 0->1, 1->2, others->0
            if (result == 0) {
                result = 1;
            } else if (result != 1) {
                result = 0;
            } else {
                result = 2;
            }

            // Apply state transition
            if (result == 0) {
                entry.timerValue = 0x10;  // reset timer
            } else if (result != 1) {
                // result must be 2 here
                entry.retryCount++;
                if (entry.retryCount > 2) {
                    FUN_00427b00();  // fire emergency handler
                }
                goto next_entry;
            }

            // result is 0 or 1: mark as done
            entry.state = 2;
        }
next_entry:;
    }
}