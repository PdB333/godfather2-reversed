// FUNC_NAME: InternalBuffer::clear
void InternalBuffer::clear(void)
{
    int *dataPtr;
    int elementCount;

    dataPtr = this->data; // +0x08
    if (dataPtr != 0) {
        // Call virtual destructor for each element? Actually calls a function from vtable at offset 4
        // The second argument is the total size to free: ((end - start) / 0x28) * 0x28
        // This suggests freeing an array of 0x28-byte objects
        elementCount = (this->end - dataPtr) / 0x28; // +0x10 is end pointer
        (this->vtable->destroyElements)(dataPtr, elementCount * 0x28); // vtable at +0x00, function at +0x04
    }
    this->data = 0;   // +0x08
    this->capacity = 0; // +0x0C
    this->end = 0;    // +0x10
}