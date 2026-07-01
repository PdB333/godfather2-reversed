// FUNC_NAME: FourIntKeyList::removeByKey
int FourIntKeyList::removeByKey(int *key)
{
    uint count = *(uint *)(this + 0xc); // number of elements in list
    uint index = 0;
    if (count != 0) {
        int **ptr = *(int ***)(this + 8); // pointer to array of element pointers
        do {
            int *element = *ptr;
            // Compare four ints at offsets +0x1c, +0x20, +0x24, +0x28 against key[0..3]
            if (element[0x1c/4] == key[0] && element[0x20/4] == key[1] &&
                element[0x24/4] == key[2] && element[0x28/4] == key[3]) {
                if (index < count - 1) {
                    // Shift remaining elements left
                    do {
                        *(int *)(*(int *)(this + 8) + index * 4) =
                            *(int *)(*(int *)(this + 8) + 4 + index * 4);
                        index++;
                    } while (index < *(int *)(this + 0xc) - 1);
                }
                // Decrement element count
                *(int *)(this + 0xc) = *(int *)(this + 0xc) - 1;
                return (int)element;
            }
            index++;
            ptr++;
        } while (index < count);
    }
    return 0;
}