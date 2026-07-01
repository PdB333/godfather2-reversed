// FUNC_NAME: EARS::Framework::ObjectArray::~ObjectArray
// Address: 0x008223d0
// This destructor iterates over an array of child objects (pointers stored at +0x8, count at +0xC),
// calls their first virtual function with argument 1 (likely Release/Destroy), then frees the array itself.

void __fastcall ObjectArray::~ObjectArray(ObjectArray* this)
{
    // Set vtable to base class destructor vtable? (This is unusual but present in debug builds)
    this->vtable = &PTR_FUN_00d73400;

    // If there are any elements in the array
    if (this->m_count != 0) {
        for (uint32_t i = 0; i < this->m_count; ++i) {
            // Retrieve each child object pointer from the array (array stored at offset +0x8)
            SomeClass* child = this->m_array[i];
            if (child != nullptr) {
                // Call the first virtual function (offset 0 in vtable) with argument 1
                // Typically this is a Release/Destroy method
                child->vtable->FirstVirtualFunction(child, 1);
            }
        }
    }

    // Free the array memory itself (if allocated)
    if (this->m_array != nullptr) {
        FUN_009c8f10(this->m_array);
    }
}