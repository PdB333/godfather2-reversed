// FUNC_NAME: ContainerBase::~ContainerBase
// Address: 0x0082a9d0
// Role: Destructor for a container class that holds a dynamic array of objects.
// Iterates over the array, calls each object's destructor (via vtable), then frees the array memory.

void __fastcall ContainerBase::~ContainerBase(ContainerBase* this)
{
    // Set vtable to base class vtable (destructor chaining)
    this->vtable = &PTR_FUN_00d737d4;  // +0x00: vtable pointer

    // If there are objects in the array
    if (this->m_count != 0)  // +0x0C: number of elements
    {
        uint32_t i = 0;
        do
        {
            // Get pointer to each object
            ObjectBase* obj = this->m_objects[i];  // +0x08: pointer to array of object pointers
            if (obj != nullptr)
            {
                // Call destructor via vtable (first entry) with flag 1 (likely "delete")
                obj->vtable->destructor(1);
            }
            i++;
        } while (i < this->m_count);
    }

    // Free the array memory
    if (this->m_objects != nullptr)  // +0x08
    {
        FUN_009c8f10(this->m_objects);  // deallocateArray (likely operator delete[])
    }
}