// FUNC_NAME: AllocationBlock::AllocationBlock
void __thiscall AllocationBlock::AllocationBlock(AllocationBlock* this, uint param_2)
{
    // Call base class constructor (likely Entity or Object)
    BaseClass::BaseClass(param_2);

    // Set vtable pointer
    this->vtable = (void**)&PTR_FUN_00d5d94c; // +0x00

    // Set function pointers at offsets 0x3C and 0x48 (indices 0x0F and 0x12)
    this->funcPtrs[0] = &PTR_LAB_00d5d93c; // +0x3C
    this->funcPtrs[1] = &PTR_LAB_00d5d938; // +0x48

    // Initialize a block of zeroed fields (offsets 0x50 to 0x70)
    this->field_0x50 = 0; // +0x50
    *(uint16*)((uint8*)this + 0x54) = 0; // +0x54
    *(uint16*)((uint8*)this + 0x56) = 0; // +0x56
    this->field_0x58 = 0; // +0x58
    *(uint16*)((uint8*)this + 0x5E) = 0; // +0x5E
    this->field_0x60 = 0; // +0x60
    *(uint16*)((uint8*)this + 0x66) = 0; // +0x66
    this->field_0x68 = 0; // +0x68
    *(uint16*)((uint8*)this + 0x6E) = 0; // +0x6E
    this->field_0x70 = 0; // +0x70

    // Poison first block with sentinel values (0x74-0x80)
    this->sentinel1_0 = 0xBADBADBA; // +0x74
    this->sentinel1_1 = 0xBEEFBEEF; // +0x78
    this->sentinel1_2 = 0xEAC15A55; // +0x7C
    this->sentinel1_3 = 0x91100911; // +0x80

    // Generate random hash for first block
    uint hash1 = FUN_0042b400();  // Random/hash generator
    this->hash1 = hash1;          // +0x84

    // Clear first sentinel block (overwrite with zero)
    this->field_0x80 = 0; // +0x80 (was sentinel1_3)
    this->field_0x7C = 0; // +0x7C (was sentinel1_2)
    this->field_0x78 = 0; // +0x78 (was sentinel1_1)
    this->field_0x74 = 0; // +0x74 (was sentinel1_0)

    // Poison second block with sentinel values (0x8C-0x98)
    this->sentinel2_0 = 0xBADBADBA; // +0x8C
    this->sentinel2_1 = 0xBEEFBEEF; // +0x90
    this->sentinel2_2 = 0xEAC15A55; // +0x94
    this->sentinel2_3 = 0x91100911; // +0x98

    // Generate random hash for second block
    uint hash2 = FUN_0042b400();  // Random/hash generator
    this->hash2 = hash2;          // +0x9C

    // Store global value
    uint32 globalValue = DAT_00d5d934; // Global constant
    this->field_0xA0 = 0;              // +0xA0

    // Clear second sentinel block
    this->field_0x98 = 0; // +0x98 (was sentinel2_3)
    this->field_0x94 = 0; // +0x94 (was sentinel2_2)
    this->field_0x90 = 0; // +0x90 (was sentinel2_1)
    this->field_0x8C = 0; // +0x8C (was sentinel2_0)

    // Initialize remaining fields from globals
    this->globalField1 = globalValue;                    // +0xA4
    this->globalField2 = DAT_00d5d740;                   // +0xA8
    uint32 repeat = _DAT_00d5780c;                       // Global constant
    this->globalField3 = repeat;                         // +0xAC
    this->globalField4 = repeat;                         // +0xB0
    this->globalField5 = repeat;                         // +0xB4
    this->globalField6 = repeat;                         // +0xB8
    this->zeroField1 = 0;                                // +0xBC
    this->zeroField2 = 0;                                // +0xC0
    this->zeroField3 = 0;                                // +0xC4
    this->globalField7 = repeat;                         // +0xC8
    this->globalField8 = repeat;                         // +0xCC
    this->zeroField4 = 0;                                // +0xD0
    this->globalField9 = repeat;                         // +0xD4
    this->globalField10 = repeat;                        // +0xD8
    this->zeroField5 = 0;                                // +0xDC
    this->globalField11 = repeat;                        // +0xE0
    this->globalField12 = repeat;                        // +0xE4

    // Zero two trailing bytes
    *(uint8*)((uint8*)this + 0xE8) = 0;
    *(uint8*)((uint8*)this + 0xE9) = 0;
}