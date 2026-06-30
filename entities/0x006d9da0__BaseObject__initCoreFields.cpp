// FUNC_NAME: BaseObject::initCoreFields
void __thiscall BaseObject::initCoreFields(BaseObject* this)
{
    // Initialize several fields common to base objects
    // +0x54: Set to a global value (likely a pointer or constant)
    *(int*)((uintptr_t)this + 0x54) = g_SomeGlobal;  // _DAT_00d5780c
    // +0x50: Copy from field at +0x24 (likely a pointer to owner/parent)
    *(int*)((uintptr_t)this + 0x50) = *(int*)((uintptr_t)this + 0x24);
    // +0x58: Reset to zero
    *(int*)((uintptr_t)this + 0x58) = 0;
    // +0x08: Byte flag set to false
    *(char*)((uintptr_t)this + 0x08) = 0;
}