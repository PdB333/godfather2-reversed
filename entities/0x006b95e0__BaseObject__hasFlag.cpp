// FUNC_NAME: BaseObject::hasFlag
uint __thiscall BaseObject::hasFlag(int *this, uint mask)
{
    char result;
    int local_4;

    local_4 = 0;
    // Call virtual function at vtable+0x10 (index 4) to check the flag
    result = ((code *)(*(int *)this + 0x10))(mask, &local_4);
    // Return mask if flag is set, otherwise 0
    return -(uint)(result != '\0') & mask;
}