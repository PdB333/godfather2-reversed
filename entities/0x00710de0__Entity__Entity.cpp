// FUNC_NAME: Entity::Entity
undefined4 __thiscall Entity::Entity(byte initFlags)
{
    // Call base class constructor (FUN_00710cd0)
    GameObject::GameObject();

    // If bit 0 of initFlags is set, perform additional initialization with size 300
    if ((initFlags & 1) != 0)
    {
        AllocateResource(this, 300); // FUN_0043b960
    }

    return this;
}