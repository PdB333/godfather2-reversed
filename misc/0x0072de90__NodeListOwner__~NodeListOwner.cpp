// FUNC_NAME: NodeListOwner::~NodeListOwner

struct ListNode {
    ListNode* next;       // +0x00
    void* data;           // +0x04 (maybe data pointer, set to 0)
};

class NodeListOwner {
public:
    void** vtable;          // +0x00
    ListNode* listHead;     // +0x04
    void* subObject;        // +0x08 (another owned resource, cleaned by FUN_004daf90)

    // Destructor
    __thiscall ~NodeListOwner(byte deleteFlag) {
        // If sub-object exists, destroy it
        if (subObject != 0) {
            FUN_004daf90(&subObject);
        }

        // Set vtable pointer (class identity)
        vtable = (void**)0x00e32808;

        // Iterate over linked list and clear each node
        ListNode* node = listHead;
        while (node != 0) {
            ListNode* nextNode = node->next;
            node->next = 0;
            node->data = 0;
            node = nextNode;
        }

        // If delete flag set, free this memory
        if ((deleteFlag & 1) != 0) {
            FUN_009c8eb0(this);
        }
    }

    // External functions (from other modules)
    void __thiscall FUN_004daf90(void** obj);
    void __cdecl FUN_009c8eb0(void* ptr);
};