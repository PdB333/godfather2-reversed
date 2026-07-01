// FUNC_NAME: applyConfigDefaults

extern void FUN_005c4630(void* dest, unsigned int size, const void* src, unsigned int extraParam);
extern unsigned char DAT_00e325c4[0x80]; // predefined default configuration block (128 bytes)

void __thiscall applyConfigDefaults(void* configData) {
    // Calls setup routine with config destination, size 0x80, default source, and field at +0xE4 (likely a subtype or identifier)
    FUN_005c4630(configData, 0x80, (const void*)&DAT_00e325c4, *(unsigned int*)((unsigned char*)this + 0xE4));
}