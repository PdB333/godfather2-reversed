// FUNC_NAME: ControllerManager::allocateControllerSlots
void __thiscall ControllerManager::allocateControllerSlots(int configParam1, int configParam2)
{
    // Free existing controller slots (offset +0x11c holds pointer to array of 16 slots)
    FreeControllerSlots(*(void **)(this + 0x11c)); // 0x11c

    // Allocate memory for 16 controller slots (0x440 = 16 * 0x44)
    void *newSlots = AllocateMemoryBlock(0x440); // 0x440
    if (newSlots != (void *)0x0) {
        // Initialize the newly allocated slots using the provided configuration
        *(void **)(this + 0x11c) = SetupControllerSlots(configParam1, configParam2); // 0x11c
        return;
    }
    *(void **)(this + 0x11c) = (void *)0x0; // 0x11c
}