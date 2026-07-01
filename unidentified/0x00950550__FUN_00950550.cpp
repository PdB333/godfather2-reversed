// FUNC_NAME: UnknownClass::setActionContext
void __thiscall setActionContext(int this_ptr, int param2, int param3)
{
    *(int *)(this_ptr + 0x154) = param2;  // +0x154: likely target or context ID
    *(int *)(this_ptr + 0x164) = param3;  // +0x164: action or state value
    *(int *)(this_ptr + 0x178) = 0;       // +0x178: zero out a related counter or flag
}