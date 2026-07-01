// FUNC_NAME: GameObject::~GameObject (destructor with delete flag)
// Address: 0x007d29b0
// Role: Destructor for a game object (likely derived from multiple base classes).
// Destroys embedded sub-objects at offsets +0xB8 and +0x7C, updates vtable pointers,
// and optionally deletes memory if deleteFlag bit 0 is set.

// Known vtable symbols (from data):
// PTR_LAB_00d6ee6c     – original child vtable
// PTR_FUN_00d6e930     – intermediate base class vtable at offset +0x74
// PTR_LAB_00d6ba68     – final base class vtable after destruction
// PTR_LAB_00d6b95c     – root base class vtable

// Offsets from this:
// +0x74 (index 0x1d) : secondary vtable pointer
// +0x7C (index 0x1f) : sub-object (e.g., string or embedded object)
// +0xB8 (index 0x2e) : sub-object (e.g., container or another object)

// Called functions:
// 0x004daf90 – release/destroy function for sub-objects
// 0x0080ea60 – global cleanup (e.g., GameState::unregister)
// 0x00624da0 – operator delete (if deleteFlag & 1)

GameObject * __thiscall GameObject::~GameObject(GameObject *this, byte deleteFlag)
{
    // Set vtable to the current class vtable (child vtable)
    this->vtable = (int *)&PTR_LAB_00d6ee6c;

    // Destroy sub-object at offset +0xB8 if it exists
    if (*(void **)((char *)this + 0xB8) != (void *)0)
    {
        FUN_004daf90(this + 0x2e); // offset 0xB8
    }

    // Set secondary vtable pointer to intermediate base class vtable
    *(int **)((char *)this + 0x74) = (int *)&PTR_FUN_00d6e930;

    // Destroy sub-object at offset +0x7C if it exists
    if (*(void **)((char *)this + 0x7C) != (void *)0)
    {
        FUN_004daf90(this + 0x1f); // offset 0x7C
    }

    // Change secondary vtable pointer to final base class vtable
    *(int **)((char *)this + 0x74) = (int *)&PTR_LAB_00d6ba68;

    // Set primary vtable to root base class vtable
    this->vtable = (int *)&PTR_LAB_00d6b95c;

    // Call global cleanup function
    FUN_0080ea60();

    // If delete flag is set, free memory
    if ((deleteFlag & 1) != 0)
    {
        FUN_00624da0(this);
    }

    return this;
}