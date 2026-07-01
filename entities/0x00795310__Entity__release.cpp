// FUNC_NAME: Entity::release
// Function address: 0x00795310
// Role: Releases the entity object - calls its destructor if the object is valid (vtable pointer non-null) and optionally frees memory if param_2 has bit 1 set.
// This pattern is common in EA's memory management for object destruction and deallocation.

int* __thiscall Entity::release(byte param_2)
{
    // Check if the object's vtable pointer (first member) is non-null, indicating a valid, not-yet-destroyed object.
    if (this->vtable != 0) {
        // Call internal destructor/cleanup function (0x004DAF90)
        internalDestroy(this);
    }
    // If the low bit of param_2 is set, deallocate the object's memory (0x009C8EB0)
    if ((param_2 & 1) != 0) {
        internalDeallocate(this);
    }
    return this;
}