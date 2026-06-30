// FUNC_NAME: Container::assignRange
Container* Container::assignRange(void* first, void* last, int flags, int destructFlag) {
    // Internal buffer descriptor fields (assumed structure):
    // +0x00: dataPtr (int*)
    // +0x04: writePtr (int*) – current end of used elements
    // +0x08: capacityPtr (int*) – end of allocated storage
    // +0x0C: capacityCount (int) – number of elements that can be stored before growth
    // This structure is pointed to by the container's internal state.

    // NOTE: In the original binary, 'first' is passed in ECX (this), 'last' is stack param (param_2),
    // and the buffer descriptor is passed as an additional stack parameter (in_stack_00000020).
    // For clarity, we assume 'this' is the container, and 'first'/'last' define the source range.

    int* src = (int*)first;
    int* srcEnd = (int*)last;
    // Assume the container's internal descriptor is accessed via a member pointer
    ContainerInternal* desc = this->internalBufferDesc;

    if (src != srcEnd) {
        do {
            if (desc->writePtr < desc->capacityPtr) {
                // Room available, copy element and advance write pointer
                *desc->writePtr = *src;
                desc->writePtr++;
            } else {
                // No room, need to grow before copying
                int currentSize = (desc->writePtr - desc->dataPtr) / 4; // number of elements used
                if (desc->capacityCount <= currentSize) {
                    this->reserve(); // FUN_00b97aea – allocate more memory
                }
                // Copy element
                if (desc->writePtr != nullptr) {
                    *desc->writePtr = *src;
                }
                desc->writePtr++;
                // After growth, capacity pointer is updated to match write pointer
                desc->capacityPtr = desc->writePtr;
            }
            src++;
        } while (src != srcEnd);
    }

    // Zero out the first five fields of param_1 (which is 'this') – likely clearing unused state
    this->field0 = 0;
    this->field1 = 0;
    this->field2 = 0;
    this->field3 = 0;
    this->field4 = 0;
    // Store the internal buffer descriptor pointer in the sixth field (likely for iteration)
    this->field5 = desc;

    if (destructFlag != 0) {
        // FUN_009c8eb0 – possibly a destructor or cleanup function
        this->callDestructor();
    }

    return this;
}