// FUNC_NAME: ObjectManager::removeByInternalID

// Cleanup function called on an element before removal (likely destructor or unregister)
void __thiscall cleanupElement(int elementPtr);

// Element structure in the array (size 0x10)
struct ObjectElement {
    int field_0x00;   // +0x00: unknown
    int field_0x04;   // +0x04: unknown
    int field_0x08;   // +0x08: unknown
    int id;           // +0x0C: internal ID used for matching
};

// Manager class holding a dynamic array of ObjectElement
class ObjectManager {
public:
    ObjectElement* array;  // +0xB4: pointer to array of elements
    int count;             // +0xB8: number of elements in array

    // Removes the element whose id matches 'idToRemove'.
    // Shifts the last element into the vacated slot to keep the array contiguous.
    void __thiscall removeByInternalID(int idToRemove) {
        if (count == 0) {
            return;
        }

        // Search for the element with matching id (field at offset 0x0C)
        unsigned int index = 0;
        int* currentIdPtr = &(array[0].id); // equivalent to (int*)((int)array + 0x0C)
        while (*currentIdPtr != idToRemove) {
            index++;
            // Move to the next element's id (each element is 0x10 bytes)
            currentIdPtr += 4; // increments by 4 * sizeof(int) = 16 bytes
            if (index >= (unsigned int)count) {
                return; // not found
            }
        }

        // Found element at index 'index' – clean it up
        cleanupElement((int)(array + index));

        // If it's not the last element, overwrite with the last element
        if (index != count - 1) {
            array[index] = array[count - 1];
        }

        count--;
    }
};