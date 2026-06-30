// FUNC_NAME: SimObject::SimObject

__thiscall void* SimObject::SimObject(void* manager, int id)
{
    // Call base class constructor (EARSObject or similar) with manager and id
    BaseClass::Constructor(manager, id);

    // Set vtable pointer (likely to SimObject vtable at 0x00d636bc)
    this->vtable = (void**)&PTR_LAB_00d636bc;

    // Initialize intrusive linked list head (offset +0x70)
    this->listHead = nullptr;
    // Initialize saved container pointer of previous head (offset +0x74)
    this->prevHeadContainerPtr = 0;

    // Retrieve a pointer from the manager's field at offset +0x2014
    // This pointer is a node that should become the first element of our list.
    void* newNode = *(void**)((char*)this->manager + 0x2014);

    // Adjust pointer (null check and offset cancellation - effectively gets the raw pointer)
    if (newNode != nullptr)
    {
        newNode = (char*)newNode - 0x48;
    }
    if (newNode != nullptr)
    {
        newNode = (char*)newNode + 0x48;
    }

    void* finalNode = newNode;

    // Compare with current list head
    if (this->listHead != finalNode)
    {
        // Remove old list head from any existing list (FUN_004daf90 likely a node removal)
        if (this->listHead != nullptr)
        {
            NodeList::Remove(&this->listHead); // FUN_004daf90
        }

        // Set new list head
        this->listHead = finalNode;

        if (finalNode != nullptr)
        {
            // Save the previous container pointer stored in the new node's +4 field
            this->prevHeadContainerPtr = *(void**)((char*)finalNode + 4);
            // Update the new node's +4 field to point back to this list head variable
            *(void***)((char*)finalNode + 4) = &this->listHead;
        }
    }

    return this;
}