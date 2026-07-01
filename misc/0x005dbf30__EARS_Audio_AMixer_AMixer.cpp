// Xbox PDB: EARS::Audio::AMixer::AMixer
// FUNC_NAME: MixAutomationPool::initializePool
void MixAutomationPool::initializePool()
{
    // +0x00 vtable pointer
    this->vtable = (void*)&PTR_FUN_00e3f2e0;
    // +0x04 unknown1
    this->field_04 = 0;
    // +0x08 unknown2
    this->field_08 = 0;
    // +0x0C unknown3
    this->field_0C = 0;
    // +0x14 freeListHead (previous head from global)
    this->freeListHead = DAT_012054b8;
    // store this object into global singleton pointer
    DAT_01223508 = this;
    // +0x18 debug name string
    this->debugName = "MixAutomationPool";
    // update global free list head to point to pool start (at +0x10)
    DAT_012054b8 = &this->field_10;
    // +0x1C unknown4
    this->field_1C = 0;
    // +0x20 unknown5
    this->field_20 = 0;
    // +0x24 unknown6
    this->field_24 = 0;
    // +0x28 pool capacity (200 blocks)
    this->capacity = 200;
    // +0x2C unknown7
    this->field_2C = 0;
    // +0x30 allocation alignment (4 bytes)
    this->alignment = 4;
    // +0x34 flags? (1 might indicate valid)
    this->flags = 1;
    // +0x3C element size (0x68 = 104 bytes)
    this->elementSize = 0x68;
    // +0x40 unknown8
    this->field_40 = 0;
    // +0x44 unknown9
    this->field_44 = 0;
    // +0x38 element size duplicate? (same value)
    this->elementSizeDuplicate = 0x68;
    // +0x10 secondary vtable pointer (set last, possibly for multiple inheritance)
    this->secondaryVtable = (void*)&PTR_FUN_00e3f2e8;

    // initialise pool internal structures (allocate memory, set up free blocks)
    FUN_005de200();
}