// FUNC_NAME: Container::clearAndDeallocate
void __fastcall Container::clearAndDeallocate(int *this)
{
    int count = this[1] - 1;
    if (count >= 0) {
        int offset = count * 0x28; // each element is 0x28 bytes
        do {
            // Element base: this[0] + offset
            int *elementBase = (int *)((char *)this[0] + offset);
            int *objectPtr = (int *)elementBase[1]; // +0x04: pointer to object
            if (objectPtr != 0) {
                // +0x10: function pointer (destructor/release)
                void (*destructor)(void *) = (void (*)(void *))elementBase[4];
                destructor(objectPtr);
            }
            count--;
            offset -= 0x28;
        } while (count >= 0);
    }
    this[1] = 0; // count = 0
    FUN_009c8f10(this[0]); // free the data array
    this[0] = 0; // data = nullptr
    this[2] = 0; // capacity = 0
}