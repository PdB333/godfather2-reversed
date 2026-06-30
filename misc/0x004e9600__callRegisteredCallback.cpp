// FUNC_NAME: callRegisteredCallback
void __fastcall callRegisteredCallback(uint32_t param1, uint32_t param2)
{
    // DAT_012234c4 is a global pointer to a context structure (e.g., event dispatcher or manager).
    // The function pointer at offset +0x2C is checked and called if non-null.
    // Note: argument order is swapped - param2 becomes first arg, param1 becomes second.
    if (*(uint32_t*)(DAT_012234c4 + 0x2c) != 0)
    {
        (*(void (__fastcall*)(uint32_t, uint32_t))(DAT_012234c4 + 0x2c))(param2, param1);
    }
}