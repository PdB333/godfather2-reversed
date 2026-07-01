// FUNC_NAME: Transform::initFromParams
undefined4 * __thiscall Transform::initFromParams(undefined4 *this, undefined4 param_2, undefined4 param_3, undefined4 param_4,
                                                   undefined4 param_5, undefined4 param_6, undefined4 param_7,
                                                   undefined4 *param_8, undefined4 param_9, undefined4 param_10,
                                                   undefined4 param_11, undefined4 param_12, undefined4 param_13,
                                                   undefined4 param_14)
{
    undefined4 local_20;
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;

    // Set first 6 fields directly from parameters
    this[0] = param_2;   // +0x00: field0
    this[3] = param_5;   // +0x0C: field3
    this[1] = param_3;   // +0x04: field1
    this[5] = param_7;   // +0x14: field5
    this[4] = param_6;   // +0x10: field4
    this[2] = param_4;   // +0x08: field2

    // Set fields 9-14 directly from parameters
    this[9] = param_9;   // +0x24: field9
    this[0xB] = param_11; // +0x2C: field11
    this[0xD] = param_13; // +0x34: field13
    this[10] = param_10;  // +0x28: field10
    this[0xC] = param_12; // +0x30: field12
    this[0xE] = param_14; // +0x38: field14

    // Copy 3 values from param_8 and normalize/transform them
    local_20 = param_8[0];
    local_1c = param_8[1];
    local_18 = param_8[2];
    local_14 = 0; // padding or unused
    FUN_0056afa0(&local_20, &local_20); // in-place normalization/transformation

    // Store the processed values into fields 6-8
    this[6] = local_20; // +0x18: field6
    this[7] = local_1c; // +0x1C: field7
    this[8] = local_18; // +0x20: field8

    return this;
}