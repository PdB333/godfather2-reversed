// FUNC_NAME: AsyncFileRequest::updateStatus
// Function at 0x005e8f20: State machine for asynchronous file/stream loading request.
// Manages transitions between states: Idle (0), Pending (1), Processing (2), Complete (3).
// Uses a global vtable (g_RequestManager) at DAT_01223510 for callbacks.
// Structure at this+0x1b4 holds request state: strings, retry count, state, flags.

#include <cstdint>

// Forward declaration of global vtable pointer (from external)
extern void* g_RequestManager;  // DAT_01223510

// Default empty string used when loaded filename is null
extern const char g_emptyString[]; // DAT_0120546e

int AsyncFileRequest::updateStatus() {
    bool bErrorFlag = false;

    do {
        // Get pointer to internal request state structure at offset 0x1b4
        RequestState* pState = *(RequestState**)(this + 0x1b4);

        // Current state is stored at pState+0x60
        int currentState = *(int*)(pState + 0x60);

        if (currentState == 0) {
            // STATE 0: Idle – ready to initiate a new async read
            if (*(int*)(pState + 0x24) != 0 && *(char*)(pState + 0x68) != 0) {
                // Check if the manager (this+0x1c8) is ready to start a new request
                char ready = (**(code**)(*(int*)g_RequestManager + 0x48))(*(int*)(this + 0x1c8));
                if (ready != 0) {
                    // Get the filename string from pState+0x20
                    const char* filename = *(const char**)(pState + 0x20);
                    if (filename == nullptr) {
                        filename = g_emptyString;
                    }

                    // Submit the async read request via manager's vtable+0x4c
                    int result = (**(code**)(*(int*)g_RequestManager + 0x4c))(
                        *(int*)(this + 0x1c8),
                        filename,
                        *(int*)(this + 0x20c),   // Offset or buffer size
                        *(int*)(this + 0x248)    // Additional parameter (e.g., buffer address)
                    );

                    // Store the returned handle/result at this+0x1d0
                    *(int*)(this + 0x1d0) = result;

                    if (result < 0) {
                        // Error: mark the state as failed
                        bErrorFlag = true;
                        *(char*)(pState + 0x68) = 0; // Clear ready flag
                    }
                    else if (*(int*)(this + 0x1cc) < 0) {
                        // Store handle only if previous handle was invalid (first time)
                        *(int*)(this + 0x1cc) = result;
                    }
                }
            }

            // Transition to state 1 (Pending)
            *(int*)(pState + 0x60) = 1;

            // Set retry count from pState+0x50
            if (*(int*)(pState + 0x50) == 0) {
                *(int*)(pState + 100) = -1; // Infinite retries? (100, likely wrong: should be 0x64? Wait, decompiler wrote +100 which is decimal? Actually probably offset 0x64, but it's decimal in decompiled. We'll keep as 0x64)
                // Actually in the code: *(int *)(iVar6 + 100) = 0xffffffff; so offset 0x64
                *(int*)(pState + 0x64) = -1;
            }
            else {
                *(int*)(pState + 0x64) = *(int*)(pState + 0x50);
            }
        }
        else if (currentState == 1) {
            // STATE 1: Pending – waiting for data or condition
            // Check if we have data buffers ready (pState+0x34 and pState+0x64)
            if (*(int*)(pState + 0x34) == 0 || *(int*)(pState + 0x64) == 0 || *(char*)(pState + 0x68) == 0) {
                // Not ready: move to state 2 (Processing)
                *(int*)(pState + 0x60) = 2;
                continue; // Go to top of loop
            }

            // Check if the current async operation is complete
            char complete = (**(code**)(*(int*)g_RequestManager + 0x8c))(*(int*)(this + 0x1d0));
            if (complete == 0) {
                // Not complete
                char ready = (**(code**)(*(int*)g_RequestManager + 0x48))(*(int*)(this + 0x1c8));
                if (ready == 0) {
                    // Manager not ready to read more, skip
                    continue;
                }
            }

            // Start another read (or retry?) if needed
            const char* filename = *(const char**)(pState + 0x30);
            if (filename == nullptr) {
                filename = g_emptyString;
            }

            int result = (**(code**)(*(int*)g_RequestManager + 0x4c))(
                *(int*)(this + 0x1c8),
                filename,
                *(int*)(this + 0x20c),
                *(int*)(this + 0x248)
            );

            *(int*)(this + 0x1d0) = result;

            if (result < 0) {
                // Error
                *(char*)(pState + 0x68) = 0;
            }
            else if (*(int*)(this + 0x1cc) < 0) {
                *(int*)(this + 0x1cc) = result;
            }

            // Decrement retry count at pState+0x64
            if (*(int*)(pState + 0x64) >= 1) {
                int* pRetry = (int*)(pState + 0x64);
                (*pRetry)--;
                if (*(int*)(pState + 0x64) != 0) {
                    continue;
                }
                // Retries exhausted: move to state 2
                *(int*)(pState + 0x60) = 2;
                bErrorFlag = false; // Reset error flag for the loop? Actually not set true here.
            }
        }
        else if (currentState == 2) {
            // STATE 2: Processing – finalizing the request
            if (*(int*)(pState + 0x44) != 0 && *(char*)(pState + 0x68) != 0) {
                // Check if manager can finalize
                char canFinalize = (**(code**)(*(int*)g_RequestManager + 0x48))(*(int*)(this + 0x1c8));
                if (canFinalize == 0) {
                    goto label_exit; // Skip to end
                }

                const char* filename = *(const char**)(pState + 0x40);
                if (filename == nullptr) {
                    filename = g_emptyString;
                }

                int result = (**(code**)(*(int*)g_RequestManager + 0x4c))(
                    *(int*)(this + 0x1c8),
                    filename,
                    *(int*)(this + 0x20c),
                    *(int*)(this + 0x248)
                );

                *(int*)(this + 0x1d0) = result;

                if (result < 0) {
                    // Error: clear flag
                    *(char*)(pState + 0x68) = 0;
                }
                else if (*(int*)(this + 0x1cc) < 0) {
                    *(int*)(this + 0x1cc) = result;
                    // Move to state 3 (Complete)
                    *(int*)(pState + 0x60) = 3;
                    goto label_exit;
                }
            }

            // If conditions not met, also transition to state 3? Actually original: *(undefined4 *)(*(int *)(unaff_ESI + 0x1b4) + 0x60) = 3; after the if block.
            *(int*)(pState + 0x60) = 3;
        }
        else {
            // Unknown state (should not happen)
        }

label_exit:
        // Continue loop if no error and not in state 3? Actually the loop continues while bVar3 is false.
        // bVar3 is set true only from state 2 error path where result < 0.
        // Also from state 1 when retry exhausted? Wait, that sets bVar3=false, so loop continues.
        // Actually the original: while (!bVar3) repeats the whole switch.
    } while (!bErrorFlag);

    // Return value: low byte is 1 if state == 3, else 0? CONCAT31 with int3 is weird.
    // Probably returns state==3 as a boolean.
    int state = *(int*)(*(int*)(this + 0x1b4) + 0x60);
    return (state == 3) ? 1 : 0;
}