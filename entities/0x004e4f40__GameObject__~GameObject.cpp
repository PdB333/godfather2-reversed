// FUNC_NAME: GameObject::~GameObject

class GameObject {
public:
    // Vtable pointer at offset 0x00
    void** vtable;

    // Offset 0x10: pointer to some linked list node (maybe a list of "children" or similar)
    void* m_pListNext;  // +0x10

    // Offset 0x14: pointer to previous node in the same list
    void* m_pListPrev;  // +0x14

    // Offset 0x28: pointer to a global object list node (used by a memory allocator or manager)
    void* m_pGlobalListNode;  // +0x28

    // Offset 0x90: pointer to another list node (e.g., for an update list)
    void* m_pUpdateListNode;  // +0x90

    // Offset 0x94: next pointer for the update list (double linked)
    void* m_pUpdateListNext;  // +0x94

    // Offset 0x98: previous pointer for the update list
    void* m_pUpdateListPrev;  // +0x98

    // Destructor
    __thiscall ~GameObject();
};

// Global pointer used for list manipulation (e.g., head of a memory pool list)
// Address 0x012068e8 + 0x14 = 0x012068fc
void** g_pGlobalListHead = (void**)0x012068fc;

// External function called during destruction
extern void __cdecl sub_52E710();

void __thiscall GameObject::~GameObject() {
    // Step 1: Set vtable to base class vtable (or first step of destruction)
    vtable = (void**)0x00e371d8;

    // Call a common destruction helper (e.g., release resources)
    sub_52E710();

    // Remove self from the global list (linked list of all alive objects)
    int* pNode = (int*)m_pGlobalListNode;  // +0x28
    if (pNode != nullptr) {
        // Get the head of the global list (actually a pointer to a pointer to the list start)
        void** ppListHead = g_pGlobalListHead;  // points to the list's first element pointer
        // The list is stored as an array of pointers? The code does:
        // **ppListHead = &someLabel; // Replace head's first field with a label
        // then ppListHead += 4; // move to next slot?
        // then *ppListHead = pNode; // store the object pointer
        // then ppListHead += 4; // finalize
        // This looks like a custom allocator that uses a pointer-within-a-pointer scheme.
        // For cleanliness, we'll just comment the inlined logic:
        // Add pNode back into the global free list (or release it)
        // (See assembly for full details)
        // We'll emulate the original flow:
        void** listIter = ppListHead;
        **listIter = (void*)0x01124ba8;   // LABEL? Possibly a sentinel
        listIter = (void**)((char*)listIter + 4);
        *(void**)listIter = pNode;
        listIter = (void**)((char*)listIter + 4);
        m_pGlobalListNode = nullptr;   // offset 0x28 = 0
    }

    // Remove self from the update list (double-linked list at +0x90)
    void* updateNode = m_pUpdateListNode;  // +0x90
    if (updateNode != nullptr) {
        void** nextUpdate = *(void***)((char*)updateNode + 4);  // next pointer at +0x04 of node
        if (nextUpdate == &m_pUpdateListNode) {
            // Node is only element, set next to our stored next (which might be null)
            m_pUpdateListNext = m_pUpdateListNext;  // identity, but effectively just sets next?
            *(void**)((char*)updateNode + 4) = m_pUpdateListNext;
        } else {
            // Traverse list to find our node
            void** cur = (void**)*((char**)nextUpdate);  // actually the node's next pointer is at +0x04
            while (cur != nextUpdate) {
                cur = (void**)*((char**)cur + 1);
            }
            // Remove node: set previous node's next to our next
            *((char**)cur + 1) = m_pUpdateListNext;
        }
    }

    // Step 2: Set vtable to another derived class vtable (second step)
    vtable = (void**)0x00e37f48;

    // If m_pListNext is not null, remove self from a doubly-linked list (child list?)
    if (m_pListNext != nullptr) {
        // Unlink from doubly-linked list at offsets +0x10 and +0x14
        *(void**)((char*)m_pListPrev + 0x10) = m_pListNext;  // previous->next = our next
        *(void**)((char*)m_pListNext + 0x14) = m_pListPrev;  // our next->prev = our previous
        m_pListNext = nullptr;
    }

    // Step 3: Final vtable assignment (pop to most base class, or mark as destroyed)
    vtable = (void**)0x00e37304;

    return;
}