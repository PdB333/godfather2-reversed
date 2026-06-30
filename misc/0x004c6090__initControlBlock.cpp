// FUNC_NAME: initControlBlock
void __fastcall initControlBlock(uint64_t *param_1)
{
    // param_1 points to a control block structure (size >= 0x1C bytes)
    // Offsets:
    //   +0x00: qword0 (set to 0) – 8 bytes
    //   +0x08: qword1 (set to 0) – 8 bytes
    //   +0x10: field_10 (int32) set to DAT_00e445fc
    //   +0x14: field_14 (int32) set to DAT_00e445f8
    //   +0x18: field_18 (int32) set to 0x80000000 (e.g., large initial count or flag)
    *(int32_t *)(param_1 + 2) = DAT_00e445fc;   // param_1+2 offsets by 16 bytes
    *(int32_t *)((int)param_1 + 0x14) = DAT_00e445f8; // offset 0x14
    *(int32_t *)(param_1 + 3) = 0x80000000;     // param_1+3 offsets by 24 bytes
    *param_1 = 0;                               // clear first 8 bytes
    param_1[1] = 0;                             // clear next 8 bytes
    return;
}