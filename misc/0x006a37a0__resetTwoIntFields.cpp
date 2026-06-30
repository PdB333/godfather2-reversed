// FUNC_NAME: resetTwoIntFields
void __fastcall resetTwoIntFields(int *ptr) {
    // Zero out two consecutive 4-byte fields at offset 0x00 and 0x04
    ptr[0] = 0;
    ptr[1] = 0;
}