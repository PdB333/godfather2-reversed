// FUNC_NAME: SceneObjectManager::cleanupDeadObjects
// Function at 0x00519020: Destroys objects marked for deletion from a doubly-linked list and clears child pointers in a tree-like structure.
// This is likely part of the EA EARS engine's object lifecycle management (The Godfather 2, 2008).
// It traverses two structures: a sibling/child list at this+0x14 and a global object list at this+0x10.
// Objects with flag bit 0 (0x1) set are removed from the list and deleted.
// Objects without flag bit 1 (0x2) get an update call before deletion.

void __thiscall SceneObjectManager::cleanupDeadObjects(void)
{
    int childIter;
    int *currentNode;
    int *prevNode;
    int *nextNode;
    int elementSize;
    int *poolHeader;

    // Phase 1: Clean up child links in a tree-like structure (offset 0x14 = first child)
    childIter = *(int *)(this + 0x14);
    if (childIter != 0) {
        // Get pool manager from thread-local storage (FS segment offset 0x2c)
        poolHeader = *(int **)(__readfsdword(0x2c) + 0x28);  // Assuming FS:[0x2c] points to pool
        elementSize = *(int *)(*(int *)(*poolHeader + 8) + 8);  // Size of each element in child list (stored in class descriptor at +8)
        do {
            int childPtr = *(int *)(childIter + 0x24);  // +0x24 seems to be a child pointer field
            if ((childPtr != 0) && ((*(byte *)(childPtr + 0x10) & 1) != 0)) {
                *(int *)(childIter + 0x24) = 0;  // Clear child pointer if flagged for deletion
            }
            childIter = *(int *)(childIter + elementSize);  // Move to next sibling (elementSize acts as stride)
        } while (childIter != 0);
    }

    // Phase 2: Traverse the global doubly-linked list of all objects (offset 0x10 = head)
    currentNode = *(int **)(this + 0x10);
    do {
        while( true ) {
            prevNode = currentNode;
            if (prevNode == 0) {
                return;
            }
            nextNode = (int *)prevNode[0x31];  // +0xC4 offset for next pointer
            if ((prevNode[4] & 1U) != 0) break;  // Flag bit 0: marked for deletion
            if ((prevNode[4] & 2U) == 0) {  // Flag bit 1: skip update
                (**(code **)(*prevNode + 0x10))();  // Virtual function at vtable+0x10 (update?)
            }
        }
        // Object is flagged for deletion; remove it from linked list
        if (prevNode == *(int **)(this + 0x10)) {
            // It's the head node
            *(int **)(this + 0x10) = nextNode;
            if (nextNode == 0) goto LAB_005190b8;
            nextNode[0x32] = 0;  // +0xC8 offset for previous pointer
            (**(code **)*prevNode)(1);  // Virtual destructor call (maybe operator delete)
        } else {
            if (prevNode[0x32] != 0) {
                *(int **)(prevNode[0x32] + 0xC4) = nextNode;  // Update previous node's next
            }
            if (nextNode != 0) {
                *(int *)(nextNode[0x32] + 0xC8) = prevNode[0x32];  // Update next node's previous
            }
            (**(code **)*prevNode)(1);  // Delete object
        }
    } while( true );
}