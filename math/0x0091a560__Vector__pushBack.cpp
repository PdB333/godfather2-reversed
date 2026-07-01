// FUNC_NAME: Vector::pushBack
void __thiscall Vector::pushBack(const undefined4& value) {
    // Offsets: +0x00 data pointer, +0x04 size, +0x08 capacity
    int size = *(int *)((char *)this + 4);
    int capacity = *(int *)((char *)this + 8);
    
    if (size == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        // Calls internal grow function (FUN_00917990) to reallocate buffer
        grow(capacity);
    }
    
    undefined4 *slot = *(undefined4 **)this + size;
    *(int *)((char *)this + 4) = size + 1;
    
    if (slot != nullptr) {
        *slot = value;
    }
}