// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Constructor for the main game manager singleton.
// Called from 0x0091f920. Sets up vtable, internal tables, and default state.

void __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this)
{
    // Call base class constructor / init (e.g. EARS::Framework::Object?)
    sub_5BF9B0();

    // vtable pointer (offset 0x00)
    this->vfptr = (void **)&PTR_FUN_00d8c6c8;

    // Pointer table at +0x10
    this->field_0x10 = (void *)&PTR_LAB_00d8c6a4;

    // Primary data pointer table (offset +0x4C) – overwritten later
    this->pDataTable1 = (void *)&PTR_LAB_00d8c4e0;

    // Final table pointer (offset +0x4C)
    this->pDataTable1 = (void *)&PTR_LAB_00d8c6a0;

    // Various function pointer tables set to a common data block (offset 0x84, 0x108, 0x18C, 0x210)
    this->pTableA[0] = (void *)&PTR_LAB_00d83b18;   // +0x84
    this->pTableA[1] = (void *)&PTR_LAB_00d83b18;   // +0x108
    this->pTableA[2] = (void *)&PTR_LAB_00d83b18;   // +0x18C
    this->pTableA[3] = (void *)&PTR_LAB_00d83b18;   // +0x210

    // Byte flags / state at +0x2AD, +0x2C0, +0x2C1
    this->byte_0x2AD = 0;
    this->byte_0x2C0 = 0;
    this->byte_0x2C1 = 0;

    // Zero out a block of 4-byte fields (0x50–0x74)
    this->field_0x50 = 0;
    this->field_0x54 = 0;
    this->field_0x58 = 0;
    this->field_0x5C = 0;
    this->field_0x60 = 0;
    this->field_0x64 = 0;
    this->field_0x68 = 0;
    this->field_0x6C = 0;
    this->field_0x70 = 0;
    this->field_0x74 = 0;

    // Index/state field at +0x78
    this->field_0x78 = 0;

    // Sentinel or invalid index (offset +0x7C)
    this->someInvalidIndex = -1;

    // IDs or counters at +0x2B0, +0x2B4, +0x2B8, +0x2BC
    this->field_0x2B0 = 0;
    this->field_0x2B4 = 0;
    this->field_0x2B8 = 0;
    this->field_0x2BC = 0;

    // Unknown count/limit at +0x2C4
    this->someCount = 6;

    // Store singleton pointer in global
    g_pGodfatherGameManager = this;
}