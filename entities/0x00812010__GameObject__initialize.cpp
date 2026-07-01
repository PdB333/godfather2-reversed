// FUNC_NAME: GameObject::initialize
// Function address: 0x00812010
// This function initializes a game object. It calls a base initializer,
// sets the vtable, registers two callback function pointers, and sets a state sentinel to -1.

// Base initializer at 0x008119f0
void __thiscall baseInitialize(void* param_2);

class GameObject {
public:
    void* __thiscall initialize(void* param_2) {
        // Call base initialization
        baseInitialize(param_2);

        // Set the virtual function table pointer
        this->vtbl = (void*)0x00d72f88;

        // Set callback function pointers
        this->onEvent = (void*)0x00d72f78;   // offset 0x3C
        this->onUpdate = (void*)0x00d72f74;  // offset 0x48

        // Set state to -1 (uninitialized)
        this->state = -1;                     // offset 0xF0

        return this;
    }

private:
    void* vtbl;          // +0x00
    // base class members (size unknown, likely up to offset 0x3C)
    void* onEvent;       // +0x3C
    void* onUpdate;      // +0x48
    // ... padding or other fields ...
    int state;           // +0xF0
};