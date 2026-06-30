// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::EARSObject(void* this) {
    // +0x00: vtable pointer - set to base class vtable
    *(void**)this = (void*)&PTR_FUN_00e31080;

    // +0x04: pointer to a subobject that needs initialization
    initSubObject(*(void**)((char*)this + 4));

    // Update vtable to derived class vtable
    *(void**)this = (void*)&PTR_LAB_00e31084;

    // Reset global initialization flag
    g_initialized = 0;  // global at 0x012233a0
}