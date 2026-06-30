// FUNC_NAME: clearBooleanFlagAtOffset0x20
void __fastcall clearBooleanFlagAtOffset0x20(void* obj) {
    // Set boolean flag at offset 0x20 to false (0)
    *(uint8_t*)((uintptr_t)obj + 0x20) = 0;
}