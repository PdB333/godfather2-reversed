// FUNC_NAME: ElementArray::addMultipleElements
void __thiscall ElementArray::addMultipleElements(unsigned int count)
{
    int currentEnd = this->end;   // +0x04: pointer to end of allocated elements
    int currentStart = this->start; // +0x00: pointer to start of allocated elements

    // Calculate number of elements currently in the array (element size = 0x50)
    int currentCount = (currentEnd - currentStart) / 0x50;

    // If we need more elements than the current capacity allows, we must reallocate
    if ((unsigned int)currentCount < count)
    {
        // Temporary element to use as a "default" for construction
        // The actual element structure is 0x50 bytes.
        // We initialize it to 0, then set word at offset 0x30 to 1.
        // (Note: Ghidra's decompiler shows the locals as fragmented; in reality it's a single buffer)
        struct TempElement {
            char data[0x50];
        } tempElement;
        memset(&tempElement, 0, sizeof(tempElement));
        // Set a specific field (possibly a "valid" flag or "type" field)
        *reinterpret_cast<unsigned short*>(tempElement.data + 0x30) = 1;

        // Allocate more memory and construct the new elements (including the tempElement as prototype)
        allocateAndConstruct(currentEnd, count - currentCount, &tempElement);
    }
    else
    {
        // There is enough capacity; just construct new elements in the existing buffer
        constructElements(currentStart + count * 0x50, currentEnd);
    }
}