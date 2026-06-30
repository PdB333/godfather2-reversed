// FUNC_NAME: Entity::setSubObjectField(0x54A90)
void __thiscall Entity::setSubObjectField(int thisPtr, int value)
{
    // thisPtr + 0x18: pointer to a sub-object (e.g., state component)
    int* subObject = *(int**)(thisPtr + 0x18);
    // subObject + 0x8: some field to set (e.g., flags, state ID)
    subObject[2] = value;
}