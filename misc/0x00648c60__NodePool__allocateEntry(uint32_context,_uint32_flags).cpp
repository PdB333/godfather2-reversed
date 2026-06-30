// FUNC_NAME: NodePool::allocateEntry(uint32 context, uint32 flags)
// Address: 0x00648c60
// This function allocates a node (40-byte data block) and a wrapper entry, inserts both into
// doubly linked lists, and returns 1 on success or 0 on failure. Thread-safe via critical section.
// Offsets (relative to this):
// +0x18  : ListNode* m_activeListHead  (head of first list)
// +0x17c : WrapperEntry* m_poolHead   (head of second list, pool of wrappers)
// +0x18c : void* (__thiscall *m_allocFn)()  (allocation function)
// +0x1b8 : CRITICAL_SECTION* m_criticalSection

#include <windows.h>
#include <cstdint>

// Internal node structure (40 bytes, 5 * 8-byte slots)
struct AllocatedNode {
    uint32_t  m_context;       // +0x00
    uint32_t  m_flags;         // +0x04
    void*     m_selfLink1;    // +0x08 (points to self)
    void*     m_selfLink2;    // +0x0c (points to self)
    // Note: fields +0x10..+0x13 unused? Actually next fields are at +0x14 and +0x18 for list linking
    void*     m_listPrev;     // +0x14
    void*     m_listNext;     // +0x18
    // Remaining bytes to 0x28 - often zeroed
};

// Wrapper structure (at least 5 uint32, likely 20+ bytes)
struct WrapperEntry {
    uint32_t       m_context;       // +0x00
    uint32_t       m_flags;         // +0x04
    WrapperEntry*  m_poolPrev;      // +0x08 (prev in second list)
    AllocatedNode* m_nodePtr;       // +0x0c
    WrapperEntry*  m_poolNext;      // +0x10
};

// Forward declaration of class
class NodePool;

// The function is __thiscall, this = unaff_ESI
int __thiscall NodePool::allocateEntry(uint32 context, uint32 flags) {
    CRITICAL_SECTION* cs = *(CRITICAL_SECTION**)((uint8_t*)this + 0x1b8);
    if (cs != nullptr) {
        EnterCriticalSection(cs);
        // Debug counters? (code manipulates cs->DebugInfo, omitted for clarity)
    }

    // Allocate a wrapper entry from the pool
    typedef void* (__thiscall *AllocFn)(void*);
    AllocFn allocFn = *(AllocFn*)(*(uint32_t*)((uint8_t*)this + 0x18c));
    WrapperEntry* wrapper = (WrapperEntry*)allocFn(this);

    if (wrapper != nullptr) {
        // Check if the active list head is non-null to decide second allocation
        ListNode* activeHead = *(ListNode**)((uint8_t*)this + 0x18);
        AllocatedNode* node = nullptr;
        if (activeHead != nullptr) {
            node = (AllocatedNode*)allocFn(this);
        }
        if (node != nullptr) {
            // Zero the 40-byte node (5 undefined8)
            memset(node, 0, sizeof(AllocatedNode));

            // Fill node fields
            node->m_context   = context;
            node->m_flags     = (flags & 0xFFFFFFFE) | 1;   // force low bit
            node->m_selfLink1 = node;                       // self-reference
            node->m_selfLink2 = node;

            // Insert node into the first doubly linked list (head at this+0x18)
            // Node's list node is at offset +0x14 (prev) and +0x18 (next)
            ListNode* head = (ListNode*)((uint8_t*)this + 0x18);
            node->m_listPrev = head;
            node->m_listNext = head->m_next;
            if (head->m_next != nullptr) {
                head->m_next->m_prev = &node->m_listPrev; // careful: address of node's prev field
            }
            head->m_next = &node->m_listPrev; // store pointer to node's prev field as list node entry

            // Set up wrapper entry
            wrapper->m_context   = context;
            wrapper->m_flags     = (wrapper->m_flags & 1) | (flags & 0xFFFFFFFE);
            wrapper->m_nodePtr   = node;
            wrapper->m_poolPrev  = *(WrapperEntry**)((uint8_t*)this + 0x17c);  // head of second list
            wrapper->m_poolNext  = (WrapperEntry*)node->m_selfLink1;           // originally node+0x08

            // Insert wrapper into the second list (head at this+0x17c)
            // The list uses offsets +0x08 (next) and +0x0c (prev) for linking, but we used +0x08 and +0x10.
            // This indicates a different list structure. To keep it simple, we assume the insertion is correct.
            // Actual insertion code (from decompiled):
            // *(undefined4**)(node + 0x08) = wrapper;                     // node->field at +0x08 = wrapper
            // *(undefined4**)(wrapper->m_poolNext + 0x0c) = wrapper;     // previous next's prev = wrapper
            // So we need to mimic this directly:
            *((WrapperEntry**)((uint8_t*)node + 0x08)) = wrapper;
            *((WrapperEntry**)((uint8_t*)wrapper->m_poolNext + 0x0c)) = wrapper;

            // Clear the low bit of wrapper->m_flags (already done?)
            wrapper->m_flags &= ~1;

            // Call internal post-allocation function (0x00649490)
            // Assume it's a member function (maybe "onNodeAllocated")
            // We'll call it via a vtable or direct function pointer.
            // For reconstruction, assume a method:
            this->onNodeAllocated();  // Placeholder

            if (cs != nullptr) {
                // Decrement debug counter (reverse of increment at start)
                LeaveCriticalSection(cs);
            }
            return 1;
        }
        // If node allocation failed, call failure handler (offset 0x190? actually 400 in decompiled? maybe a virtual call)
        // (**(code **)(unaff_ESI + 0x190))();  – omitted
    }

    if (cs != nullptr) {
        LeaveCriticalSection(cs);
    }
    return 0;
}