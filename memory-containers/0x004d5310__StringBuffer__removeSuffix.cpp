// FUNC_NAME: StringBuffer::removeSuffix
int* __thiscall StringBuffer::removeSuffix(int* this, char* suffix) {
    // this+0x00: pointer to buffer data (char*)
    // this+0x04: length of buffer (int)
    char* data = *(char**)this; // offset 0
    int length = this[1]; // offset 4

    // If buffer is empty, return
    if (data == nullptr)
        return this;

    // Get the first valid element (likely checks that data points to a valid string)
    char* current = (char*)validateStringAt((unsigned int)data);
    if (current == nullptr)
        return this;

    // Calculate length of the suffix to remove (excluding null terminator)
    int suffixLen = strlen(suffix);
    // Start scanning by stepping suffixLen bytes each time
    char* next = (char*)validateStringAt((unsigned int)(current + suffixLen));
    while (next != nullptr) {
        current = next;
        next = (char*)validateStringAt((unsigned int)(next + suffixLen));
    }

    // If the final valid element plus suffixLen exactly reaches the end of the buffer,
    // then the last segment matches the suffix → truncate at that point.
    if (current + suffixLen == data + length) {
        *current = '\0';                 // null-terminate at the truncation point
        length = (int)(current - data); // update buffer length
        this[1] = length;               // store new length
    }
    return this;
}