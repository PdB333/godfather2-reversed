// FUNC_NAME: GameObject::~GameObject
// Function at 0x7676d0 - Destructor with delete flag for a multiple-inheritance object
void* __thiscall GameObject_Destructor(GameObject* this, byte deleteFlag)
{
    // Set vtable pointers for destruction (presumably to the destructor vtables)
    *(void**)((char*)this + 0x70) = &PTR_LAB_00d64708; // secondary vtable at +0x70
    *(void**)this = &PTR_LAB_00d63090;                 // primary vtable at +0x00

    // Release a sub-object or resource stored at offset 0x68
    void* resource = *(void**)((char*)this + 0x68);    // +0x68
    if (resource != 0) {
        FUN_004daf90(resource);  // likely release or delete the resource
    }

    // Global cleanup (e.g., notify manager, decrement global reference count)
    FUN_0080ea60();

    // If the object was allocated on the heap (deleteFlag & 1), free memory
    if ((deleteFlag & 1) != 0) {
        FUN_00624da0(this); // operator delete
    }

    return this;
}