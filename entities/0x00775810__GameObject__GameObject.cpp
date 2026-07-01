// FUNC_NAME: GameObject::GameObject
// Constructor at 0x00775810. Performs base initialization and optional extra setup based on a flag.
uint32_t __thiscall GameObject::GameObject(GameObject* this, uint8_t initFlags)
{
    // Call base class constructor or common initializer (FUN_00774f30)
    baseConstructor(this);
    // If the low bit is set, perform additional initialization (FUN_00624da0)
    if (initFlags & 1) {
        extraInitialize(this);
    }
    return (uint32_t)this;
}