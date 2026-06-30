// FUNC_NAME: GameManager::GameManager
void __fastcall GameManager::GameManager(void *this, void *parent)
{
    // vtable setup: first set to base vtable, then override
    this->vtable = &PTR_FUN_00e3a7a8;          // +0x00: vtable pointer
    this->field_4 = &PTR_LAB_00e3a844;         // +0x04: secondary vtable or data
    this->field_8 = &PTR_LAB_00e3a840;         // +0x08: another vtable pointer
    this->field_0C = 0;                        // +0x0C
    this->field_10 = 0;                        // +0x10
    this->field_1C = 0;                        // +0x1C
    this->field_20 = 0;                        // +0x20
    this->field_24 = 0;                        // +0x24
    this->parentObject = parent;               // +0x28: store parent pointer
    this->field_2C = 0x14;                     // +0x2C: some constant
    this->field_30 = 0;                        // +0x30
    this->field_34 = 0;                        // +0x34
    this->field_38 = 0;                        // +0x38
    this->field_3C = 0;                        // +0x3C
    this->field_40 = 0;                        // +0x40
    this->field_44 = 0;                        // +0x44
    this->field_48 = 1;                        // +0x48: flag
    this->field_4C = 0;                        // +0x4C
    this->field_50 = 0;                        // +0x50
    this->field_54 = 0;                        // +0x54
    this->field_58 = 0;                        // +0x58

    FUN_00ae9710();                            // initialize subsystem A

    this->field_11C = 0;                       // +0x11C
    this->field_120 = 0;                       // +0x120
    this->field_10 = 0;                        // +0x10 (redundant?)
    *(byte *)(this + 0x14) = 0;                // +0x14: byte field
    this->field_EC = 0x80;                     // +0xEC: some size/count

    FUN_00adbf50();                            // setup B

    this->field_E8 = &this->field_5C;          // +0xE8: pointer to offset 0x5C
    this->field_114 = 1;                       // +0x114: flag

    // Call a virtual function on parent object (offset 8 in its vtable)
    (*(void (**)(void))(*(int *)parent + 8))();

    thunk_FUN_00aedbc0(FUN_005677c0, &LAB_005677f0); // register callback
    thunk_FUN_00af0c90();                      // finalize initialization

    void *obj = (void *)FUN_00ad8270();        // get some manager
    (*(void (**)(void))(*(int *)obj + 0))();   // call its first virtual function (likely constructor/init)
}