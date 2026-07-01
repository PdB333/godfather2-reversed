// FUNC_NAME: GameObject::GameObject
// Function address: 0x008ca930
// Identified role: Constructor that calls a base initialization routine and sets the vtable pointer.

GameObject* __thiscall GameObject::GameObject(GameObject* this, void* baseInitParam1, void* baseInitParam2)
{
    // Call base class constructor or initialization with two parameters
    baseInitFunction(baseInitParam1, baseInitParam2);

    // Set vtable pointer to the class-specific virtual function table
    *reinterpret_cast<void**>(this) = reinterpret_cast<void*>(0x00d7c0c8);

    return this;
}