// FUNC_NAME: GameObject::~GameObject
// Function at 0x0045ca40: Destructor that removes this object from a circular doubly-linked list and optionally frees memory.
// This is likely part of the EARS engine's object management system.
// Object layout (offsets relative to this):
//   +0x00: vtable pointer (set to a destroyed-state vtable here)
//   +0x04: pointer to the list header (or sentinel node) – used to locate the list for removal
//   +0x08: 'next' pointer in the linked list (also used during removal)
// The linked list is circular with a sentinel whose 'next' field lives at this+0x04.
// The sentinel's address is &this->listHeaderPtr (i.e., this+0x04).
// The node to remove is identified by its 'next' pointer (this+0x08) being set or as the current node.

// __thiscall calling convention assumed
void __thiscall GameObject::~GameObject(GameObject *this, byte freeFlag)
{
    // +0x04: pointer to the list header
    uint32 *listHeader = this->listHeader;
    if (listHeader != 0) {
        // +0x04 in the list header: presumably its 'next' pointer
        uint32 **headerNext = (uint32 **)(listHeader + 1);
        uint32 *prevNode; // will hold the node before this one in the list

        if (*headerNext == (uint32 *)(&this->listHeader)) {
            // The only node in the list: update header's 'next' to this->next (which is effectively the sentinel)
            *headerNext = this->next;
        } else {
            // Walk the list to find the node whose 'next' points to this->listHeader (i.e., the node just before the sentinel)
            prevNode = (uint32 *)(*headerNext)[1];
            while (prevNode != (uint32 *)(&this->listHeader)) {
                headerNext = (uint32 **)(*headerNext)[1];
                prevNode = (uint32 *)(*headerNext)[1];
            }
            // Update that node's 'next' to skip this node
            *headerNext = this->next;
        }
    }

    // Mark object as destroyed by setting vtable to a static destroyed vtable
    this->vtable = &gDestroyedVtable; // PTR_LAB_00e2f0c0

    if ((freeFlag & 1) != 0) {
        // Free the memory (operator delete, but not named)
        FUN_009c8eb0(this);
    }
}