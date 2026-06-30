// FUNC_NAME: SomeContainer::~SomeContainer
int __thiscall SomeContainer::destructor(int flags) {
    // flags bit 1 (0x2) indicates this is an array destructor
    // flags bit 0 (0x1) indicates the allocated memory should be freed

    if (flags & 2) {
        // Array destruction path
        int count = *(int *)((char *)this - 4); // element count stored at this-4 (before object)
        if (count >= 0) {
            // Element size is 0x2c bytes
            int *elementBase = (int *)((char *)this + 0x14); // base of array buffer
            int *curr = elementBase + count * 11; // initially points past the last element (11 ints per element)
            do {
                int *elem = curr - 11; // previous element start
                // Free three pointers per element at offsets -0x08, 0x00, +0x08 from element start
                if (curr[-9] != 0) { // offset +0x08 within element
                    FUN_004daf90(curr + -9); // destructor for that pointer's owned object
                }
                if (*elem != 0) { // offset 0x00
                    FUN_004daf90(elem);
                }
                if (curr[-0xd] != 0) { // offset -0x08 within element
                    FUN_004daf90(curr + -0xd);
                }
                count--;
                curr = elem;
            } while (count >= 0);
        }
        if (flags & 1) {
            FUN_009c8f10(this - 4); // delete[] the memory block
        }
        return (int)(this - 4); // return the memory block pointer
    } else {
        // Single object destruction path
        if (*(int *)((char *)this + 0x1c) != 0) {
            FUN_004daf90((int *)((char *)this + 0x1c)); // field at +0x1c
        }
        if (*(int *)((char *)this + 0x14) != 0) {
            FUN_004daf90((int *)((char *)this + 0x14)); // field at +0x14
        }
        if (*(int *)((char *)this + 0xc) != 0) {
            FUN_004daf90((int *)((char *)this + 0xc)); // field at +0x0c
        }
        if (flags & 1) {
            FUN_009c8eb0(this); // delete the object
        }
        return (int)this;
    }
}