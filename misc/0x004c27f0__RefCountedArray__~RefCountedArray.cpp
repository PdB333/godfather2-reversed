// FUNC_NAME: RefCountedArray::~RefCountedArray
void __fastcall RefCountedArray::~RefCountedArray(RefCountedArray* this)
{
    // this->vtable at offset 0
    // this->padding[1] at offset 4 (unused)
    // this->entries[] at offset 8 (array of 8-byte entries: [pointer, reserved])
    // this->count at offset 0x324

    // Set vtable to derived class (this class)
    this->vtable = (void*)&PTR_FUN_00e361ec;

    if (this->count != 0) {
        // Walk the array of entries (each entry is two ints: first = pointer to refcounted object)
        uint i = 0;
        int** entryPtr = (int**)(&this->entries); // cast to pointer-to-pointer for first field
        do {
            int* obj = *entryPtr;  // first int* of entry is pointer to object
            if (obj != NULL) {
                // Decrement reference count at offset 0 of object
                obj[0] = obj[0] - 1;
                if (obj[0] == 0) {
                    // Object reached zero refcount, call its virtual destructor (vtable at offset 0x10C, method at offset 0x18)
                    // obj[0x43] is a pointer to a vtable (offset 0x10C)
                    (*(void (__thiscall**)(int*))(*(int*)obj[0x43] + 0x18))(obj);
                }
            }
            *entryPtr = NULL;               // clear pointer in array
            i++;
            entryPtr += 2;                  // advance 8 bytes (two ints) to next entry
        } while (i < this->count);
    }

    // Set vtable to base class (destruction phase)
    this->vtable = (void*)&PTR_LAB_00e361cc;
}