// FUNC_NAME: GameObject::GameObject(bool)
GameObject* __thiscall GameObject::GameObject(byte flags)
{
    // Call base class constructor at 0x0049c640
    this->baseConstructor();
    // If flag bit 0 set, perform additional initialization (at 0x009c8eb0)
    if (flags & 1)
    {
        this->postConstruct();
    }
    return this;
}