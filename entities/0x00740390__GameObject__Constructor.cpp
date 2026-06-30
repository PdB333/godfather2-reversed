// FUNC_NAME: GameObject::Constructor
GameObject* __thiscall GameObject::Constructor(GameObject* this, byte flags)
{
    // Call base initializer (FUN_0073fce0) – sets up common members
    GameObject::InitCommon(this);
    if (flags & 1) {
        // Perform extended setup (FUN_00624da0) – e.g., allocate resources or register
        GameObject::InitExtended(this);
    }
    return this; // Standard constructor return
}