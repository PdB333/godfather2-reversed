// FUNC_NAME: DynamicArray::reserve
// Function at 0x006f81c0 - Resizes dynamic array only if new capacity exceeds current.
// Structure fields (this):
//   +0x00: Element* data      - pointer to array of elements (12 bytes each)
//   +0x04: int32 count        - number of active elements
//   +0x08: int32 capacity     - allocated capacity

void __thiscall DynamicArray::reserve(uint newCapacity)
{
    // External allocation/release functions (likely memory management)
    extern void* __cdecl allocateMemory(uint size);
    extern void __cdecl freeMemory(void* ptr);
    extern void __cdecl releaseElement(Element* elem); // clean-up for an element

    // Element structure (12 bytes):
    //   +0x00: int* objectPtr   - pointer to associated game object
    //   +0x04: int* prevLink    - linked list pointer (backlink from object)
    //   +0x08: uint8 flags      - low byte of third word

    struct Element {
        int* objectPtr;
        int* prevLink;
        uint8 flags;
    };

    Element* oldData = *(Element**)this;
    int count = *(int*)((char*)this + 4);
    int capacity = *(int*)((char*)this + 8);

    if (capacity >= newCapacity)
        return;

    // Allocate new array (each element = 12 bytes)
    uint newSize = newCapacity * sizeof(Element);
    Element* newData = (Element*)allocateMemory(newSize);
    if (!newData)
        return; // allocation failure (original code does not check)

    if (oldData)
    {
        for (int i = 0; i < count; i++)
        {
            Element* oldElem = oldData + i;
            Element* newElem = newData + i;

            // Copy the object pointer
            int* obj = oldElem->objectPtr;
            newElem->objectPtr = obj;
            newElem->prevLink = nullptr;

            if (obj)
            {
                // Update linked list back-pointer in the object
                newElem->prevLink = (int*)*(int*)((char*)obj + 4);
                *(int**)((char*)obj + 4) = newElem;
            }

            // Copy flags (only low byte)
            newElem->flags = (uint8)oldElem->flags;

            // Release the old element (likely decrement refcount or remove from list)
            if (oldElem->objectPtr)
                releaseElement(oldElem);
        }

        freeMemory(oldData);
    }

    *(Element**)this = newData;
    *(int*)((char*)this + 8) = newCapacity;
}