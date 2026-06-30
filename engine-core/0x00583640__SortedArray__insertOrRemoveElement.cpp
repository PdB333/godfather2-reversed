// FUNC_NAME: SortedArray::insertOrRemoveElement
void __thiscall SortedArray::insertOrRemoveElement(int *this, int *iter)
{
    // this is a pointer to a container with a pointer to the element to be processed at offset +0x4
    // iter: structure with base pointer (iter[0]), current pointer (iter[1]), count (iter[2])
    // Each element is 0x20 bytes, with a key at offset 0x1c
    struct Element {
        char data[0x1c]; // 28 bytes
        int key;          // +0x1c
    };

    Element *srcElement = *(Element **)(this + 4);       // element to process
    int index = ((char *)srcElement - (char *)iter[0]) >> 5;  // element index relative to base

    if (0 < iter[2]) {
        do {
            // if the element's key is already <= current position, stop
            if (index <= ((Element *)iter[1])->key) break;
            iter[2] = iter[2] - 1;
            iter[1] = iter[1] + 0x20;  // advance to next element
        } while (0 < iter[2]);

        // if we found an exact key match, remove that element from the list
        if ((0 < iter[2]) && (((Element *)iter[1])->key == index)) {
            // destroy the element (likely a destructor call)
            FUN_00582c70(srcElement);   // cleanup / destructor
            iter[1] = iter[1] + 0x20;  // skip the removed element
            iter[2] = iter[2] - 1;
            return;
        }
    }

    // No matching key found: copy the element to itself (presumably the destination pointer has been updated elsewhere)
    Element *dstElement = *(Element **)(this + 4);
    *dstElement = *srcElement;  // copy 0x20 bytes (8 dwords)
}