// FUNC_NAME: RefCountedPointer::assign
// Function at 0x0056f6e0: Assigns a new object to a reference-counted pointer member.
// The class holds a member at this+0x3C (m_pTarget) which points to a ref-counted node.
// Node structure: +0x00: prev, +0x04: next, +0x08: deadFlag (byte), +0x09: refCount (byte).
// Global g_freeList (at 0x01205588) manages a doubly-linked list of free/active nodes.

struct RefCountedNode {
    RefCountedNode* prev;       // +0x00
    RefCountedNode* next;       // +0x04
    char deadFlag;              // +0x08 == 0 means dead (can be freed)
    char refCount;              // +0x09 reference counter
};

// Global free list structure (address 0x01205588)
struct FreeList {
    RefCountedNode* head;       // +0x00
    RefCountedNode* tail;       // +0x04
    RefCountedNode* somePtr;    // +0x08 (used as temporary)
    RefCountedNode* spare;      // +0x0C
};

extern FreeList g_freeList;

class RefCountedPointer {
    RefCountedNode* m_pTarget; // offset +0x3C

public:
    void assign(RefCountedNode* newTarget) {
        // Step 1: increment new target's ref count
        if (newTarget != nullptr) {
            newTarget->refCount++;
        }

        // Step 2: release old target
        RefCountedNode* oldTarget = this->m_pTarget;
        if (oldTarget != nullptr) {
            oldTarget->refCount--;

            // Check if old target can be removed from global list
            if (oldTarget->deadFlag == 0 && oldTarget->refCount == 0) {
                // Unlink oldTarget from the global list
                RefCountedNode* prev = oldTarget->prev;
                RefCountedNode* next = oldTarget->next;

                if (prev != nullptr) {
                    prev->next = next;
                } else {
                    // oldTarget was head; update head pointer
                    g_freeList.head = next;
                    if (next == nullptr) {
                        g_freeList.head = g_freeList.tail; // might not be correct but matches decompiled logic
                    }
                }

                if (next != nullptr) {
                    next->prev = prev;
                }

                // Update the free list's somePtr (maybe used for allocation)
                // The original code does: *(undefined4 *)(&g_freeList + 8) = *(undefined4 *)(&g_freeList + 4);
                // then sets g_freeList.tail to prev (iVar2)
                // Basically: g_freeList.somePtr = g_freeList.tail;
                //             g_freeList.tail = prev;
                //             if (prev == 0) { g_freeList.somePtr = g_freeList.spare; }
                g_freeList.somePtr = g_freeList.tail;
                g_freeList.tail = prev;
                if (prev == nullptr) {
                    g_freeList.somePtr = g_freeList.spare;
                }
            }
        }

        // Step 3: assign new target
        this->m_pTarget = newTarget;
    }
};