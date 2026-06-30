// FUNC_NAME: Entity::isType
bool __thiscall Entity::isType(int *thisPtr, int typeId)
{
    int vtableTypeId;
    vtableTypeId = (**(code **)(*thisPtr + 0x1e8))(); // vtable[0x1e8/4] = getTypeId()
    return typeId == vtableTypeId;
}