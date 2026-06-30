// FUNC_NAME: InputManager::processInput

#include <cstdint>

// Forward declarations of called functions
extern void FUN_004d3bc0(void* thisPtr);
extern uint8_t FUN_005dc3d0(void* globalManager, void* inputData);
extern void* DAT_01223508; // InputManager singleton pointer

class InputManager {
public:
    // Process an input event (param_2) from the caller.
    // Returns a status byte (0 = not handled, 1 = handled, etc.)
    uint8_t processInput(void* inputEvent) {
        void* callbackParam;          // local_18 - condition flag (uninitialized in decompiled code)
        void (*callbackFunc)(void*); // local_c - function pointer (uninitialized)

        // Calls an initialization/reset function with 'this' as argument.
        FUN_004d3bc0(this);

        // Delegates actual processing to a global singleton manager.
        uint8_t result = FUN_005dc3d0(DAT_01223508, inputEvent);

        // If a callback parameter is non-zero, invokes the stored callback.
        // (Note: callbackParam and callbackFunc appear uninitialized in the original
        //  decompilation; this may be an artifact of optimization or missing data flow.)
        if (callbackParam != 0) {
            callbackFunc(callbackParam);
        }

        return result;
    }
};