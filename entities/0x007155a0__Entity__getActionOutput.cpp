// FUNC_NAME: Entity::getActionOutput
uint __thiscall Entity::getActionOutput(Entity* this, uint input1, uint input2, int flag)
{
    uint result;
    // +0xC is m_flags
    if ((*(uint*)((char*)this + 0xC) >> 1 & 1) != 0) {
        // Bit 1 set: extract bits 9..? and shift left 8
        return (*(uint*)((char*)this + 0xC) >> 9) << 8;
    }
    result = FUN_00713960(input1, input2);
    if (((flag == 0) && (result != 1)) && (result != 2)) {
        return result & 0xffffff00;
    }
    result = FUN_007151e0(input1, input2, flag, 0);
    return result;
}