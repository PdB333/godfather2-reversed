// FUNC_NAME: InputDeviceManager::initializeDeviceStates
// Address: 0x005f0e40
// Role: Initializes two device state blocks (each 12 bytes) inside the InputDeviceManager.
//        Allocates a pool of 0x80 elements of size 0x44, then initializes each state block.

#include <cstdint>

// Forward declarations for functions called
void* allocateObjectPool(uint32_t elementCount, uint32_t elementSize, void* destructor);
void initDeviceStateBlock(void* block, uint32_t maxValue);

// Structure representing one device state (size = 0xC)
struct DeviceState {
    uint32_t field0;      // +0x00
    uint32_t field4;      // +0x04
    uint16_t maxValue;    // +0x08 (set to 0x80)
    uint16_t fieldA;      // +0x0A (set to 0)
};

class InputDeviceManager {
public:
    DeviceState states[2];   // +0x00 (total size 0x18)

    // Constructor-like initialization
    void initializeDeviceStates();
};

void InputDeviceManager::initializeDeviceStates()
{
    // Allocate a pool of 0x80 elements, each 0x44 bytes, with destructor callback at 0x005f0e20
    allocateObjectPool(0x80, 0x44, (void*)0x005f0e20);

    DeviceState* current = &states[0];
    DeviceState* const end = &states[2];

    while (current < end) {
        if (current != nullptr) {
            current->field0 = 0;
            current->field4 = 0;
            current->maxValue = 0x80;
            current->fieldA = 0;
            initDeviceStateBlock(current, 0x80);
        }
        ++current;
    }
}