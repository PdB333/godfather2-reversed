// FUNC_NAME: StringBuffer::appendChar
void __thiscall StringBuffer::appendChar(int* this, char ch)
{
    int len = this[1]; // +0x4: length
    if (len != 0) {
        int cap = this[2]; // +0x8: capacity
        if ((unsigned int)cap <= len + 1U) {
            // Need to grow buffer: allocate new space (len+2 to fit char + null terminator)
            void* newBuf = (void*)FUN_009c8e50(len + 2); // custom allocator
            _memcpy(newBuf, (void*)*this, len); // copy existing data
            if (*this != 0) {
                (*(void (*)(void*))this[3])(*this); // +0xC: custom deallocator
            }
            *this = (int)newBuf;
            this[2] = len + 1U; // capacity = new length (len+1)
            this[3] = (int)thunk_FUN_009c8eb0; // set deallocator to default
        }
        // Place character at old length position
        *(char*)(*this + len) = ch;
        this[1] = len + 1; // increment length
        // Null-terminate
        *(char*)(*this + this[1]) = 0;
        return;
    }
    // If length is 0, delegate to single-character handling
    FUN_004d3f90(ch);
    return;
}