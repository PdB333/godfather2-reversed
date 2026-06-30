// FUNC_NAME: CallVirtualOnGlobalObject
void CallVirtualOnGlobalObject(void* param_1)
{
    // DAT_01223510 points to a global object whose vtable pointer is at offset 0.
    // Vtable entry at offset 0xD4 (index 53) is a function called with param_1 as the sole argument.
    (*(void (**)(void*))(*(int*)0x01223510 + 0xD4))(param_1);
}