// FUNC_NAME: ModuleBase::~ModuleBase
// Address: 0x0077b650 - Destructor for a module/component class. Cleans up four pointer member fields and resets a global active flag.

void __fastcall ModuleBase::~ModuleBase(ModuleBase* thisClass)
{
    // Switch vtable to the derived class vtable (likely for correct cleanup order in multiply-inherited hierarchies)
    *reinterpret_cast<void**>(thisClass) = &PTR_FUN_00d6854c; // Derived vtable offset

    // Deallocate pointer at +0x28 (uint[10]) - e.g., an array or subobject
    if (thisClass->field_0x28 != nullptr) {
        FUN_009c8f10(thisClass->field_0x28); // memoryDeallocate
    }

    // Deallocate pointer at +0x1C (uint[7])
    if (thisClass->field_0x1C != nullptr) {
        FUN_009c8f10(thisClass->field_0x1C);
    }

    // Deallocate pointer at +0x10 (uint[4])
    if (thisClass->field_0x10 != nullptr) {
        FUN_009c8f10(thisClass->field_0x10);
    }

    // Deallocate pointer at +0x04 (uint[1])
    if (thisClass->field_0x04 != nullptr) {
        FUN_009c8f10(thisClass->field_0x04);
    }

    // Switch vtable to base class vtable (finalize destruction)
    *reinterpret_cast<void**>(thisClass) = &PTR_LAB_00d68548; // Base vtable offset

    // Reset global active flag; indicates this module is no longer in use
    DAT_0112af28 = 0; // g_moduleActive
}