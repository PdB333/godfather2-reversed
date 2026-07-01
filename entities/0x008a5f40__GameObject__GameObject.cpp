//FUNC_NAME: GameObject::GameObject
// Address: 0x008a5f40
// Constructor for a game object. Calls base constructor and optionally performs additional initialization based on a flag.
GameObject* __thiscall GameObject::GameObject(GameObject* this, byte initFlag) {
    // Call base class constructor (FUN_008a5bf0)
    BaseClass::BaseClass(this);
    if (initFlag & 1) {
        // Additional initialization (FUN_009c8eb0)
        this->initialize();
    }
    return this;
}