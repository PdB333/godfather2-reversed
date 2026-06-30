// FUNC_NAME: checkDisabledFlag
void __fastcall checkDisabledFlag(int* param_1)
{
    // Check if bit 0x20000 (bit 17) is set at offset 0x10c of the object pointed to by *param_1
    // If set, return early (likely indicating a disabled state)
    if ((*(uint*)(*param_1 + 0x10c) & 0x20000) != 0) {
        return;
    }
    return;
}