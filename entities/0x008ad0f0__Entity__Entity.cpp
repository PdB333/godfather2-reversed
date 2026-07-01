// FUNC_NAME: Entity::Entity
// This function is the constructor for the Entity class (or a derived class).
// It calls a base class constructor and sets the vtable pointer to point to the Entity vtable at 0x00e317cc.
// The base constructor at 0x004bc280 likely belongs to a parent class such as SimObject or EARS::Object.

// Forward declaration for base class constructor (signature assumed __thiscall)
void __thiscall BaseClassConstructor(void* thisPtr);

void __thiscall Entity::Entity()
{
    // Call base class initializer (this pointer passed via ecx)
    BaseClassConstructor(this);

    // Set the vtable for this instance (offset 0x00 representing the vtable pointer)
    this->vtable = (void*)0x00e317cc; // VTable address for Entity class
}