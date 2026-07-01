// FUNC_NAME: GameObject::GameObject
// Address: 0x0082bc80
// Role: Copy constructor for GameObject

class GameObject {
public:
    // Constructor that copies from another GameObject
    GameObject(const GameObject& source) {
        // Call base class copy constructor (or internal clone helper)
        // This is called on the source object; likely initializes base data.
        reinterpret_cast<void(*)(const GameObject*)>(0x0081f9f0)(&source);
        
        // Set vtable pointer for this class
        this->vtablePtr = reinterpret_cast<void* const*>(0x00d73738);
        
        // Copy field at offset 0x4C from source to new object
        // Offset 0x4C = 0x13 * 4 (since param_1[0x13] corresponds to this offset)
        this->field_0x4C = source.field_0x4C;
    }

private:
    void* vtablePtr;          // +0x00
    // Other fields ...
    uint32_t field_0x4C;      // +0x4C
};