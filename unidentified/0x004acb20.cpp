// FUN_NAME: GameObject::GameObject
GameObject* __thiscall GameObject::GameObject(GameObject* this, byte flags)
{
    // Call base class initializer (common for all instances)
    this->initBase();
    
    // If the least significant bit of flags is set, perform additional setup
    if (flags & 1) {
        this->setupFeature();
    }
    
    return this;
}