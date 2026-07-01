// FUNC_NAME: EntityManager::getEntityFromComponentArray
// Function at 0x008e33d0: Retrieves a pointer to an entity from an array of component pointers.
// The array is stored at offset 0xC4 from 'this', each element is 0x5C bytes.
// Each element contains a pointer to a component (at offset 0x00 within the element).
// The actual entity base is at componentPtr - 0x48.
// Returns 0 if the component pointer is null.

int __thiscall EntityManager::getEntityFromComponentArray(int thisPtr, int index)
{
    // Access the array at offset 0xC4, element size 0x5C
    int* componentPtr = *(int**)(index * 0x5C + 0xC4 + thisPtr);
    if (componentPtr != 0) {
        // The component pointer points into the entity at offset 0x48,
        // so subtract 0x48 to get the entity base.
        return componentPtr - 0x48;
    }
    return 0;
}