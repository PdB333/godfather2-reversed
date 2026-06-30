// FUNC_NAME: startupWaitLoop

// Function at 0x0067c4f0 - startup/initialization wait loop with countdown
// Purpose: waits for a condition (e.g., system ready signal) while pumping subsystems,
//          with a max retry count of 5. Outputs a global loading message each iteration.

#include <cstdint>

// Forward declarations of called helper functions (placeholders based on EARS engine)
void systemUpdateStart();                          // FUN_004034c0
bool isExitRequested();                            // FUN_004035a0 (returns char)
void debugOutputMessage(void* structPtr, int arg); // FUN_00408a00
void updateSubsystemA(int param);                  // FUN_0068bcd0
void updateSubsystemB(int param);                  // FUN_0068baf0
void systemUpdateEnd();                            // FUN_00403530

// Global data: pointer to a loading message string (DAT_01206940)
extern const char* g_loadingMessage;

// Small structure passed to debug output function
struct DebugMessage {
    const char* text;   // +0x00
    int32_t flags;      // +0x04
    int8_t padding;     // +0x08
};

void startupWaitLoop(void) {
    int retryCount = 5;

    // Begin the waiting/update frame
    systemUpdateStart();

    while (true) {
        char checkResult = isExitRequested();   // non-zero means some event occurred
        int newCount = retryCount;

        if (checkResult != '\0') {
            newCount = retryCount - 1;
            if (retryCount == 0) {
                break;  // timed out waiting for condition to become false
            }
        }

        // Prepare and output a debug/loading message
        DebugMessage msg;
        msg.text    = g_loadingMessage;
        msg.flags   = 0;
        msg.padding = 0;
        debugOutputMessage(&msg, 0);            // second param is likely severity level

        // Drive subsystems (e.g., input, audio, network)
        updateSubsystemA(0);
        updateSubsystemB(0);

        retryCount = newCount;
    }

    // Finalize the waiting/update frame
    systemUpdateEnd();
}