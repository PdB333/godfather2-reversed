// FUNC_NAME: SomeClass::handleComponentEvent
// Function address: 0x00800960
// Role: Handles a component event/lifecycle in the entity system.
// The entity has a pointer at +0x74c to a sub-object that is located at +0x48 inside a container object.
// If the container's virtual function at vtable+0x184 returns true, the component is processed and cleared.

void __thiscall handleComponentEvent(int thisPtr) {
    int* pComponentData = (int*)(thisPtr + 0x74c); // +0x74c: pointer to a component data structure
    int componentValue = *pComponentData;

    // Check if component is valid (non-null and not a sentinel 0x48)
    if (componentValue != 0 && componentValue != 0x48) {
        int* pContainer = nullptr;
        if (componentValue == 0) {
            pContainer = nullptr;
        } else {
            // The component data is at offset 0x48 inside the container object
            pContainer = (int*)(componentValue - 0x48);
        }

        // Virtual call at vtable+0x184: checks if the component's action should be performed
        bool shouldProcess = (**(code**)(*pContainer + 0x184))();
        if (shouldProcess) {
            // Process component action
            func_00707a40(); // Likely dispatch/run action
            int containerBase = (componentValue == 0) ? 0 : componentValue - 0x48;
            func_00704360(containerBase); // Likely reset/deactivate the component container

            // Virtual call at vtable+0x170: perform action with parameters
            // Parameters: id=0, index=0x1ff (511), flag=1, float=1.0f, extra=0
            (**(code**)(*pContainer + 0x170))(0, 0x1ff, 1, 0x3f800000, 0);

            if (componentValue != 0) {
                func_004daf90(pComponentData); // Free the component data
                *pComponentData = 0;            // Clear the pointer
            }
            func_007f6420(10); // Schedule next event/timer (10 ms?)
        }
    }
}