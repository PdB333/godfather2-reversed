// FUNC_NAME: LinkedList::replaceHead
// Function at 0x007689d0: Replaces the head node of a linked list, detaching the old head and attaching a new node.
// The list uses an intrusive node structure: each node at offset +0x48 within the object, with a back pointer at +0x4.
// This+0x70 is the head pointer, +0x74 stores the previous back pointer for list management.

void __thiscall LinkedList::replaceHead(int newObject) {
    int* headPtr = reinterpret_cast<int*>(this + 0x70); // +0x70: pointer to current head node
    int* newNode = nullptr;
    if (newObject != 0) {
        newNode = reinterpret_cast<int*>(newObject + 0x48); // +0x48: offset of node within the given object
    }
    if (*headPtr != reinterpret_cast<int>(newNode)) {
        if (*headPtr != 0) {
            removeListHead(headPtr); // 0x004daf90: detach old head node from the list
        }
        *headPtr = reinterpret_cast<int>(newNode);
        if (newNode != nullptr) {
            // Save the node's current back pointer into the list head's saved pointer
            *reinterpret_cast<int*>(this + 0x74) = *(newNode + 4); // +0x74: stores the old back pointer
            // Point the node's back pointer to the list head pointer itself
            *reinterpret_cast<int**>(newNode + 4) = headPtr; // node+0x4 now points to &this->head
        }
    }
}