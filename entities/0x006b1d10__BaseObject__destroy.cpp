// FUNC_NAME: BaseObject::destroy
// Address: 0x006b1d10
int* __thiscall BaseObject::destroy(unsigned char shouldFree)
{
    // Check if the object is valid (vtable pointer non-null)
    if (m_vtable != nullptr) {
        shutdown(); // FUN_004daf90 - release internal resources
    }
    // If bit 0 of flag is set, deallocate memory
    if ((shouldFree & 1) != 0) {
        operator delete(this); // FUN_009c8eb0 - free object memory
    }
    return this;
}