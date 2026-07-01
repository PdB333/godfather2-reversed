// FUNC_NAME: DynamicArray::push_back
void __thiscall DynamicArray::push_back(void* this, int* value) {
    DynamicArray* arr = (DynamicArray*)this;
    if (arr->count == arr->capacity) {
        int newCapacity;
        if (arr->capacity == 0) {
            newCapacity = 1;
        } else {
            newCapacity = arr->capacity * 2;
        }
        arr->reallocate(newCapacity); // FUN_00963dc0 – reallocates internal buffer
    }
    int* dest = arr->data + arr->count;
    arr->count++;
    if (dest != nullptr) {
        *dest = *value;
    }
}