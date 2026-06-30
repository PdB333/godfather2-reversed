// FUNC_NAME: DispatchVirtualWithFallback
void __thiscall DispatchVirtualWithFallback(void* self, uint32 param2) {
    // self is pointer to object with layout:
    // +0x00: vtable pointer (first entry is default function)
    // +0x14: optional override function pointer (can be null)

    typedef void (__thiscall *OverrideFunc)(void* self, uint32 param);
    typedef void (__thiscall *DefaultFunc)(uint32 param); // this implicitly from ECX, same as self

    OverrideFunc overrideFp = *(OverrideFunc*)((uint8*)self + 0x14);
    if (overrideFp != nullptr) {
        overrideFp(self, param2);
        return;
    }

    // Fallback to vtable's first function (index 0)
    void** vtable = *(void***)self;
    DefaultFunc defaultFp = (DefaultFunc)vtable[0];
    defaultFp(param2);
}