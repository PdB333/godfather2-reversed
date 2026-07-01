//FUNC_NAME: ObjectManager::removeObject
void __thiscall ObjectManager::removeObject(int this, int object)
{
    int node; // pointer to embedded list node at object+0x48
    int oldNext; // saved next pointer
    int containerFromHead; // container object derived from head node

    // Initialize node pointer: if object is null, node is null; else node points to the embedded list node at offset 0x48
    if (object == 0) {
        node = 0;
    } else {
        node = object + 0x48; // +0x48: embedded ListNode
    }

    // Save the old next pointer of the node and set it to point to the local node variable (stack address) – this is likely a temporary list head for removal
    oldNext = 0;
    if (node != 0) {
        oldNext = *(int *)(node + 4); // +0x04: ListNode::next
        *(int **)(node + 4) = &node; // set node->next = &node (temporary circular reference)
    }

    // Get the container object from the head node stored at this+0x24
    if (*(int *)(this + 0x24) == 0) { // +0x24: headNode pointer (points to a ListNode at offset 0x48 of some object)
        containerFromHead = 0;
    } else {
        containerFromHead = *(int *)(this + 0x24) - 0x48; // container = headNode - 0x48
    }

    // If the container of the head node is the same as the object being removed, update the head; otherwise unlink the node
    if (containerFromHead == object) {
        FUN_0094eea0(); // likely updates the head pointer (e.g., head = head->next)
    } else {
        FUN_0094ecf0(&node); // unlink the node from the list (node is a temporary list head)
    }

    // Global manager check: if the current object pointer matches the object's ID field, clear it
    if (*(int *)(DAT_01129938 + 0x28) == *(int *)(object + 100)) { // +0x28: currentObject, +100: objectId
        *(int *)(DAT_01129938 + 0x28) = 0;
    }

    // Cleanup: if node was non-null, call a destructor or finalizer on the temporary list head
    if (node != 0) {
        FUN_004daf90(&node); // likely frees or resets the temporary list head
    }
}