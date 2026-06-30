// FUNC_NAME: Entity::getOwner

int __thiscall Entity::getOwner(Entity* this)
{
    // dereference pointer at +0x1c78; if non-null, subtract 0x48 to get parent container
    if (*(int*)((char*)this + 0x1c78) != 0)
    {
        return *(int*)((char*)this + 0x1c78) - 0x48;
    }
    return 0;
}