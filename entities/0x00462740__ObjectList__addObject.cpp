// FUNC_NAME: ObjectList::addObject
// Function at 0x00462740: Adds an object to a doubly linked list with duplicate checking by ID.
// Class members:
//   +0x28: m_pHead (Node*)
//   +0x2c: m_pTail (Node*)
//   +0x30: m_nCount (int)
//   +0x34: m_pDefaultAllocator (void*)
//   +0x38: m_pAllocateFunc (void* pointer to vtable/allocator)
// Node layout (0xC bytes):
//   +0x00: m_pData (void*)
//   +0x04: m_pNext (Node*)
//   +0x08: m_pPrev (Node*)
// Object layout:
//   +0x70: m_pIDContainer (SomeIDContainer*)
//     +0x08: m_nID (int)

#include <cstddef>

// Forward declaration of the duplicate handler (FUN_00463560)
void handleDuplicate(void* param_1, void** param_2); // Callback when duplicate found

class ObjectList {
public:
    struct Node {
        void* m_pData;
        Node* m_pNext;
        Node* m_pPrev;
    };

    struct IDContainer {
        // ... possibly more fields
        int32_t m_nID; // +0x08
    };

    Node* m_pHead;          // +0x28
    Node* m_pTail;          // +0x2c
    int32_t m_nCount;       // +0x30
    void* m_pDefaultAllocator; // +0x34
    void* m_pAllocateFunc;  // +0x38 – pointer to a vtable/allocator function

    void addObject(void* pNewObject, void* unknownParam) {
        // Iterate over existing nodes to check for duplicate ID
        for (Node* pNode = m_pHead; pNode != nullptr; pNode = pNode->m_pNext) {
            // Compare the ID at offset 0x70->0x08
            IDContainer* curContainer = reinterpret_cast<IDContainer*>(pNode->m_pData) + 0x70; // but need to deref? Actually offset 0x70 from object, not from node data. Correct: In code: *(int *)(param_3 + 0x70) gives a pointer, then +8 gives ID. So:
            int32_t curID = *reinterpret_cast<int32_t*>(*reinterpret_cast<char**>(pNode->m_pData) + 0x70 + 0x08);
            // Wait, the decompiled: *(int *)(*(int *)(param_3 + 0x70) + 8)
            // So first cast: char* base = (char*)pNode->m_pData
            // Then char* containerPtr = *(char**)(base + 0x70)
            // Then int32_t id = *(int32_t*)(containerPtr + 0x08)
            // Similarly for new object:
            int32_t newID = *reinterpret_cast<int32_t*>(*reinterpret_cast<char**>(pNewObject) + 0x70 + 0x08);
            // Check equality
            if (curID == newID) {
                // Duplicate found – call handler and return
                handleDuplicate(unknownParam, &pNewObject);
                return;
            }
        }

        // No duplicate – allocate new node using custom allocator
        Node* pNewNode = nullptr;
        void* allocator = m_pDefaultAllocator;
        if (allocator == nullptr) {
            allocator = &g_DefaultAllocator; // some global default, address 0x01218a14
        }

        // Allocate 12 bytes (sizeof(Node)) via function pointer at m_pAllocateFunc
        if (m_pAllocateFunc != nullptr) {
            // The allocation function is called as: (**(code**)(*(undefined4**)(param_2 + 0x38)))(0xc, allocator)
            // So m_pAllocateFunc points to a vtable; first entry is allocate method
            auto allocVtable = reinterpret_cast<void**>(m_pAllocateFunc);
            using AllocFunc = void* (*)(size_t size, void* allocator);
            auto allocFunc = reinterpret_cast<AllocFunc>(allocVtable[0]); // or perhaps allocVtable is the function itself? The code double-dereferences: **(code **)**(undefined4 **)(param_2 + 0x38). So m_pAllocateFunc is a pointer to a pointer to a function? Actually: param_2+0x38 is a pointer to some structure (maybe another void*). So we have a pointer (let's call pAllocInterface = *(void**)(this+0x38)). Then the first 4 bytes of that interface is a function pointer. So:
            void* pAllocInterface = *(void**)(reinterpret_cast<char*>(this) + 0x38);
            auto allocFunc = *reinterpret_cast<void* (*)(size_t, void*) *>(pAllocInterface);
            pNewNode = reinterpret_cast<Node*>(allocFunc(12, allocator));
        }

        if (pNewNode != nullptr) {
            pNewNode->m_pData = pNewObject;
            pNewNode->m_pNext = nullptr;
            pNewNode->m_pPrev = nullptr;

            // Insert at tail of list
            if (m_pTail != nullptr) {
                m_pTail->m_pNext = pNewNode;
                pNewNode->m_pPrev = m_pTail;
            }
            m_pTail = pNewNode;
            if (m_pHead == nullptr) {
                m_pHead = pNewNode;
            }
            m_nCount++;
        }
    }
};

// Global default allocator (address 0x01218a14)
extern void* g_DefaultAllocator;