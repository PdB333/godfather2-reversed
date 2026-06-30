// FUNC_NAME: clearFlagBit1
void __fastcall clearFlagBit1(void* thisPtr)
{
    // Clear bit 1 (value 2) of flags field at offset +0x1c
    *(uint32_t*)((uint8_t*)thisPtr + 0x1c) &= 0xfffffffd;
}