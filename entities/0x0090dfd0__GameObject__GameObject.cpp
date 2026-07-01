// FUNC_NAME: GameObject::GameObject
// Constructor for a game object, takes a flag for optional initialization.
// Calls base constructor first, conditionally performs additional setup.
// param_1: this pointer (returned)
// param_2: flags (bit 0 triggers extra initialization)

class GameObject {
public:
    GameObject(byte flags);
};

GameObject::GameObject(byte flags) {
    // Base class constructor (likely Object::Object or similar)
    BaseObject::BaseObject(); // Address: 0x0090dda0
    if (flags & 1) {
        // Optional initialization routine (e.g., setup components)
        this->init(); // Address: 0x009c8eb0
    }
}