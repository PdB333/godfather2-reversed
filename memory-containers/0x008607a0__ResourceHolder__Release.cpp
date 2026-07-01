// FUNC_NAME: ResourceHolder::Release
void __thiscall ResourceHolder::Release(int *this) // this = offset 0x00? Actually this is a pointer to the object
{
    // Check if the pointer at offset 0x00 (m_pResource) is non-null
    if (this[0] != 0) {
        // Release the internal resource (likely calls destructor or delete)
        FUN_004daf90(this); // internal release function (TODO: rename)
        this[0] = 0; // clear pointer at +0x00
    }
    // Clear reference count or ownership flag at offset 0x08
    this[2] = 0; // clears int at +0x08
}