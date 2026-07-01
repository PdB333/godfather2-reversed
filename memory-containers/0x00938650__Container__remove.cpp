// FUNC_NAME: Container::remove
void __thiscall Container::remove(uint32 index) {
    uint32 count = this->count; // +0x04: number of elements
    // Shift elements left to fill the hole at 'index'
    if (index < count - 1) {
        int32 offset = index * 0x10; // 16-byte element stride
        do {
            // Destroy the element at (index+1) before it gets overwritten by the shift?
            // Actually this calls on the element that will be moved; typical pattern: call destructor on the slot that will be overwritten.
            // Here it's called on the source (next element), likely meaning FUN_004d3e20 is a "move" that also clears the source.
            Container::destroyElement((ContainerElement*)(this->buffer + offset + 0x10));
            index++;
            offset += 0x10;
        } while (index < count - 1);
    }
    this->count = count - 1; // decrement element count
    // Clear the last slot (now unused) by calling its destructor if it holds a valid object
    ContainerElement* lastSlot = (ContainerElement*)(this->buffer + this->count * 0x10);
    if (lastSlot->ptr != 0) { // +0x00: pointer to object (likely the allocated entity)
        // +0x0C: function pointer for destructor/release
        ((void (*)(void*))lastSlot->dtorFunc)(lastSlot->ptr);
    }
}