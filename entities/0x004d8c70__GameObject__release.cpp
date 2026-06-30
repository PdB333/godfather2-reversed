// FUNC_NAME: GameObject::release
int __thiscall GameObject::release(byte flags)
{
    // +0x14: pointer to a child object in a hierarchy
    GameObject* child = *(GameObject**)(this + 0x14);

    // Recursively destroy the child with full deletion flags (1)
    if (child != nullptr)
    {
        child->release(1);
    }

    // If the lowest bit of flags is set, deallocate this object
    if ((flags & 1) != 0)
    {
        // Custom memory deallocation at 0x009c8eb0
        MemoryDeallocate(this);
    }

    return (int)this;
}