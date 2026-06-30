// FUNC_NAME: ObjectList::findByID
// Address: 0x00624bd0
// Searches a singly linked list of objects for one whose ID matches the given value.
// The list head pointer is stored at offset 0x20 from 'this'.
// Each node has a vtable pointer at offset 0, and a next pointer at offset 0x28 (10th element).
// The virtual function at vtable[0] returns an integer ID.

undefined4* __thiscall ObjectList::findByID(int this, int id)
{
    // Get head of linked list
    undefined4* currentNode = *(undefined4**)(this + 0x20);
    if (currentNode == nullptr) {
        return nullptr;
    }
    do {
        // Save next pointer before potentially returning
        undefined4* nextNode = (undefined4*)currentNode[10]; // offset 0x28
        // Call virtual function to get ID of current node
        int nodeId = (**(int (__thiscall**)(undefined4*))(*currentNode))(); // vtable[0]
        if (nodeId == id) {
            return currentNode;
        }
        currentNode = nextNode;
    } while (nextNode != nullptr);
    return nullptr;
}