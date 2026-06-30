// FUNC_NAME: AIBehavior::AIBehavior
undefined4 * __thiscall AIBehavior::AIBehavior(undefined4 *this, undefined4 arg0, undefined4 arg1)
{
    uint *flagsPtr;
    float threshold;
    int basePtr;
    float randomVal;

    // Call base class constructor (likely EntityComponent or similar)
    BaseClassConstructor(arg0, arg1);

    // Initialize vtable pointers and fields
    this[0x14] = &PTR_FUN_00e32808; // Initial vtable at +0x50
    this[0x15] = 0;                 // +0x54
    this[0] = &PTR_LAB_00d651f8;    // Main vtable at +0x00
    this[0x14] = &PTR_LAB_00d651f4; // Override vtable at +0x50
    this[0x17] = 0;                 // +0x5C
    this[0x1e] = 0;                 // +0x78
    this[0x23] = 0;                 // +0x8C
    this[0x24] = 0;                 // +0x90
    this[0x29] = 0;                 // +0xA4
    this[0x2a] = 0;                 // +0xA8 flags
    this[0x2b] = 0;                 // +0xAC
    this[0x2c] = 0;                 // +0xB0
    this[0x2d] = 0;                 // +0xB4
    this[0x30] = 0;                 // +0xC0
    this[0x31] = 0;                 // +0xC4
    *(byte *)&this[0x35] = 0;       // +0xD4 (1 byte)
    this[0x36] = 0;                 // +0xD8
    this[0x3b] = 0;                 // +0xEC
    this[0x3c] = 0;                 // +0xF0
    this[0x1a] = 0;                 // +0x68
    this[0x19] = 0;                 // +0x64
    this[0x18] = 0;                 // +0x60

    // Derive internal pointers from owner pointer at +0x48
    if (this[0x12] == 0) {
        basePtr = 0;
    }
    else {
        basePtr = this[0x12] - 0x48; // Subtract offset to get base object
    }
    this[0x16] = basePtr;             // +0x58 (pointer to base object)
    this[0x2e] = basePtr + 0x3c0;     // +0xB8 (pointer to subcomponent)

    // Random chance to set/unset flag (bit 2 of flags at +0xA8)
    threshold = DAT_00d651f0;          // float threshold
    randomVal = (float)_rand() * DAT_00e44590; // random in [0,1]
    if (randomVal <= threshold) {
        this[0x2a] &= 0xfffffffb;     // Clear bit 2
    }
    else {
        this[0x2a] |= 4;              // Set bit 2
    }

    // Initialize behavior parameters
    this[0x1d] = 0;                   // +0x74 (some index)
    this[0x1c] = 3;                   // +0x70 (action count or state)
    this[0x1b] = threshold;           // +0x6C (store threshold as float)

    // Check if base object has a flag at +0x8e8 bit 3; set bit 4 of behavior flags
    if ((*(uint *)(this[0x16] + 0x8e8) >> 3 & 1) == 0) {
        this[0x2a] &= 0xffffffef;     // Clear bit 4
    }
    else {
        this[0x2a] |= 0x10;           // Set bit 4
    }

    // Play a sound or event (0x43 = 67, possibly a sound cue)
    FUN_007f63e0(0x43);

    // Check another flag at +0xE4 from subcomponent; if bit 6 set, set bit 8 of flags and call virtual function
    if ((*(uint *)(this[0x2e] + 0xe4) >> 6 & 1) != 0) {
        this[0x2a] |= 0x100;          // Set bit 8 (0x100)
        // Call a virtual method on the base object (offset 0x290 in vtable) with args 0 and 0x10
        (**(code **)(*(int *)this[0x16] + 0x290))(0, 0x10);
    }

    // Set a random timer for next behavior action
    randomVal = (float)_rand() * DAT_00e44590 * DAT_00d5f520 + DAT_00d5f378;
    this[0x2f] = randomVal;           // +0xBC (behavior timer in seconds?)

    // If a specific byte at base+0x566 bit0 is zero, set flag and modify another flag
    if ((*(byte *)(this[0x16] + 0x566) & 1) == 0) {
        flagsPtr = (uint *)(this[0x16] + 0x564);
        *flagsPtr |= 0x10000;         // Set bit 16 in base flags
        this[0x2a] |= 0x400;          // Set bit 10 (0x400) in behavior flags
    }

    return this;
}