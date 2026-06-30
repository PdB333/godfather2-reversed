// FUNC_NAME: String::assign
// 0x004d3b50: Copy assignment operator for custom String class (EASTL-like)
// Field offsets (in bytes):
//   +0x00: char* data
//   +0x04: int size    (length of string, without null)
//   +0x08: int capacity (allocated size, including null)
//   +0x0C: void (*deallocator)(void*) // typically free or custom
int* __thiscall String::assign(String* this, const String* source)
{
    int srcSize = source->size; // param_2[1]

    if (srcSize != 0) {
        this->size = srcSize;
        this->capacity = srcSize; // note: capacity equals size, no extra space
        // Allocate new buffer with room for null terminator
        char* newData = (char*)FUN_009c8e50(srcSize + 1);
        this->data = newData;
        memcpy(newData, source->data, srcSize);
        newData[srcSize] = '\0';
        this->deallocator = thunk_FUN_009c8eb0; // set deallocator function
        return this;
    }
    // If source is empty, reset this to empty
    this->data = nullptr;
    this->capacity = 0;
    this->size = 0;
    return this;
}