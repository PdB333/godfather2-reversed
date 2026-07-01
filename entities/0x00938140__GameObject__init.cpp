// FUNC_NAME: GameObject::init
// Address: 0x00938140
// Role: Initializes a GameObject by calling base class init and registering with a global manager at offset 0x54 (likely a component or callback slot).

void __thiscall GameObject::init(GameObject* this)
{
    // Call base class initialization (likely common setup)
    FUN_005c1740();

    // Register this object with the global manager at DAT_00d8a36c.
    // The manager is passed a pointer to the object's member at offset +0x54,
    // along with four zero parameters (probably flags or default values).
    FUN_005c01d0(&DAT_00d8a36c, this + 0x54, 0, 0, 0, 0);
}