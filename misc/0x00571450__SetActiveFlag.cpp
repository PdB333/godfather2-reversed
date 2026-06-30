// FUNC_NAME: SetActiveFlag
uint __thiscall SetActiveFlag(char param1)
{
    char cVar1;
    uint result;

    if (this == 0) {
        return (uint)(char)in_EAX & 0xFFFFFF00;
    }
    if (param1 == '\0') {
        *(int *)(this + 4) &= 0xFFFFF7FF;  // clear bit 0x800
    } else {
        *(int *)(this + 4) |= 0x800;       // set bit 0x800 (+4 flags)
    }
    cVar1 = FUN_005795f0();               // some global condition check
    if (cVar1 != '\0') {
        result = FUN_00578620(unaff_EDI, 2); // handle event with code 2
        return result;
    }
    // call virtual function at vtable index 1 (offset +4)
    result = (*(code **)(*(int *)this + 4))();
    return result;
}