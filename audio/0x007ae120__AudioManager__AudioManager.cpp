// FUNC_NAME: AudioManager::AudioManager
undefined4 * __thiscall AudioManager::AudioManager(undefined4 *this, undefined4 param2, undefined4 param3)
{
    int someState;

    // Call base class constructor
    BaseClass::BaseClass(param2, param3);

    // Set vtable pointer
    *this = &PTR_LAB_00d6bbfc;

    // Initialize fields
    *(undefined1 *)(this + 0x20) = 0;  // +0x80: some byte field
    this[0x1d] = 0;                     // +0x74: some int field
    this[0x1e] = 0;                     // +0x78: some int field
    this[0x1f] = 0;                     // +0x7c: some int field

    // Play initial sounds (likely sound event IDs)
    playSound(0x31);  // Sound ID 0x31
    playSound(0x22);  // Sound ID 0x22

    // Check state from a manager object (offset 0x16 * 4 = 0x58 from this)
    // The manager has a field at offset 0xff0
    someState = *(int *)(this[0x16] + 0xff0);  // this[0x16] is a pointer to some manager

    if ((someState != 0) && (someState != 0x48)) {
        // If state is non-zero and not 0x48, play sound 0x22 again
        if (*(int *)(this[0x16] + 0xff0) != 0) {
            playSound(0x22);
            return this;
        }
        playSound(0x22);
    }

    return this;
}