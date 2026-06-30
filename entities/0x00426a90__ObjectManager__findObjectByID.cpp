// FUNC_NAME: ObjectManager::findObjectByID
// Address: 0x00426a90
// Searches a linked list of nodes (each node contains an object pointer at offset 0 and a next pointer at offset 4)
// for an object whose ID at +0xA8 matches the given parameter.
// Returns the object pointer if found, otherwise 0.
// The list head is stored at this+0x4C.
// Calls critical section lock/unlock functions to protect traversal.

int* ObjectManager::findObjectByID(int id)
{
    // Lock the critical section (DAT_00e2e6f0 is the mutex object)
    csLock(&DAT_00e2e6f0);

    // Get head of the linked list from this+0x4C
    int* node = *(int**)(this + 0x4C);
    int* object = 0;

    // Traverse the list
    if (node != 0) {
        while (true) {
            // Dereference node to get the object pointer (node[0])
            object = (int*)*node;

            // If object is valid and its ID matches, break out
            if (object != 0 && *(int*)(object + 0xA8) == id) {
                break;
            }

            // Move to next node (node[1])
            node = (int*)node[1];
            if (node == 0) {
                csUnlock(&DAT_00e2e6f0);
                return 0;
            }
        }
    }

    csUnlock(&DAT_00e2e6f0);
    return object;
}