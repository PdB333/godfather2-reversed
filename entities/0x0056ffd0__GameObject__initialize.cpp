// FUNC_NAME: GameObject::initialize
// Address: 0x0056ffd0
// Role: Initializes a three-field local structure to zero and delegates to a global function pointer.
// The global DAT_0120556c likely points to a constructor or initializer routine specific to the object's type.

void GameObject::initialize() {
    // Temporary structure to hold initial zeroed state
    struct {
        int field_0; // +0x00
        int field_4; // +0x04
        int field_8; // +0x08
    } initialData = {0, 0, 0};

    // Call the global function pointer to perform actual initialization
    // Function signature: void (__thiscall*)(GameObject*, void*)
    typedef void (__thiscall *InitFunc)(GameObject*, void*);
    ((InitFunc)DAT_0120556c)(this, &initialData);
}