// FUNC_NAME: VehicleBrain::isControlActive
// Function at 0x008653f0 checks if a specific vehicle digital control (e.g., gas/brake) is active.
// Works with forward/reverse control sets based on vehicle state flags.
// Parameters: this (vehicle brain object), isBrakeMode (0 = gas axis, non-zero = brake axis)

bool __thiscall VehicleBrain::isControlActive(int this, bool isBrakeMode)
{
    // +0xF28: Vehicle state flags
    uint flags = *(uint *)(this + 0xF28);
    // Control axis threshold: 0x800 (brake) or 0xC00 (gas)
    ushort axisMask = isBrakeMode ? 0x800 : 0xC00;
    bool result = false;

    // Check if vehicle is active (bit 25)
    if ((flags >> 25) & 1)
    {
        // Determine direction: bit 29 == 0 means forward, 1 means reverse
        if (((flags >> 29) & 1) == 0)
        {
            // Forward control set
            // +0x1038: Pointer to forward control? (null check)
            if (*(int *)(this + 0x1038) != 0)
            {
                // +0x1040: Pointer to control state structure; +10 = current digital input bits
                ushort inputBits = *(ushort *)(*(int *)(this + 0x1040) + 10);
                if (inputBits & axisMask)
                {
                    result = true;
                }
            }
        }
        else
        {
            // Reverse control set
            // +0x1044: Pointer to reverse control? (null check)
            if (*(int *)(this + 0x1044) != 0)
            {
                // +0x104C: Pointer to reverse control state; +10 = current digital input bits
                ushort inputBits = *(ushort *)(*(int *)(this + 0x104C) + 10);
                if (inputBits & axisMask)
                {
                    result = true;
                }
            }
        }
    }
    return result;
}