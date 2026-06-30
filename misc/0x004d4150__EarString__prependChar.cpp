// FUNC_NAME: EarString::prependChar

// Reconstructed string class with custom allocator/deleter.
// Structure offsets:
// +0x00: char* m_buffer           - pointer to string data
// +0x04: size_t m_length          - current length (excluding null terminator)
// +0x08: size_t m_capacity        - allocated capacity (including null terminator)
// +0x0C: void* m_deleter          - function pointer to free m_buffer (custom allocator)

void __thiscall EarString::prependChar(EarString* this, char ch)
{
    size_t oldLen = this->m_length;

    if (oldLen == 0) {
        // If empty, delegate to a specialized single‑char assignment
        EarString::assignSingleChar(this, ch);
        return;
    }

    // Check if there is room for one more character plus the null terminator
    // Capacity is total allocated slots including null.
    if (oldLen + 1 < this->m_capacity) {
        // Shift existing content right by one byte
        memmove(this->m_buffer + 1, this->m_buffer, oldLen);
        // Place new character at the beginning
        *this->m_buffer = ch;
        // Update length and null‑terminate
        this->m_length = oldLen + 1;
        *(this->m_buffer + this->m_length) = '\0';
        return;
    }

    // Need to reallocate: allocate oldLen + 2 bytes (for the added char + null)
    char* newBuf = (char*)customAlloc(oldLen + 2);
    char* src = this->m_buffer;
    char* dst = newBuf + 1; // leave first slot for the new character

    // Copy the old string (including null terminator via the do‑while loop)
    do {
        *dst = *src;
        ++dst;
        ++src;
    } while (*src != '\0'); // careful: this copies up to the old null, but null is included

    // Place the new character at the very beginning
    *newBuf = ch;

    // Free the old buffer using the custom deleter
    if (this->m_buffer != NULL) {
        ((void (*)(void*))this->m_deleter)(this->m_buffer);
    }

    // Update structure fields
    this->m_length = oldLen + 1;
    this->m_buffer = newBuf;
    // Capacity is set to exactly the new length (no extra space allocated – could be a design choice)
    this->m_capacity = oldLen + 1;
    this->m_deleter = (void*)(thunk_customAlloc); // standard deleter (thunk to custom free)
}