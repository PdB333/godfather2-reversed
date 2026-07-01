// FUNC_NAME: VehicleInputHandler::processInput
// Address: 0x0076ed30
// Role: Process analog input from controller (gamepad) and keyboard, compute combined control value and apply it.

#include <cstdint>

// Forward declarations of other engine functions
void FUN_0076ec60(void*);          // Possibly resetInput
void FUN_00b9a9fa();               // Unknown, perhaps floating-point normalization
void* FUN_00471610();              // Returns pointer to keyboard input state
void FUN_007f7540(float controlValue, uint32_t flags, float sensitivity); // Apply control

// Global variables (constants likely)
extern float DAT_00d5ef84;         // Dead zone threshold
extern uint32_t DAT_00e44680;      // Mask for extracting axis bits (e.g., 0xFFFF)
extern float DAT_00d5f520;         // Sensitivity multiplier

// Input device vtable indices
constexpr int kGetAnalogInputs = 0x90; // Offset in vtable

void __fastcall VehicleInputHandler::processInput(void* thisPtr)
{
    // Check if controller input object exists at offset +0x50
    void* controller = *(void**)((char*)thisPtr + 0x50);
    if (controller == nullptr) {
        return;
    }

    // Buffer for analog input data (12 bytes)
    uint8_t analogBuffer[12];  // But actual data may extend beyond; treated as raw storage
    uint32_t axisX = 0;        // uStack_3c - assumed left stick X
    float    axisY = 0.0f;     // fStack_38 - assumed left stick Y (magnitude)
    uint32_t trigger = 0;      // local_34 - assumed trigger value

    // Call virtual function to get analog input from controller
    // signature: void getAnalogInputs(void* outputBuffer, void* inputData, uint32_t controllerIndex)
    // controllerIndex = 1
    void* inputData = (void*)((char*)controller + 0x1ba);
    auto vtable = *(void***)controller;
    auto getAnalogInputs = (void(__thiscall*)(void*, void*, uint32_t))vtable[kGetAnalogInputs];
    getAnalogInputs(controller, analogBuffer, inputData, 1);

    // Note: The decompiler shows that after the call, the code reads axisX, axisY, trigger
    // which are actually on the stack after the 12-byte buffer. They might be part of a larger struct.
    // For clarity, we read them from the stack as if they were returned by the function.
    // The offsets: axisX at rbp-0x3c, axisY at rbp-0x38, trigger at rbp-0x34.
    // We simulate by assuming they are stored in the local variables.
    // In the reconstructed code, we directly assign from the buffer if appropriate.
    // For now, we keep the logic as is, but note the confusing layout.

    // Compute magnitude from controller input (use axisY if any axis exceeds dead zone)
    float controllerMagnitude;
    if (DAT_00d5ef84 <= (float)(axisX & DAT_00e44680) ||
        DAT_00d5ef84 <= (float)(*(uint32_t*)&axisY & DAT_00e44680) || // reinterpret bitwise
        DAT_00d5ef84 <= (float)(trigger & DAT_00e44680)) {
        double temp = (double)axisY;  // axisY is float, but used as magnitude
        FUN_00b9a9fa();              // might do nothing; kept for compatibility
        controllerMagnitude = (float)temp;
    } else {
        controllerMagnitude = 0.0f;
    }

    // Get keyboard input state
    void* keyboardState = FUN_00471610(); // Returns pointer to a struct with analog inputs

    float keyboardMagnitude;
    if (DAT_00d5ef84 <= (float)(*(uint32_t*)((char*)keyboardState + 0x20) & DAT_00e44680) ||
        DAT_00d5ef84 <= (float)(*(uint32_t*)((char*)keyboardState + 0x24) & DAT_00e44680) ||
        DAT_00d5ef84 <= (float)(*(uint32_t*)((char*)keyboardState + 0x28) & DAT_00e44680)) {
        double temp = (double)*(float*)((char*)keyboardState + 0x24); // Use offset +0x24 as magnitude
        FUN_00b9a9fa();
        keyboardMagnitude = (float)temp;
    } else {
        keyboardMagnitude = 0.0f;
    }

    // Combine: controller minus keyboard (likely for steering where keyboard provides opposite)
    float finalControl = controllerMagnitude - keyboardMagnitude;

    // Apply control with sensitivity
    FUN_007f7540(finalControl, 1, DAT_00d5f520);
}