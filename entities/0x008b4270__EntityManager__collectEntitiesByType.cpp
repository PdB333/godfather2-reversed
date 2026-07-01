// FUNC_NAME: EntityManager::collectEntitiesByType
int* __thiscall EntityManager::collectEntitiesByType(int* outArray, int typeId, char includeFlagged)
{
    // outArray: dynamic array struct: [0] pointer, [1] count, [2] capacity
    outArray[0] = 0;
    outArray[1] = 0;
    outArray[2] = 0;

    // +0x60: pointer to head of linked list of entity nodes
    int* node = *(int**)(this + 0x60);
    if (node == 0) {
        // empty list, return empty array
        return outArray;
    }

    // Check if the node's next pointer (offset +8) is null -> empty list
    if (*(int*)(node + 8) == 0) {
        node = 0;
    }

    while (node != 0) {
        // Call a global function to get info about the current node
        // This is likely a virtual function on the node object returning a pointer to an info struct
        EntityNodeInfo* info = (EntityNodeInfo*)(*(code*)PTR_FUN_00e35c28)();

        if (info->type == typeId &&
            (includeFlagged ||
             ((*(uint*)((code*)PTR_FUN_00e35c28() + 0x30) >> 1 & 1) == 0))) {
            // If conditions satisfied, add the entity's ID (offset +8 of info) to the array
            int id = *(int*)((code*)PTR_FUN_00e35c28() + 8);
            if (outArray[1] == outArray[2]) {
                // Grow array if full
                int newCapacity = outArray[2] == 0 ? 1 : outArray[2] * 2;
                growArray(newCapacity); // likely resize/realloc helper
            }
            *(int*)(outArray[0] + outArray[1] * 4) = id;
            outArray[1]++;
        }

        // Move to next node in the linked list (global function)
        (*(code*)_UNK_00e35c2c)();
    }

    // Sort the collected IDs if more than one
    if (outArray[1] > 1) {
        qsort((void*)outArray[0], outArray[1], 4, &compareIds);
    }

    return outArray;
}