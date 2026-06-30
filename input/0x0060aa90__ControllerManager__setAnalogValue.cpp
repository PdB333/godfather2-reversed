// FUNC_NAME: ControllerManager::setAnalogValue
void ControllerManager::setAnalogValue(uint controlIndex, float value)
{
    // Global pointer to the singleton ControllerManager instance
    // +0x000: vtable pointer
    ControllerManager* pManager = reinterpret_cast<ControllerManager*>(g_controllerManagerPtr);
    if (controlIndex != 0) {
        // Extract the low byte as the slot index (0-255)
        uint slotIndex = controlIndex & 0xff;
        // Determine which control array to use based on the high bit
        // High bit set -> signed/right-stick/relative controls, else unsigned/left-stick/absolute
        float* controlArray;
        if ((controlIndex & 0x80000000) == 0) {
            // Absolute control values (left stick, triggers)
            controlArray = &g_absoluteControls[slotIndex].x; // +0x11d97f0, array of 16-byte structs
        } else {
            // Relative control values (right stick, shoulder buttons)
            controlArray = &g_relativeControls[slotIndex].x; // +0x11ea8f0
        }
        // Only update if the value actually changed
        if (*controlArray != value) {
            uint vtable = *reinterpret_cast<uint*>(pManager); // vtable pointer
            *controlArray = value;
            if ((controlIndex & 0x80000000) != 0) {
                // Notify for relative control (e.g., right stick)
                (*(code**)(vtable + 0x178))(); // virtual function: onRelativeControlChanged
            } else {
                // Notify for absolute control (e.g., left stick)
                (*(code**)(vtable + 0x1b4))(pManager, slotIndex, controlArray, 1); // virtual function: onAbsoluteControlChanged
            }
        }
    }
}