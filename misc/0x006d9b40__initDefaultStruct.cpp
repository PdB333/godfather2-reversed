// FUNC_NAME: initDefaultStruct
void __fastcall initDefaultStruct(undefined4 *param_1)
{
    // +0x00: field0
    *param_1 = DAT_00d5e288;
    // +0x04: field1
    param_1[1] = _DAT_00d5780c;
    // +0x08: field2
    param_1[2] = _DAT_00d5cf70;
    // +0x0C: field3 (same value as field2)
    param_1[3] = _DAT_00d5cf70;
    // +0x10: field4 through +0x20: field8 set to zero
    param_1[7] = 0;
    param_1[6] = 0;
    param_1[5] = 0;
    param_1[4] = 0;
    param_1[8] = 0;
}