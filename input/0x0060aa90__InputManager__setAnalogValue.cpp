// FUNC_NAME: InputManager::setAnalogValue

// Reconstructed from Ghidra at 0x0060aa90
// Function: Sets an analog float value (e.g., joystick axis) in one of two arrays
// based on sign bit of combinedIndex (bit 31): positive = controller, negative = keyboard/mouse.
// If value changes, calls the appropriate callback on the global InputManager singleton.

#include <cstdint>

// Forward declaration of the InputManager class with stored function pointers at known offsets
class InputManager {
public:
    // offset 0x178: void (*onNegativeAnalogChange)();  (no arguments)
    void (*onNegativeAnalogChange)();
    
    // offset 0x1b4: void (*onPositiveAnalogChange)(uint8_t index, float* value, int32_t flag);
    void (*onPositiveAnalogChange)(uint8_t index, float* value, int32_t flag);
    
    // other members...
};

// Global pointer to the InputManager singleton (stored at DAT_01205750)
extern InputManager* g_inputManager;

// Two arrays of 256 slots, each 0x10 bytes (we only use the first float at offset 0)
// Positive sign (controller) values
static float s_controllerAnalogValues[256][4]; // +0x00: float value, rest unknown
// Negative sign (keyboard/mouse) values
static float s_keyboardAnalogValues[256][4];

void InputManager::setAnalogValue(uint32_t combinedIndex, float newValue)
{
    // Combined index: bits 0-7 = slot index (0-255)
    // bit 31 = sign (1 = negative/alternate array)
    if (combinedIndex == 0) {
        return;
    }

    uint8_t idx = static_cast<uint8_t>(combinedIndex & 0xFF);
    float* pValue;

    if (combinedIndex & 0x80000000) {
        // Negative sign: use keyboard/mouse array
        pValue = &s_keyboardAnalogValues[idx][0];
    } else {
        // Positive sign: use controller array
        pValue = &s_controllerAnalogValues[idx][0];
    }

    if (*pValue != newValue) {
        *pValue = newValue;

        // Notify the InputManager about the change
        InputManager* mgr = g_inputManager;

        if (combinedIndex & 0x80000000) {
            // Call the negative analog change callback (offset 0x178)
            // Typically used for keyboard/mouse input
            if (mgr->onNegativeAnalogChange) {
                mgr->onNegativeAnalogChange();
            }
        } else {
            // Call the positive analog change callback (offset 0x1b4)
            // Typically used for controller input; passes the slot index, value pointer, and a flag (1)
            if (mgr->onPositiveAnalogChange) {
                mgr->onPositiveAnalogChange(idx, pValue, 1);
            }
        }
    }
}