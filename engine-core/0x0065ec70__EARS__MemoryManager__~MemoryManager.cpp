// FUNC_NAME: EARS::MemoryManager::~MemoryManager

class EARS::MemoryManager {
public:
    // +0x00: vtable pointer
    // +0x04: linked list head (Node*) for free blocks or per-thread data
    // +0x14: first buffer pointer (freed)
    // +0x20: second buffer pointer (freed)
    // +0x2C: third buffer pointer (freed)
    // +0x30: thread handle (HANDLE)
    // +0x34: critical section (CRITICAL_SECTION)
    // +0x4C: thread local storage index (DWORD)

    // Node is 12 bytes: [0] field, [1] field, [2] next pointer
    struct Node {
        DWORD field0;   // +0x00
        DWORD field1;   // +0x04
        Node* next;     // +0x08
    };

    void __thiscall destructor(void) {
        // Step 1: Set vtable to own class vtable (ensures correct virtual dispatch during destruction)
        *(DWORD*)this = (DWORD)&g_VTableSelf;   // PTR_LAB_00e43500

        // Free TLS index
        TlsFree(*(DWORD*)((char*)this + 0x4C)); // offset 0x4C

        // Delete critical section
        DeleteCriticalSection((LPCRITICAL_SECTION)((char*)this + 0x34));

        // Close thread handle
        CloseHandle((HANDLE)*(DWORD*)((char*)this + 0x30));

        // Free allocated buffers
        free(*(void**)((char*)this + 0x2C));
        free(*(void**)((char*)this + 0x20));
        free(*(void**)((char*)this + 0x14));

        // Step 2: Set vtable to base class vtable (or sentinel) after cleanup
        *(DWORD*)this = (DWORD)&g_VTableBase;   // PTR_LAB_00e42de4

        // Free the linked list
        Node* node = *(Node**)((char*)this + 0x04);  // list head at +0x04
        while (node != nullptr) {
            Node* next = node->next;                 // node[2]
            // Clear node contents (possibly marking as freed)
            node->field0 = 0;
            node->field1 = 0;
            node->next = nullptr;
            node = next;
        }
    }
};