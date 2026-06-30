// FUNC_NAME: StringBuffer::removeAt

// Removes the character at the given index from the string buffer.
// The buffer is null-terminated and stores its length in the second field.
// If the index is at or beyond the current length, the string is truncated to that index.
// Otherwise, characters are shifted left and the length is decremented.
// Returns a pointer to this object.
int* __thiscall StringBuffer::removeAt(int* this, int index)
{
    // this[0] = pointer to character data (char*)
    // this[1] = current length of the string (excluding null terminator)
    char* data = (char*)this[0];
    int length = this[1];

    if (length <= index + 1)
    {
        // Truncate: set new length and null-terminate at the given index
        this[1] = index;
        data[index] = '\0';
        return this;
    }

    // Shift characters left by one position starting at index
    memmove(data + index, data + index + 1, length - index - 1);
    this[1] = length - 1;
    data[this[1]] = '\0';
    return this;
}