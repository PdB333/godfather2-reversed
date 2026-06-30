// FUNC_NAME: ListManager::removeByObject
// Function at 0x006fa060: Removes an object from an intrusive linked list managed by this class.
// The list holds pointers to an embedded member at offset 0x48 within the object.
// There is also a direct pointer stored at this+0x3c to a similar embedded member (possibly head).
void __thiscall ListManager::removeByObject(void* this, void* objectPtr)
{
    void* derivedBase;
    void* listNode;
    void* savedObject = objectPtr;

    // Derive the base pointer from the direct pointer at this+0x3c (if non-null)
    if (*(int*)((char*)this + 0x3c) == 0) {
        derivedBase = 0;
    } else {
        derivedBase = (void*)(*(int*)((char*)this + 0x3c) - 0x48); // +0x3c: direct pointer to embedded member
    }

    // If the object matches this special direct reference, handle it separately
    if (objectPtr == derivedBase) {
        FUN_006faa40(); // likely handleRemovalOfDirectEntry
    }

    // Walk the linked list at this+0x6d4
    listNode = *(void**)((char*)this + 0x6d4); // +0x6d4: pointer to list head
    if (listNode != 0) {
        while (true) {
            // Derive object base from the node's stored pointer (+0x10)
            if (*(int*)((char*)listNode + 0x10) == 0) {
                derivedBase = 0;
            } else {
                derivedBase = (void*)(*(int*)((char*)listNode + 0x10) - 0x48); // +0x10: pointer to embedded member
            }

            if (savedObject == derivedBase) {
                break; // Found matching node
            }

            // Move to next node (list is singly linked via +0x18)
            if (listNode == 0) {
                listNode = 0;
            } else {
                listNode = *(void**)((char*)listNode + 0x18); // +0x18: next pointer
            }

            if (listNode == 0) {
                return; // Not found, exit
            }
        }

        // Remove the found node from the list; pass addresses of 'this' and the node pointer
        FUN_006f9a10(&this, &listNode); // likely unlinkNode(this, &node)
    }
    return;
}