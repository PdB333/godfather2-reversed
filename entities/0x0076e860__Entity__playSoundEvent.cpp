// FUNC_NAME: Entity::playSoundEvent
// Address: 0x0076e860
// Role: Plays a sound event based on whether the given sound ID matches one of two current sound IDs stored in the sound state object.
// The sound state object is at this+0x50. Offsets 0x68c and 0x674 hold encoded sound IDs (shifted right by 2).
// If the sound ID matches either, a "valid" sound (0xcc610fa) is played; otherwise an "invalid" sound (0x4eb13e2d) is played.
// The virtual function at vtable+0x2c takes (uint hash, int, int, int, float volume, float pitch).

void __thiscall Entity::playSoundEvent(uint soundId)
{
    // Get pointer to sound state object (offset 0x50 from this)
    uint* soundState = *(uint**)(this + 0x50);

    // Read two current sound IDs (stored with a right shift of 2)
    uint currentId1 = *(uint*)(soundState + 0x68c) >> 2;
    uint currentId2 = *(uint*)(soundState + 0x674) >> 2;

    if (soundId != currentId1 && soundId != currentId2)
    {
        // Play "invalid" sound
        (**(code**)(*this + 0x2c))(0x4eb13e2d, 1, 1, 0, 0x3f800000, 0x3f800000);
    }
    else
    {
        // Play "valid" sound
        (**(code**)(*this + 0x2c))(0xcc610fa, 1, 1, 0, 0x3f800000, 0x3f800000);
    }
}