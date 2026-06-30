// FUNC_NAME: computeBufferSize
// Function at 0x006b2340 calculates (field38 + field3c) * 20 + 96.
int __thiscall computeBufferSize(void* thisPtr) {
    int field38 = *(int*)((uint8_t*)thisPtr + 0x38); // +0x38: likely count or base offset
    int field3c = *(int*)((uint8_t*)thisPtr + 0x3c); // +0x3c: likely second count or element size
    return (field38 + field3c) * 20 + 96; // 96 = fixed header size? 20 = per-element size?
}