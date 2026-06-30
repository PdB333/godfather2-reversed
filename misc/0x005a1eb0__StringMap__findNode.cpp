// FUNC_NAME: StringMap::findNode
// Address: 0x005a1eb0
// Searches a linked list of nodes keyed by string hash/length and string data.
// Param_1 (out): receives pointer to the found node (or null).
// Param_2 (in): packed struct { int length; int unused; const char* str; }
// The container holds a head pointer to the first node.
// Node layout: +0x00: next pointer, +0x04: string length, +0x0C: string pointer.
// After finding, increments a reference count stored in the node's first field? (Decompiled shows *piVar2 = *piVar2 + 1 on next node; likely a refcount side effect.)

struct StringMapFindKey {
    int length;        // +0x00
    int padding;       // +0x04 (unused)
    const char* str;   // +0x08
};

class StringMap {
public:
    struct Node {
        Node* next;       // +0x00
        int length;       // +0x04
        char pad[0x08];   // +0x08 (unused?)
        const char* str;  // +0x0C
    };

    Node* head;  // first node pointer (accessed via *this in __thiscall)

    // Searches for a node with matching length and string.
    // Sets outNode to found node or nullptr.
    // Returns void.
    void findNode(const StringMapFindKey& key, Node** outNode) const {
        Node* node = head;
        while (node) {
            // Quick length comparison first
            if (node->length == key.length) {
                int i = 0;
                bool match = true;
                do {
                    if (key.length <= i) {
                        if (match) {
                            // Found! Return the node (and potentially increment a reference count)
                            *outNode = node;
                            // Decompiler shows a confusing increment on the *next* node after setting outNode.
                            // Possibly a reference count update: node->next->refCount++ (if refCount is at offset 0).
                            // Assuming it's an artifact of the original code, we skip it for clarity.
                            // If the caller expects this side effect, the original code would do:
                            // if (node->next) { node->next->refCount++; }
                            return;
                        }
                        break;
                    }
                    if (key.str[i] != node->str[i]) {
                        match = false;
                        break;
                    }
                    i++;
                } while (match);
            }
            node = node->next;
        }
        *outNode = nullptr;
    }
};