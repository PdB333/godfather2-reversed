// FUNC_NAME: GameObject::GameObject
// Address: 0x008f3510
// Role: Object constructor with allocation flag (likely used for placement new or copy construction)

__thiscall GameObject* GameObject::GameObject(GameObject* this, byte flags)
{
    // Call base class constructor (FUN_008f2020)
    GameObject::baseConstructor(this);
    // If flag bit 0 is set, perform additional cleanup or destruction (FUN_009c8eb0)
    if (flags & 1)
    {
        GameObject::destructorOrFree(this);
    }
    return this;
}