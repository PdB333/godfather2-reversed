// FUNC_NAME: EntityComponent::initComponent (at 0x00707430)
// Initializes a sub-component pointer stored at offset +0x1b0, allocating a new object
// from a pool and setting fields for timer/state management.

#include <cstdint>

// Forward declarations of unknown helper functions
extern "C" int __fastcall getFrameCount();
extern "C" int* __fastcall allocateFromPool(int poolType, int size, int timestamp);
extern int g_someGlobalConstant; // _DAT_00d5780c

class EntityComponent {
public:
    void initComponent();
};

void __fastcall EntityComponent::initComponent()
{
    // Retrieve pointer to a sub-component stored at +0x1b0 from 'this'
    int* subComponent = *reinterpret_cast<int**>(reinterpret_cast<uintptr_t>(this) + 0x1b0);
    if (subComponent != nullptr) {
        // Get a timestamp/identifier from the engine
        int timestamp = getFrameCount();
        // Allocate a new object from pool (pool type 8, size 0x15 = 21 bytes)
        int* newObject = allocateFromPool(8, 0x15, timestamp);
        int globalVal = g_someGlobalConstant;

        // Initialize fields of the newly allocated object
        *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(subComponent) + 0x2c) = reinterpret_cast<int>(newObject);
        *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(subComponent) + 0x84) = globalVal;
        *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(subComponent) + 0x88) = 0;
        *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(subComponent) + 0x184) = globalVal;
        *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(subComponent) + 0x188) = globalVal;
    }
}