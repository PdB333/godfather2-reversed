// FUNC_NAME: KeyValueList::findValueByKey
// Address: 0x006fb2b0
// This function searches a linked list of key-value pairs.
// The list head is stored at this+0x10.
// Returns the value associated with the given key, or 0 (nullptr) if not found.

struct KeyValueNode {
    void* value;        // +0x00
    int key;            // +0x04
    KeyValueNode* next; // +0x08
};

class KeyValueList {
    // +0x10: head of the linked list
    KeyValueNode* head;

public:
    void* findValueByKey(int key) {
        KeyValueNode* node = head;
        while (node != nullptr) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        return nullptr;
    }
};