// FUNC_NAME: EARSQueue::~EARSQueue

extern const void* PTR_LAB_00e434f0; // vtable pointer for this class
extern const void* PTR_LAB_00e42de4; // vtable pointer for base class

struct ListNode {
    uint32_t field0;      // +0x00
    uint32_t field4;      // +0x04
    ListNode* next;       // +0x08
};

class EARSQueue {
public:
    const void* vtable;          // +0x00
    ListNode* head;              // +0x04
    // ... other fields (padding assumed) ...
    HANDLE hEvent;               // +0x10 (event or semaphore handle)

    ~EARSQueue() {
        // Set vtable to this class (child)
        this->vtable = &PTR_LAB_00e434f0;

        // Close the kernel handle
        CloseHandle(this->hEvent);

        // Switch vtable to base class before clearing inherited data
        this->vtable = &PTR_LAB_00e42de4;

        // Free all nodes in the linked list
        ListNode* cur = this->head;
        while (cur != nullptr) {
            ListNode* next = cur->next;
            cur->field0 = 0;
            cur->field4 = 0;
            cur->next = nullptr;
            cur = next;
        }
        // Note: nodes themselves are not freed (likely managed externally)
    }
};