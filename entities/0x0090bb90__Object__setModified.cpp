// FUNC_NAME: Object::setModified
// Address: 0x0090bb90
// Role: Sets a modified flag and potentially an additional pending flag based on input.
// Offset 0x10: uint flags; bit0 = modified, bit1 = pending (or similar)

void __thiscall Object::setModified(char modified)
{
    uint& flags = *(uint*)((char*)this + 0x10); // +0x10: flags

    if (modified == '\0') {
        if ((flags & 1) != 0) {
            flags &= 0xfffffffe;  // clear bit0 (modified)
            flags |= 2;           // set bit1 (pending)
        }
    }
    else {
        if ((flags & 1) == 0) {
            flags |= 1;           // set bit0 (modified)
            flags |= 2;           // set bit1 (pending)
        }
    }
}