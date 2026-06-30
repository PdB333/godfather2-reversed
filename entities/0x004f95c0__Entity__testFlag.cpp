// FUNC_NAME: Entity::testFlag
uint Entity::testFlag(uint flag)
{
    uint unused;
    bool isSet = (**(code **)(*(int*)this + 0x10))(flag, &unused);
    return isSet ? flag : 0;
}