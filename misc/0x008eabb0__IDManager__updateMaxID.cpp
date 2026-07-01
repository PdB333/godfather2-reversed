// FUNC_NAME: IDManager::updateMaxID
// Function address: 0x008eabb0
// Role: Scans the linked list of nodes to recompute and cache the maximum ID value.

class IDManager {
public:
    struct Node {
        Node* next;   // +0x00
        int unknown1; // +0x04
        int unknown2; // +0x08
        int id;       // +0x0C
    };

    Node* firstNode;  // +0x00
    int field_4;      // +0x04
    int field_8;      // +0x08
    int cachedMaxID;  // +0x0C

    void updateMaxID() {
        if (cachedMaxID == -1) {
            int maxID = -1;
            Node* current = firstNode;
            while (current != nullptr) {
                if (maxID < current->id) {
                    maxID = current->id;
                }
                current = current->next;
            }
            cachedMaxID = maxID;
        }
    }
};