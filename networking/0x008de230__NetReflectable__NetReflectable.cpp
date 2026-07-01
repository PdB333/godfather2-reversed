// FUNC_NAME: NetReflectable::NetReflectable

void __fastcall NetReflectable::NetReflectable(NetReflectable* this) // at address 0x008de230
{
    // Set primary vtable
    this->vfptr = (void*)&PTR_FUN_00d7ea28; // +0x00

    // Set reflection/interface tables
    this->reflectionTable1 = (void*)&PTR_LAB_00d7ea18; // offset +0x3C (0xf * 4)
    this->reflectionTable2 = (void*)&PTR_LAB_00d7ea14; // offset +0x48 (0x12 * 4)
    this->reflectionTable3 = (void*)&PTR_LAB_00d7ea10; // offset +0x50 (0x14 * 4)
    this->reflectionTable4 = (void*)&PTR_LAB_00d7e9b0; // offset +0x54 (0x15 * 4)
    this->reflectionTable5 = (void*)&PTR_LAB_00d7e948; // offset +0x58 (0x16 * 4)

    // Initialize sub-object at offset 0x190 (100 DWORDs from this)
    FUN_00408310(reinterpret_cast<undefined4*>(&this[100])); // sub-object constructor

    // Static initialization for module
    FUN_008d8620();
}