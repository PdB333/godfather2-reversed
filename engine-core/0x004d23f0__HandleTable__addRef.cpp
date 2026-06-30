// FUNC_NAME: HandleTable::addRef
int __fastcall HandleTable::addRef(unsigned int handle)
{
    // Hash the handle to index into the 0x2000-slot table
    HandleNode *node = s_handleTable[handle & 0x1FFF];
    if (node != nullptr) {
        while (node->handleID != handle) {
            node = node->next;
            if (node == nullptr) {
                return -1;
            }
        }
        // Node found – increment its reference count atomically
        // (actual code uses LOCK/UNLOCK macros for a global spinlock)
        //
        // LOCK();
        int oldRef = node->refCount;
        node->refCount = oldRef + 1;
        // UNLOCK();
        return oldRef + 1;
    }
    return -1;
}

// Structure of a handle table node (offsets relative to int* base):
// +0x00: refCount (int)
// +0x04: unknown1 (int)
// +0x08: unknown2 (int)
// +0x0C: handleID (int)
// +0x10: next (HandleNode*)
struct HandleNode {
    int refCount;       // +0x00
    int unknown1;       // +0x04
    int unknown2;       // +0x08
    int handleID;       // +0x0C
    HandleNode *next;   // +0x10
};

// Global handle table – array of 0x2000 pointers to linked lists
// (address: DAT_012054ac)
static HandleNode *s_handleTable[0x2000];