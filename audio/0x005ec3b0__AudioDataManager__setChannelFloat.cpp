// FUNC_NAME: AudioDataManager::setChannelFloat
// Function address: 0x005ec3b0
// Sets a float value on a specific audio channel (index 0-127). Thread-safe with critical section.
// Structure: AudioDataManager has an array of 128 channel structs (size 0xF8) starting at offset 0x5A4.
// Offset 0x580 is a pointer to a mutex or state flag that must be non-zero to allow writes.

__thiscall bool AudioDataManager::setChannelFloat(AudioDataManager* this, ushort channelIndex, float value)
{
    // Check index bounds and that the manager is ready (mutex/shared resource initialized)
    if (channelIndex > 0x7F || *(int*)(this + 0x580) == 0)
    {
        return false;
    }

    // Compute pointer to the specific channel struct
    // Each channel struct is 0xF8 bytes, starting at this + 0x5A4
    byte* channelBase = (byte*)((uint)channelIndex * 0xF8 + (int)this + 0x5A4);

    // Check if value already matches to avoid unnecessary writes
    if (*(float*)channelBase == value)
    {
        return true;
    }

    // Check if a mutex/state allows modification (FUN_005e9d10 likely returns non-zero if ready)
    if (FUN_005e9d10() != 0)
    {
        // Begin critical section
        FUN_00c9eac0();
        // Set the float value (second parameter is 0, possibly a sub-index within the struct?)
        FUN_00ca4e90(0, value);
        // End critical section
        FUN_00c9eae0();

        // Update the stored value
        *(float*)(channelBase) = value;
        return true;
    }

    return false;
}