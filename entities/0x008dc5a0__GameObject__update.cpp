// FUNC_NAME: GameObject::update
void __fastcall GameObject::update(int* this)
{
    // Call base class update (likely TNL or EARS base object)
    BaseObject::update();

    // Call another update (e.g., animation, physics, or state machine)
    GameObject::subUpdate();

    // Call virtual function at vtable offset 0x1a8 (e.g., OnUpdate, OnTick)
    (*(void (**)(void))(*this + 0x1a8))();

    // Check if this object is pending destruction (e.g., dead/removed)
    if (GameObject::isPendingDestroy())
    {
        int subObjectPtr = this[100]; // Offset +0x190: pointer to a sub-object (e.g., weapon, gadget)

        if (subObjectPtr != 0)
        {
            // Deallocate memory starting at offset 0x58 within the sub-object
            // This likely frees a specific component or sub-sub-object
            Memory::deallocate((void*)(subObjectPtr + 0x58));
        }
        else
        {
            // Safe deallocation of null pointer
            Memory::deallocate(nullptr);
        }

        // Perform final destruction steps (e.g., remove from manager lists)
        GameObject::finalizeDestroy();
    }
}