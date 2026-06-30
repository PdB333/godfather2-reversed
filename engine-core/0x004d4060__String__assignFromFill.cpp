// FUNC_NAME: String::assignFromFill

void __thiscall String::assignFromFill(String* this, uint newLength, char fillChar) {
    uint uVar1; // loop variable
    void* _Dst; // new buffer

    // Case: new length fits within existing capacity
    if (newLength < this->capacity) {
        // Fill from current length to (newLength - 1) with fillChar
        for (uVar1 = this->length; uVar1 < newLength; uVar1++) {
            *(char*)(uVar1 + this->data) = fillChar;
        }
        // If either shrinking the string or fillChar is non-zero, null-terminate and update length
        if ((newLength < this->length) || (fillChar != '\0')) {
            *(undefined1*)(newLength + this->data) = 0; // null terminator at index newLength
            this->length = newLength;
            return;
        }
    }
    // Case: capacity insufficient, need to grow
    else if (this->capacity < newLength) {
        // Allocate new buffer (newLength+1 bytes)
        _Dst = (void*)FUN_009c8e50(newLength + 1);
        // Copy existing data (up to current length) into new buffer
        if ((void*)this->data != (void*)0x0) {
            _memcpy(_Dst, (void*)this->data, this->length);
            // Free old buffer using deallocator
            if (this->data != 0) {
                (*(code*)this->deallocator)(this->data);
            }
        }
        // Set new data pointer and deallocator (default to thunk_FUN_009c8eb0)
        this->data = (char*)_Dst;
        this->deallocator = (int)thunk_FUN_009c8eb0; // likely free or operator delete
        // Fill the new portion after old length with fillChar
        _memset((void*)(this->length + (int)_Dst), (int)fillChar, newLength - this->length);
        // If fillChar is non-zero, set the final length and null-terminate
        if (fillChar != '\0') {
            this->length = newLength;
            *(undefined1*)(newLength + this->data) = 0;
        }
        // Update capacity to the new allocated size
        this->capacity = newLength;
    }
    // Case: newLength exactly equals capacity (implicitly handled by nothing? The code just returns)
    return;
}