// FUNC_NAME: GameObject::GameObject
undefined4 __thiscall GameObject::GameObject(GameObject* this, byte allocFlag) {
    // Call base class constructor (likely BaseObject::BaseObject)
    FUN_0075a550();
    // If the lower bit of allocFlag is set, the object was heap-allocated,
    // so we must call the deallocation routine (operator delete or similar)
    if ((allocFlag & 1) != 0) {
        FUN_00624da0(this);
    }
    return this;
}