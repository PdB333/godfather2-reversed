// FUNC_NAME: Entity::Entity
Entity* __thiscall Entity::Entity(Entity* this, int argFlags)
{
    // Call base class constructor
    BaseClass::Constructor(argFlags);

    // Set vtable pointers (multiple inheritance or embedded vtables)
    // +0x50: second vtable pointer
    this[0x50/4] = &PTR_LAB_00e32854;   // +0x50
    *this = &PTR_FUN_00e32b6c;          // +0x00: primary vtable
    this[0x3C/4] = &PTR_LAB_00e32b98;   // +0x3C
    this[0x48/4] = &PTR_LAB_00e32ba8;   // +0x48
    this[0x50/4] = &PTR_LAB_00e32bac;   // +0x50 (overwrites earlier)

    // Load global constants
    unsigned int gValA = DAT_00e2b1a4;   // global float? int?
    unsigned int gValB = DAT_00e2b04c;   // global float? int?

    // Initialize fields
    this[0x15] = 0;                     // +0x54
    *(short*)((int)this + 0x5A) = 0;   // +0x5A
    this[0x17] = 0;                     // +0x5C
    *(short*)((int)this + 0x62) = 0;   // +0x62
    this[0x19] = 0;                     // +0x64
    *(short*)((int)this + 0x6A) = 0;   // +0x6A

    // Magic debug markers (will be overwritten later)
    this[0x1B] = 0xBADBADBA;           // +0x6C
    this[0x1C] = 0xBEEFBEEF;           // +0x70
    this[0x1D] = 0xEAC15A55;           // +0x74
    this[0x1E] = 0x91100911;           // +0x78

    this[0x22] = 0;                     // +0x88
    this[0x23] = 0;                     // +0x8C
    *(byte*)(this + 0x24) = 0;         // +0x90 (byte)
    this[0x21] = 1;                     // +0x84
    this[0x25] = 1;                     // +0x94
    this[0x26] = 0;                     // +0x98
    this[0x27] = 0;                     // +0x9C
    *(byte*)(this + 0x28) = 0;         // +0xA0 (byte)
    this[0x2B] = gValB;                // +0xAC
    unsigned int gValC = DAT_00e2b050; // another global
    this[0x2E] = 0;                     // +0xB8
    *(byte*)(this + 0x29) = 0;         // +0xA4 (byte)
    this[0x2A] = gValA;                // +0xA8
    *(byte*)((int)this + 0xA5) = 0;    // +0xA5 (byte)
    this[0x2C] = gValC;                // +0xB0
    this[0x2D] = 0;                     // +0xB4
    this[0x2F] = 0;                     // +0xBC
    this[0x30] = 0;                     // +0xC0

    // Call random seed initializer (FUN_005e3130)
    int randomVal = FUN_005e3130();     // returns something in EDX

    unsigned int globalD = DAT_0110ac04;
    this[0x3A] = randomVal;            // +0xE8
    this[0x4C] = globalD;              // +0x130
    this[0x4D] = randomVal;            // +0x134
    *(short*)((int)this + 0x138) = (short)randomVal; // +0x138
    *(short*)((int)this + 0x13A) = (short)randomVal; // +0x13A

    this[0x3C] = gValA;                // +0xF0
    this[0x3D] = 0;                     // +0xF4
    this[0x3E] = 0;                     // +0xF8
    this[0x3F] = 0;                     // +0xFC
    this[0x40] = 0;                     // +0x100
    this[0x41] = gValA;                // +0x104
    this[0x42] = 0;                     // +0x108
    this[0x43] = 0;                     // +0x10C
    this[0x44] = 0;                     // +0x110
    this[0x45] = 0;                     // +0x114
    this[0x46] = gValA;                // +0x118
    this[0x47] = 0;                     // +0x11C
    this[0x48] = 0;                     // +0x120
    this[0x49] = 0;                     // +0x124
    this[0x4A] = 0;                     // +0x128
    this[0x4B] = gValA;                // +0x12C

    // Overwrite the initial magic markers with random values
    this[0x1E] = randomVal;            // +0x78
    this[0x1D] = randomVal;            // +0x74
    this[0x1C] = randomVal;            // +0x70
    this[0x1B] = randomVal;            // +0x6C

    // Second call to random seed initializer
    FUN_005e3130();

    return this;
}