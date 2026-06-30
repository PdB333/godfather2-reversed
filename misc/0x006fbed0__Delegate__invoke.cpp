// FUNC_NAME: Delegate::invoke
// Address: 0x006fbed0
// Role: Invokes a stored function pointer if it is non-null.
// The function pointer is stored at offset +0x18 from this.
void __thiscall Delegate::invoke(void* param_1, uint32_t param_2) {
    // Fetch the stored function pointer at offset 0x18
    void (*funcPtr)(void*, uint32_t) = *(void(**)(void*, uint32_t))((char*)param_1 + 0x18);
    if (funcPtr != nullptr) {
        funcPtr(param_1, param_2);
    }
}