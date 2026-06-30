// FUNC_NAME: Entity::~Entity
// Function at 0x004cfb00: Destructor for the Entity class. Sets base vtable, calls base destructor,
// frees internal pointer (offset +0x04), and optionally deallocates the object itself if flags & 1.

class BaseEntity {
public:
    virtual ~BaseEntity(); // Called via FUN_004cfcc0
};

class Entity : public BaseEntity {
public:
    void* vtable;        // +0x00: vtable pointer (set to BaseEntity vtable during destruction)
    void* somePointer;   // +0x04: pointer freed unconditionally

    virtual ~Entity();   // Destructor function at 0x004cfb00
};

// __thiscall, returns this (ignored in destructor)
void* __thiscall Entity::~Entity(Entity* this, byte flags) {
    // Step 1: Set vtable to base class to prevent virtual calls to derived methods
    this->vtable = &BaseEntity::vtable;

    // Step 2: Call base destructor (FUN_004cfcc0)
    reinterpret_cast<BaseEntity*>(this)->~BaseEntity();

    // Step 3: Free internal pointer (operator delete, safe for null)
    operator delete(this->somePointer);

    // Step 4: If object was dynamically allocated, free the memory itself
    if (flags & 1) {
        operator delete(this);
    }

    return this; // Common convention in EA code
}