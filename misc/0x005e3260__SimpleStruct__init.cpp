// FUNC_NAME: SimpleStruct::init
void __fastcall SimpleStruct::init(int* param_1)
{
    // +0x00: active flag (set to 1)
    *param_1 = 1;
    // +0x04: count1 (set to 0)
    param_1[1] = 0;
    // +0x08: count2 (set to 0)
    param_1[2] = 0;
    // +0x0C: padding or unused byte (set to 0)
    *(uint8_t*)(param_1 + 3) = 0;
}