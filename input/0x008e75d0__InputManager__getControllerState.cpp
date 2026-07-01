// FUNC_NAME: InputManager::getControllerState

#include <cstdint>

// Global default value for controller state (likely neutral, e.g., 0.0f or 0x00000000)
extern uint32_t g_defaultControllerState; // _DAT_00d5780c

// Forward declaration for the interface that provides raw controller data
class IControllerDataProvider {
public:
    virtual void* getControllerBuffer() = 0; // vtable +4 offset (index 1)
};

// Function: InputManager::getControllerState
// Address: 0x008e75d0
// Initializes a ControllerState output structure with default values, then
// overrides with live data from a hardware/input manager if available.
// param_1: this pointer (InputManager*)
// param_2: pointer to ControllerState output (16 dwords = 64 bytes)
// Returns: param_2
__thiscall uint32_t* InputManager::getControllerState(int* thisPtr, uint32_t* outState)
{
    uint32_t defaultVal = g_defaultControllerState;

    // Initialize the first 16 dwords of the output with a sparse default pattern.
    // Only indices 0, 5, 10, 15 are set to the global default; the rest are zero.
    outState[0]  = defaultVal;
    outState[1]  = 0;
    outState[2]  = 0;
    outState[3]  = 0;
    outState[4]  = 0;
    outState[5]  = defaultVal;
    outState[6]  = 0;
    outState[7]  = 0;
    outState[8]  = 0;
    outState[9]  = 0;
    outState[10] = defaultVal;
    outState[11] = 0;
    outState[12] = 0;
    outState[13] = 0;
    outState[14] = 0;
    outState[15] = defaultVal;

    // Attempt to get a raw controller data provider from the input manager
    // Virtual function call at vtable+0xc (index 3) – likely "getRawDataProvider()"
    IControllerDataProvider* provider = (IControllerDataProvider*)(*(void***)thisPtr)[3]();
    if (provider != nullptr)
    {
        // Get the raw 64-byte buffer from the provider (vtable+4, index 1)
        uint32_t* rawBuffer = (uint32_t*)(*(void***)provider)[1]();
        if (rawBuffer != nullptr)
        {
            // Overwrite the output with the live data (16 dwords)
            for (int i = 0; i < 16; ++i)
            {
                outState[i] = rawBuffer[i];
            }
        }
    }

    return outState;
}