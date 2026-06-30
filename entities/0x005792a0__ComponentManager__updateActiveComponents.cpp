// FUNC_NAME: ComponentManager::updateActiveComponents

// Function address: 0x005792a0
// This function iterates over a primary component (at this+0x64) and an array of sub-component containers (at this+0x2ec, count at this+0x2e4).
// Each container is 0xE0 bytes and has a pointer-to-component at +0x64 (same offset as the main one).
// If that pointer is non-null, the component's update function is called.

#include <cstdint>

// Forward declaration of the unknown component update function
void processComponent(int param_1); // FUN_005822d0 - likely a member function of the component

class ComponentManager {
public:
    // Offset   Type     Description
    // 0x00 - 0x63: Other members
    // 0x64: int*      Pointer to the primary component (or active state flag)
    // ... (unknown members, likely padding or other data)
    // 0x2E4: int32_t  Count of sub-component containers
    // 0x2EC: void*    Pointer to array of sub-component containers (each 0xE0 bytes)

    void updateActiveComponents(int deltaTime) { // param_1 is delta time (float or integer)
        // Update the primary component if it exists
        if (*(int*)(this + 0x64) != 0) {
            processComponent(deltaTime);
        }

        int32_t count = *(int32_t*)(this + 0x2E4);
        if (count > 0) {
            // Calculate stride: 0xE0 (224 bytes) per container
            int containerBase = *(int*)(this + 0x2EC); // Base address of the array
            for (int i = 0; i < count; ++i) {
                int* container = (int*)(containerBase + i * 0xE0);
                // Check if the component pointer at offset +0x64 inside the container is non-null
                if (*(container + 0x64 / sizeof(int)) != 0) { // container[0x64/4] = container[25]
                    processComponent(deltaTime); // Note: same param_1 as primary; could also be container-specific, but original code passes param_1
                }
            }
        }
    }
};