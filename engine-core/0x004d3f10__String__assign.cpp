// FUNC_NAME: String::assign
int* __thiscall String::assign(int* this, const char* src, int srcOffset, unsigned int count)
{
    // String structure layout:
    // +0x00: char* data
    // +0x04: int length
    // +0x08: int capacity
    // +0x0C: void (*destructor)(char*)
    char* data = (char*)this[0];
    int capacity = this[2];
    void (*destructor)(char*) = (void (*)(char*))this[3];

    if (count != 0) {
        if (capacity <= (int)count) {
            // Reallocate to fit the new size
            if (data != (char*)0x0) {
                destructor(data);
            }
            // Allocate count+1 bytes (null terminator)
            data = (char*)FUN_009c8e50(count + 1);
            this[0] = (int)data;
            this[2] = count;
            this[3] = (int)thunk_FUN_009c8eb0;
        }
        // Copy the source substring and null-terminate
        _memcpy(data, src + srcOffset, count);
        data[count] = '\0';
        this[1] = count;
        return this;
    }
    // count == 0: clear the string
    this[1] = 0;
    if (data != (char*)0x0) {
        data[0] = '\0';
    }
    return this;
}