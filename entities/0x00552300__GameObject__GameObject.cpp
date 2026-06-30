// FUNC_NAME: GameObject::GameObject
// Function address: 0x00552300
// Role: Constructor for a game object. Calls base class initializer, then optionally allocates memory via TLS allocator.

int __thiscall GameObject::GameObject(GameObject* this, byte allocFlags)
{
    // Call base class constructor/initializer
    BaseClass::BaseClass(this);

    // If bit 0 of allocFlags is set, perform heap allocation using thread-local storage allocator
    if ((allocFlags & 1) != 0) {
        // Retrieve thread-local allocator (likely from TLS slot)
        void* tlsAllocator = TlsGetValue(DAT_01139810);
        // Allocate memory for this object: size = 0x34, using the 2-byte field at offset +4 as a type/size hint
        FUN_00aa26e0(this, *(unsigned short*)((char*)this + 4), 0x34);
    }

    return this;
}