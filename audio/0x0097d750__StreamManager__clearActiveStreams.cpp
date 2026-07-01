// FUNC_NAME: StreamManager::clearActiveStreams
void __thiscall StreamManager::clearActiveStreams(void)
{
    uint count;               // number of elements in array
    int elementOffset;        // byte offset into element array
    int handle;               // resource handle (e.g. sound ID)
    int *element;             // pointer to current element
    int releaseBuffer;        // temporary buffer for resource release call
    uint index;               // loop counter

    count = *(uint *)(this + 0xac);          // number of active streams
    if (count != 0) {
        elementOffset = 0;
        do {
            // element structure: [0]=object pointer, [4]=object pointer, [8]=handle
            handle = *(int *)(*(int *)(this + 0xa8) + 8 + elementOffset);
            element = (int *)(*(int *)(this + 0xa8) + elementOffset);
            if (handle != 0) {
                FUN_009e71f0(&releaseBuffer, handle);   // release the resource handle
                FUN_009f01a0();                           // cleanup after release
                element[2] = 0;                           // clear handle in element
            }
            // release first object pointer via vtable call
            if (element[1] != 0) {
                (*(void (**)(int))(*(int *)element[1]))(1);
                element[1] = 0;
            }
            // release second object pointer via vtable call
            if (element[0] != 0) {
                (*(void (**)(int))(*(int *)element[0]))(1);
                element[0] = 0;
            }
            index = index + 1;
            elementOffset = elementOffset + 0x10;        // each element is 16 bytes
        } while (index < count);
    }
    *(uint *)(this + 0xac) = 0;                          // reset count
    FUN_009c8f10(*(int *)(this + 0xa8));                  // free the array memory
    *(int *)(this + 0xa8) = 0;                            // clear pointer
    *(int *)(this + 0xb0) = 0;                            // reset capacity/other count
}