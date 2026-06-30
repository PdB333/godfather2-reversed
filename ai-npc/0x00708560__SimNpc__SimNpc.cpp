// FUNC_NAME: SimNpc::SimNpc
SimNpc* __thiscall SimNpc::SimNpc(SimNpc* this, void* param_2)
{
    // Allocate or configure a buffer of size 0x4000
    FUN_0046e6b0(param_2, 0x4000); // e.g. EA::Memory::allocate

    // Set vtable pointer (first field)
    this->m_pVTable = (void*)&PTR_FUN_00d61210;

    // Additional virtual table / interface pointers
    this->m_pUnknownVtable1 = (void*)&PTR_LAB_00d61200; // offset 0x3C
    this->m_pUnknownVtable2 = (void*)&PTR_LAB_00d611fc; // offset 0x48
    this->m_pUnknownVtable3 = (void*)&PTR_LAB_00d611f8; // offset 0x50
    this->m_pUnknownVtable4 = (void*)&PTR_LAB_00d61198; // offset 0x54
    this->m_pUnknownVtable5 = (void*)&PTR_LAB_00d61130; // offset 0x58

    // Clear many fields (offsets 0x60 to 0x99)
    this->m_field_0x60 = 0;
    this->m_field_0x61 = 0;
    this->m_debugMarker1 = 0xbeefbeef; // offset 0x63? Actually index 99 => offset 0x18C
    this->m_debugMarker2 = 0xeac15a55; // offset 0x190
    this->m_debugMarker3 = 0x91100911; // offset 0x194
    this->m_debugMarker4 = 0xbadbadba; // offset 0x188
    // ... repeated pattern
    this->m_debugMarker5 = 0xbadbadba; // offset 0x198
    this->m_debugMarker6 = 0xbeefbeef; // offset 0x19C
    this->m_debugMarker7 = 0xeac15a55; // offset 0x1A0
    this->m_debugMarker8 = 0x91100911; // offset 0x1A4

    // Zero a block of fields (offsets 0x1B8 to 0x254)
    this->m_field_0x6e = 0;
    this->m_field_0x6f = 0;
    this->m_field_0x70 = 0;
    this->m_field_0x71 = 0;
    this->m_field_0x74 = 0; // flags field
    this->m_field_0x78 = 0;
    // ... many more zeroes
    this->m_field_0x84 = 0;
    this->m_ptrToSomeList = 0; // offset 0x214, initially zero
    // ... more zeroes until offset 0x268

    // Set debug markers at offset 0x2AC (0xAB*4), 0x2B0, 0x2B4, 0x2B8
    this->m_debugMarker9 = 0xbadbadba; // offset 0x2AC
    this->m_debugMarker10 = 0xbeefbeef; // offset 0x2B0
    this->m_debugMarker11 = 0xeac15a55; // offset 0x2B4
    this->m_debugMarker12 = 0x91100911; // offset 0x2B8

    // More zeroes and a sentinel -1
    this->m_field_0x2BC = 0;
    this->m_field_0x2C0 = 0;
    this->m_field_0x2C4 = 0;
    this->m_field_0x2C8 = 0;
    this->m_field_0x2CC = (int)0xFFFFFFFF; // -1, sentinel

    // Global initialization call
    FUN_00481530(); // e.g. InputManager::initialize or similar

    // If the list pointer is non-null, release it
    if (this->m_ptrToSomeList != 0) {
        FUN_004daf90(this->m_ptrToSomeList); // destruction
        this->m_ptrToSomeList = 0;
    }

    // Modify flags at offset 0x1D0
    this->m_flags &= 0xFFFFE8FF; // clear bits
    this->m_flags |= 0x8800;      // set bits
    // Set other fields
    this->m_global1 = DAT_00d5eee4; // offset 0x26C
    this->m_global2 = 0;           // offset 0x270
    this->m_global3 = DAT_00e44744; // offset 0x274

    // More flag modifications
    this->m_flags |= 0x12;         // set bits
    *(short*)((char*)this + 0x1D4) = 8; // offset 0x1D4, short
    *(char*)((char*)this + 0x1A8) = 0;  // offset 0x1A8, byte

    this->m_flags |= 0x40;         // set bit
    *(short*)((char*)this + 0x1D4) &= 0xFFFE; // clear LSB

    this->m_flags &= 0xFFFFFF7F;  // clear bit 7

    // Clear more fields
    this->m_field_0x158 = 0;      // offset 0x158
    this->m_field_0x298 = 0;      // offset 0x298
    this->m_field_0x2A0 = 0;      // offset 0x2A0
    this->m_field_0x1B0 = 0;      // offset 0x1B0
    this->m_field_0x1B4 = 0;      // offset 0x1B4
    *(short*)((char*)this + 0x1D4) = 0; // clear short at 0x1D4

    return this;
}