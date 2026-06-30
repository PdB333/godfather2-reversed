// FUNC_NAME: Entity::getDataPointer
int __thiscall Entity::getDataPointer()
{
    // Offset 0x1BC - pointer to a component or data block (e.g. script data, inventory, etc.)
    return reinterpret_cast<int>(reinterpret_cast<char*>(this) + 0x1BC);
}