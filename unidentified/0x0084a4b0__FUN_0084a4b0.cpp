// FUNC_NAME: SomeObject::getDisplayName
int * __fastcall SomeObject::getDisplayName(int *this)
{
    // Check if the name buffer is already populated (flag at offset 0x20)
    if (this[8] == 0) {
        // Lazy-initialize the name string from an external source
        // Source: dereference pointer at offset 0x00 then add 0x40 to get a pointer to the string pointer
        // Then read the actual string pointer from that location
        // Destination: the internal name buffer at offset 0x1c (this+7)
        FUN_00603330(
            *(undefined4 *)(*this + 0x40),   // char* source: read ptr from (*this + 0x40)
            this + 7                          // char* destination: this->m_szName
        );
        // Mark the buffer as initialized (flag at offset 0x20)
        this[8] = 1;
    }
    // Return pointer to the name buffer (offset 0x1c)
    return this + 7;
}