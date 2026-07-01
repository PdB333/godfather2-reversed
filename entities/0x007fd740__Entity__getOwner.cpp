// FUNC_NAME: Entity::getOwner
int __fastcall Entity::getOwner(Entity* this)
{
    // +0xff8: flag indicating if this is the root owner (1 = self is owner)
    // +0xff0: pointer to owner's internal structure (offset by 0x48 from actual owner base)
    if (*(char*)((int)this + 0xff8) != 1)
    {
        if (*(int*)((int)this + 0xff0) != 0)
        {
            // Subtract 0x48 to get the actual owner object base
            return *(int*)((int)this + 0xff0) - 0x48;
        }
        return 0;
    }
    return (int)this;
}