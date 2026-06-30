// FUNC_NAME: CallbackList::clearAndDestroyNodes
// Address: 0x00540670
// Iterates through a linked list of callback nodes, invokes each callback, then deletes all nodes and resets the list.

class CallbackList {
public:
    struct Node {
        void (*callback)();    // +0x00
        Node* next;            // +0x04
    };

    Node* head;                // +0x44
    int count;                 // +0x48

    void clearAndDestroyNodes() {
        uint i = 0;
        Node* current = this->head;
        int cnt = this->count;

        // First pass: call all callbacks
        if (cnt != 0) {
            do {
                current->callback();
                current = current->next;
                i++;
            } while (i < cnt);
        }

        // Second pass: free each node
        int nodeAddr = reinterpret_cast<int>(this->head);
        i = 0;
        if (cnt != 0) {
            do {
                int nextAddr = *reinterpret_cast<int*>(nodeAddr + 4); // Node::next
                FUN_009c8eb0(reinterpret_cast<void*>(nodeAddr));     // free node
                i++;
                nodeAddr = nextAddr;
            } while (i < cnt);
        }

        // Reset list
        this->head = nullptr;
        this->count = 0;
    }
};