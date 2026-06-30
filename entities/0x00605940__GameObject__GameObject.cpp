// FUNC_NAME: GameObject::GameObject
// Function address: 0x00605940
// Constructor for base GameObject. Calls internal initializer and optionally registers with global manager.
__thiscall GameObject* GameObject::GameObject(GameObject* this, byte shouldRegister)
{
    this->initialize();          // FUN_00605960 - performs base initialization
    if (shouldRegister & 1)
    {
        this->registerWithManager(); // FUN_009c8eb0 - registers this instance with a manager
    }
    return this;
}