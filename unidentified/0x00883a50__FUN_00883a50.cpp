// FUNC_NAME: SomeClass::queryState
uint __thiscall SomeClass::queryState(int this, undefined4 param_2, undefined4 param_3, int param_4, undefined4 param_5)
{
    char cVar1;
    undefined4 uVar2;
    uint uVar3;
    
    switch (param_4 - 10)
    {
    case 0: // param_4 == 10
        // Return a bitfield from a structure pointed to by this+0x58, offset 0x1b94
        // Shift right 0x13 bits and mask with 0xffffff01
        return *(uint*)(*(int*)(this + 0x58) + 0x1b94) >> 0x13 & 0xffffff01;
    case 1: // param_4 == 11
        uVar3 = FUN_0045eec0(0x46f5c7b4);
        return uVar3;
    case 2: // param_4 == 12, falls through to default logic after switch
        break;
    case 3: // param_4 == 13
        // Compare global float / this->field_0x78 <= this->field_0x30
        if (DAT_00d76f64 / *(float*)(this + 0x78) <= *(float*)(this + 0x30))
            return 1;
        return 0;
    case 4: // param_4 == 14
        // Based on a state at this+0x50
        if (*(int*)(this + 0x50) != 0)
            return (uint)(*(int*)(this + 0x50) == 0x48);
        return 1;
    default:
        uVar3 = FUN_004ac640(param_2, param_3, param_4, param_5);
        return uVar3;
    }
    // For case 2: process after break
    uVar2 = FUN_00875b40(this + 0x5c); // Get something from object at this+0x5c
    if (*(int*)(this + 0x50) != 0)
    {
        cVar1 = FUN_0045ef10(uVar2);
        return (uint)(cVar1 == '\0'); // true if null char
    }
    cVar1 = FUN_0045ef10(uVar2);
    return (uint)(cVar1 == '\0');
}