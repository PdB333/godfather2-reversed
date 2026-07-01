//FUNC_NAME: EntityManager::collectEntitiesByType
// Function address: 0x008de020
// Role: Iterates over a fixed-size array of entity nodes (300 entries, stride 0xC) and collects pointers to entities of a specific type (type == 3) into a dynamic array.
// The manager's entity list is at this+0x24 (pointer to array of node structs).
// Each node struct (size 0xC) has a pointer to an internal node at offset 4.
// The actual entity object is at node - 0x48.
// Entity type field is at entity+0x13C.
// The output array structure (param_2) has: [0] = pointer to array, [1] = count, [2] = capacity.

int __thiscall EntityManager::collectEntitiesByType(int thisPtr, int* outArray)
{
    int* nodePtr;
    int entityNode;
    int* arrayPtr;
    int isValid;
    unsigned int index;

    arrayPtr = outArray;
    index = 0;
    outArray[1] = 0;          // count = 0
    freeArray((void*)*outArray); // FUN_009c8f10 - free old array if any
    *outArray = 0;            // pointer = NULL
    outArray[2] = 0;          // capacity = 0

    do {
        // Read node pointer from manager's list at stride 0xC, offset 4
        entityNode = *(int*)(index + 4 + *(int*)(thisPtr + 0x24)); // +0x24: pointer to node array
        if (entityNode != 0) {
            int entity = entityNode - 0x48; // Adjust to actual entity object
            if (entity != 0 && *(int*)(entityNode + 0x13C) == 3) { // Type check (3 = e.g., NPC)
                acquireEntity(*(int*)(entityNode + 0x180)); // FUN_006b0ee0 - reference counting
                isValid = isEntityValid(); // FUN_006b4860 - returns 0 if valid
                if (isValid == 0) {
                    // Grow array if needed
                    if (outArray[1] == outArray[2]) {
                        int newCapacity = (outArray[2] == 0) ? 1 : outArray[2] * 2;
                        resizeEntityArray(newCapacity); // FUN_008dd700 - reallocate
                    }
                    // Append entity pointer
                    int* slot = (int*)(*outArray + outArray[1] * 4);
                    outArray[1] = outArray[1] + 1;
                    if (slot != 0) {
                        *slot = entity;
                    }
                    arrayPtr = (int*)((int)arrayPtr + 1); // Increment return counter (decompilation artifact)
                }
            }
        }
        index += 0xC; // Stride 12 bytes per node
    } while (index < 300); // Fixed 300 entries

    return (int)arrayPtr; // Returns count of added entities
}