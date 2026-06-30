// FUNC_NAME: EventProcessor::handleMessage
// Function address: 0x006be770
// Role: Handles an incoming message/event, validates it against expected type, checks a condition, and dispatches to one of two stored callbacks based on global state.

// Forward declarations for called functions (assumed global or member)
void FUN_0046c6a0(int* param);          // Processes the message structure
int FUN_006b0ee0(int param);            // Checks some condition (e.g., object validity)
int FUN_006b4860(void);                 // Returns global state (e.g., game mode)
void FUN_00408a00(int* data, int flag); // Dispatches action (e.g., send response)

void __thiscall EventProcessor::handleMessage(int thisPtr, int* message)
{
    int globalState;
    int unused_local_8;
    char unused_local_4;
    int callbackData;

    // Process the incoming message structure
    FUN_0046c6a0(message);

    // Check if the message type matches the expected type stored at +0x1c
    if (*message == *(int*)(thisPtr + 0x1c)) {
        // Check a condition using the value at +0x14 (e.g., a feature flag or object pointer)
        if (FUN_006b0ee0(*(int*)(thisPtr + 0x14)) != 0) {
            globalState = FUN_006b4860(); // Get current global state (e.g., game mode)
            unused_local_8 = message[1];  // Possibly used elsewhere, but not here
            unused_local_4 = 0;

            // Compare global state with the stored state at +0x18
            if (globalState == *(int*)(thisPtr + 0x18)) {
                // Use callback data from +0x24
                callbackData = *(int*)(thisPtr + 0x24);
                FUN_00408a00(&callbackData, 0);
                return;
            }
            // Otherwise use callback data from +0x2c
            callbackData = *(int*)(thisPtr + 0x2c);
            FUN_00408a00(&callbackData, 0);
        }
    }
    return;
}