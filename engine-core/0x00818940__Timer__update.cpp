//FUNC_NAME: Timer::update
void __thiscall Timer::update(int thisPtr, float deltaTime)
{
    bool hasInput;
    int deltaInt;
    float inputX;
    float inputY;

    deltaInt = (int)deltaTime;
    if (deltaInt >= 0) {
        // Check if there is a referenced object (e.g., a controller or entity)
        if (*(int *)(thisPtr + 8) != 0) {
            inputX = 0.0f;
            inputY = 0.0f;
            // Call to get analog input (likely left stick X/Y)
            // Parameters: 1 (maybe controller index), &inputX, &inputY, 1, 0, deadZone, deadZone, deadZone
            FUN_0079eab0(1, &inputX, &inputY, 1, 0, DAT_00d5ccf8, DAT_00d5ccf8, DAT_00d5ccf8);
            hasInput = (inputX != 0.0f) || (inputY != 0.0f);
            // If there is input, or if a specific bit (bit 4) in the referenced object's flags is set
            if (hasInput || ((*(uint *)(*(int *)(thisPtr + 8) + 0x8e0) >> 4 & 1) != 0)) {
                // Reset timer to max value and mark as active
                *(uint *)(thisPtr + 0xb4) = DAT_01205224;  // +0xB4: timer remaining
                *(byte *)(thisPtr + 0x78) = 1;              // +0x78: timer active flag
                return;
            }
        }
        // If timer is already zero or adding delta would exceed max, do nothing
        if ((*(int *)(thisPtr + 0xb4) == 0) ||
            (DAT_01205224 <= (uint)(*(int *)(thisPtr + 0xb4) + deltaInt))) {
            return;
        }
        // Decrement timer to zero
        *(int *)(thisPtr + 0xb4) = 0;
    }
    // Mark timer as inactive
    *(byte *)(thisPtr + 0x78) = 0;
}