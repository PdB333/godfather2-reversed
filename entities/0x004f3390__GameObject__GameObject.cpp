// FUNC_NAME: GameObject::GameObject

__thiscall GameObject::GameObject(byte flags)
{
    // Call global base initializer (0x004f3850)
    baseInit();
    // If bit 0 is set, call extra initializer (0x009c8eb0)
    if (flags & 1) {
        extraInit(this);
    }
    return this;
}