// FUNC_NAME: GameObject::GameObject
// Function address: 0x006bbeb0
// Role: Constructor for GameObject, calls base constructor and conditionally initializes heap-allocated objects.

// Note: param_2 is a flag indicating whether the object was allocated on the heap (bit 0 set).
// If heap-allocated, a function is called to set up the vtable or register the object.

void __thiscall GameObject::GameObject(byte isHeapAllocated)
{
    // Call base class constructor
    BaseObject::BaseObject();

    // If the object was heap-allocated, perform additional initialization
    if (isHeapAllocated & 1)
    {
        // Initialize heap-allocated object with size 0x130 (304 bytes)
        // This likely sets up the vtable pointer or registers the object with a manager.
        initializeHeapObject(this, 0x130);
    }

    // Return the constructed object (this pointer)
    return this;
}