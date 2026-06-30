// FUNC_NAME: MessageStream::MessageStream

uint __thiscall MessageStream::MessageStream(MessageStream* this, uint param2) {
    uint hashVal;
    char* str;
    uint ch;
    int hash;

    // Call base class constructor
    BaseClassConstructor(param2);

    // Set vtable
    this->vtable = &PTR_FUN_00e3334c;          // +0x00

    // Set function pointers / interface pointers
    this->field_0x3C = &PTR_LAB_00e33368;      // +0x3C
    this->field_0x48 = &PTR_LAB_00e33378;      // +0x48

    // Initialize stream state fields to zero
    this->field_0x50 = 0;                      // +0x50
    *(short*)((int)this + 0x54) = 0;           // +0x54 (2 bytes)
    *(short*)((int)this + 0x56) = 0;           // +0x56 (2 bytes)
    this->field_0x58 = 0;                      // +0x58
    *(short*)((int)this + 0x5C) = 0;           // +0x5C
    *(short*)((int)this + 0x5E) = 0;           // +0x5E

    // Fill buffer marker area with sentinel values
    this->field_0x60 = 0xBADBADBA;             // +0x60
    this->field_0x64 = 0xBEEFBEEF;             // +0x64
    this->field_0x68 = 0xEAC15A55;             // +0x68
    this->field_0x6C = 0x91100911;             // +0x6C

    // Fill two 16-byte blocks (each 4 ints) with the same sentinels
    uint* block = &this->field_0x70;           // start at +0x70
    int count = 2;
    do {
        *block = 0xBADBADBA;
        block[1] = 0xBEEFBEEF;
        block[2] = 0xEAC15A55;
        block[3] = 0x91100911;
        block += 4;                            // advance 16 bytes
        count--;
    } while (count >= 0);

    // Zero out two bytes at the end of the structure
    *(byte*)((int)this + 0x90) = 0;            // +0x90
    *(byte*)((int)this + 0x91) = 0;            // +0x91

    // Static initialization (likely register stream callbacks)
    FUN_0047fde0();

    // Clear the sentinel values (now overwritten with zeros)
    this->field_0x6C = 0;                      // +0x6C
    this->field_0x68 = 0;                      // +0x68
    this->field_0x64 = 0;                      // +0x64
    this->field_0x60 = 0;                      // +0x60

    // Clear additional space – covers offsets 0x68..0x8C
    // Starting from +0x70 (this->field_0x70), clear 8 ints in two groups
    uint* clearPtr = &this->field_0x70;        // start at +0x70
    int clearCount = 2;
    do {
        clearPtr[1] = 0;   // +4
        clearPtr[0] = 0;
        clearPtr[-1] = 0;  // -4
        clearPtr[-2] = 0;  // -8
        clearPtr += 4;     // advance 16 bytes
        clearCount--;
    } while (clearCount != 0);

    // Compute hash for "iMsgStreamSetCommandComplete" and register
    str = "iMsgStreamSetCommandComplete";
    hash = 0;
    ch = 0x69; // 'i' (first character)
    do {
        str++;
        if (ch - 0x41 < 0x1A) {               // uppercase to lowercase
            ch += 0x20;
        }
        hash = hash * 0x1003F + ch;
        ch = (uint)(byte)*str;
    } while (*str != 0);
    FUN_00408260(&DAT_0120eb00, hash);         // register hash to static global

    // Compute hash for "iMsgStreamSetLoadStarted" and register
    str = "iMsgStreamSetLoadStarted";
    hash = 0;
    ch = 0x69; // 'i'
    do {
        str++;
        if (ch - 0x41 < 0x1A) {
            ch += 0x20;
        }
        hash = hash * 0x1003F + ch;
        ch = (uint)(byte)*str;
    } while (*str != 0);
    FUN_00408260(&DAT_0120eaf8, hash);         // register hash to static global

    return (uint)this;
}