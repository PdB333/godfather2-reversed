//FUNC_NAME: enableFeature
// Function address: 0x00977290
// Role: Enables a feature by setting a flag and calling an initialization function.
// Offsets: this+0x60 = flags (bit 8 = 0x100), global+0x10 = globalFlags (bit 2 = 0x4)

void __thiscall enableFeature(void* thisPtr)
{
    uint flags = *(uint*)((char*)thisPtr + 0x60);
    if ((flags >> 8 & 1) == 0) {
        initializeFeature(); // FUN_00911fd0
        *(uint*)((char*)thisPtr + 0x60) = flags | 0x100;
        *(uint*)(*(int*)0x011298d4 + 0x10) |= 4;
    }
}