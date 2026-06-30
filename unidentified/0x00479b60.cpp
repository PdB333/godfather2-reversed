// FUN_00479b60: InputMapper::handleButtonEvent
// Handles a button press event by checking against stored button IDs and accumulating flags.
// If the accumulated flags match the expected pattern, triggers an action (immediate or delayed).

#include <cstdint>

class InputMapper {
public:
    // Fields (offsets relative to 'this')
    // +0x14: buttonID1
    // +0x1c: buttonID2
    // +0x24: buttonID3
    // +0x2c: buttonID4
    // +0x34: expectedFlags (bitmask of required buttons)
    // +0x38: currentFlags (accumulated from pressed buttons)
    // +0x3c: activationDelay (seconds, 0 = immediate)
    // +0x40: eventData (pointer to some event/action data)
    // +0x48: clearButtonID (special button that resets all flags)

    void handleButtonEvent(int* buttonEvent);  // param_2 = pointer to button ID
};

// Forward declarations for called functions
void FUN_0046c6a0(int* event);                     // Process/consume button event
void FUN_00408a00(void* param, uint32_t zero);     // Call with callback context
void FUN_0045cac0();                                // Update/render something
void* FUN_009c8e50(uint32_t size);                 // Allocate memory (size = 0xC)
uint32_t FUN_0045ca00(InputMapper* parent);        // Get some value from parent (this - 0x3c)
void FUN_00440590(void* timerData, uint32_t zero, float delay, uint32_t callback, uint32_t zero2); // Set timer

void InputMapper::handleButtonEvent(int* buttonEvent) {
    FUN_0046c6a0(buttonEvent);

    int buttonID = *buttonEvent;
    uint32_t* flagsPtr = reinterpret_cast<uint32_t*>(this + 0x38);  // currentFlags

    if (buttonID == *(int*)(this + 0x14)) {
        *flagsPtr |= 1;
    }
    else if (buttonID == *(int*)(this + 0x1c)) {
        *flagsPtr |= 2;
    }
    else if (buttonID == *(int*)(this + 0x24)) {
        *flagsPtr |= 4;
    }
    else if (buttonID == *(int*)(this + 0x2c)) {
        *flagsPtr |= 8;
    }
    else if (buttonID == *(int*)(this + 0x48)) {  // clear button
        *flagsPtr = 0;
    }

    // Check if accumulated flags match expected pattern
    if (*flagsPtr == *(uint32_t*)(this + 0x34)) {
        float delay = *(float*)(this + 0x3c);
        if (delay <= 0.0f) {
            // Immediate activation: set up callback and call it
            void* callbackData[3];
            // Setup callback context (function pointer PTR_FUN_00e31e2c)
            callbackData[0] = reinterpret_cast<void*>(0x00e31e2c); // hardcoded address
            if (this == reinterpret_cast<InputMapper*>(0x3c)) {
                callbackData[1] = nullptr; // local_14 = 0
            } else {
                callbackData[1] = this + 0x0C; // local_14 = this+0xc (some node)
            }
            // Initialize linked list node at callbackData[1]
            if (callbackData[1] != nullptr) {
                *(void**)(reinterpret_cast<uintptr_t>(callbackData[1]) + 4) = &callbackData[1];
            }
            callbackData[2] = *(void**)(this + 0x40); // eventData
            // Set up local_8 = &callbackData[0]
            void** local_8 = callbackData;
            uint8_t local_4 = 0;
            FUN_00408a00(&callbackData[2], 0); // Process callback
            FUN_0045cac0();                     // Update after immediate action
            *flagsPtr = 0;
            return;
        }
        else {
            // Delayed activation: allocate memory and set timer
            void* timerMem = FUN_009c8e50(0x0C);
            uint32_t callbackArg;
            if (timerMem == nullptr) {
                callbackArg = 0;
            } else {
                // Get parent object (this - 0x3c) for callback
                callbackArg = FUN_0045ca00(reinterpret_cast<InputMapper*>(reinterpret_cast<uintptr_t>(this) - 0x3C));
            }
            FUN_00440590(this + 0x40, 0, delay, callbackArg, 0);
            *flagsPtr = 0;
        }
    }
}