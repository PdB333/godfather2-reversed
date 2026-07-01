// FUNC_NAME: Entity::dispatchMethod
void __fastcall Entity::dispatchMethod(void* this) {
    // Check flag at offset +0x14 (param_1[5])
    if (*(int*)((char*)this + 0x14) != 0) {
        FUN_00782400(*(uint32_t*)this); // Call handler with first field (likely vtable/function pointer)
        return;
    }
    FUN_00782400(*(uint32_t*)this);
    return;
}