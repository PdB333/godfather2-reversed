// FUNC_NAME: GameObject::GameObject
class GameObject {
public:
    // Constructor with a flag controlling whether to also call destructor (e.g., placement new).
    // If the low bit of 'flags' is set, the object is destroyed immediately after initialization.
    void* __thiscall GameObject(byte flags) {
        this->init(); // calls FUN_0076a220 (likely base initialization)
        if (flags & 1) {
            this->destroy(); // calls FUN_00624da0 (destructor/cleanup)
        }
        return this; // returns 'this' pointer for chaining
    }
};