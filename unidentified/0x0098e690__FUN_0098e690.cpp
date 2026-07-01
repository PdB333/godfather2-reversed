// FUNC_NAME: SomeContainer::addItem
void __thiscall SomeContainer::addItem(int this, undefined4 param2, undefined4 param3, undefined4 param4, undefined4 param5, undefined4 param6, undefined4 param7)
{
    int iVar1;
    int local_4c [3];
    code *local_40;
    int local_3c;
    undefined4 local_38;
    undefined4 local_34;
    code *local_30;
    int local_2c;
    undefined4 local_28;
    undefined4 local_24;
    code *local_20;
    int local_1c;
    undefined4 local_18;
    undefined4 local_14;
    code *local_10;
    undefined4 local_8;
    undefined4 local_4;
    
    local_4c[0] = 0;
    local_4c[1] = 0;
    local_4c[2] = 0;
    local_40 = (code *)0x0;
    local_3c = 0;
    local_38 = 0;
    local_34 = 0;
    local_30 = (code *)0x0;
    local_2c = 0;
    local_28 = 0;
    local_24 = 0;
    local_20 = (code *)0x0;
    local_1c = 0;
    local_18 = 0;
    local_14 = 0;
    local_10 = (code *)0x0;
    FUN_004d3d90(param2);
    FUN_004d3d90(param3);
    FUN_004d3d90(param4);
    FUN_004d3d90(param5);
    iVar1 = *(int *)(this + 0x78); // +0x78: capacity
    local_4 = param6;
    local_8 = param7;
    if (*(int *)(this + 0x74) == iVar1) { // +0x74: current count
        if (iVar1 == 0) {
            iVar1 = 1;
        }
        else {
            iVar1 = iVar1 * 2;
        }
        FUN_0098e020(iVar1); // resize container
    }
    iVar1 = *(int *)(this + 0x74); // +0x74: current count
    *(int *)(this + 0x74) = iVar1 + 1;
    if (iVar1 * 0x4c + *(int *)(this + 0x70) != 0) { // +0x70: data pointer, each element 0x4c bytes
        FUN_0098df80(local_4c); // copy/initialize element at index iVar1
    }
    if (local_1c != 0) {
        (*local_10)(local_1c); // cleanup function pointers
    }
    if (local_2c != 0) {
        (*local_20)(local_2c);
    }
    if (local_3c != 0) {
        (*local_30)(local_3c);
    }
    if (local_4c[0] != 0) {
        (*local_40)(local_4c[0]);
    }
    return;
}