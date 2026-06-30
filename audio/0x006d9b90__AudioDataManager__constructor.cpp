// FUNC_NAME: AudioDataManager::constructor

// Reconstructed constructor for AudioDataManager (EARS audio data manager)
// Initializes vtable pointers, interface pointers, and zeros internal state
// Address: 0x006d9b90

undefined4 * __thiscall AudioDataManager::constructor(AudioDataManager *this, undefined4 param_2)
{
    // Call base class constructor (likely StreamManager or ResourceManager)
    FUN_00473d90(param_2);

    // Set main vtable pointer (offset +0x00)
    this[0] = &PTR_FUN_00d5f590;

    // Set additional vtable/interface pointers (offset +0x3C, +0x48, +0x50)
    this[0xf] = &PTR_LAB_00d5f580;   // +0x3C: interface vtable 1
    this[0x12] = &PTR_LAB_00d5f57c;  // +0x48: interface vtable 2
    this[0x14] = &PTR_LAB_00d5f578;  // +0x50: interface vtable 3

    // Set data members from globals (likely configuration pointers or handles)
    this[0x18] = DAT_00d5e288;       // +0x60: audio bank handle / manager pointer
    this[0x19] = _DAT_00d5780c;      // +0x64: some global config value
    uVar1 = _DAT_00d5cf70;            // +0x68 duplicate
    this[0x1a] = _DAT_00d5cf70;      // +0x68: another global handle
    this[0x1b] = uVar1;              // +0x6C: same as above (maybe copy)

    // Zero out remaining state fields (counters, flags, error states)
    this[0x1c] = 0;                  // +0x70
    this[0x1d] = 0;                  // +0x74
    this[0x1e] = 0;                  // +0x78
    this[0x1f] = 0;                  // +0x7C
    this[0x20] = 0;                  // +0x80

    return this;
}