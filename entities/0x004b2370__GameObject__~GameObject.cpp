// FUNC_NAME: GameObject::~GameObject

class Child {
public:
    void* vtable; // +0x00
    // Virtual function table at offset 0x0C (4th entry) is release()
    virtual void release() = 0;
};

class GameObject {
public:
    void* vtable; // +0x00 (pointer to vtable)
    Child* child; // +0x04 (child object pointer)

    // Destructor
    void __thiscall ~GameObject() {
        // Set vtable to the destructor-specific vtable for this class
        this->vtable = &PTR_FUN_00e357e0;

        // If child exists, call its release() (virtual at vtable+0x0C) and nullify
        if (this->child != nullptr) {
            this->child->release();
            this->child = nullptr;
        }

        // Switch vtable to base class vtable (for proper destruction chain)
        this->vtable = &PTR_LAB_00e357e4;

        // Reset global instance count to 0
        DAT_012234b4 = 0;
    }
};