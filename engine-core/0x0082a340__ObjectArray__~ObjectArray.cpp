//FUNC_NAME: ObjectArray::~ObjectArray
void __fastcall ObjectArray::~ObjectArray(undefined4 *this)
{
    uint index;
    undefined4 *element;

    // Set vtable pointer (destructor vtable)
    *this = &PTR_FUN_00d73784;

    // Iterate over the array of pointers stored at offset +8
    // Array count stored at offset +12
    if (this[3] != 0) {
        index = 0;
        do {
            element = *(undefined4 **)(this[2] + index * 4);
            if (element != (undefined4 *)0x0) {
                // Call virtual release/destroy function (first vtable entry) with argument 1
                (**(code **)*element)(1);
            }
            index = index + 1;
        } while (index < (uint)this[3]);
    }

    // Free the array memory (offset +8)
    if (this[2] != 0) {
        FUN_009c8f10(this[2]); // likely operator delete[] or free
    }
    return;
}