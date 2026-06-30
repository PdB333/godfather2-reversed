// FUNC_NAME: Entity::getConditionalMask
uint Entity::getConditionalMask(uint mask)
{
    int unused = 0;
    bool condition = (this->*reinterpret_cast<bool (__thiscall Entity::*)(uint, int*)>(*(uint**)(this))[4])(mask, &unused);
    return condition ? mask : 0;
}