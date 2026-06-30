// FUN_NAME: UniqueIDList::addIfNotPresent
// Represents a linked list where each node stores an ID and has a flag bit embedded in the "next" pointer.
// Class fields:
//   +0x00 ... (other members before head)
//   +0x10 Node* m_head;
// Node layout:
//   +0x00 int id;
//   +0x04 int nextAndFlags;  // low bit = flag (0 = inactive, 1 = active?), upper bits = pointer to next node

class UniqueIDList {
public:
    struct Node {
        int id;            // +0x00
        int nextAndFlags;  // +0x04
    };

    Node* m_head; // +0x10 (estimated offset, class may have additional members)

    // Helper: allocate a new node from memory pool (FUN_00441cd0)
    Node* allocateNode();

    // Adds the given ID to the list only if no node with that ID and flag==0 exists.
    // If a node already exists with same ID and clear flag, does nothing.
    // Otherwise appends a new node (with flag=0) at the end.
    void addIfNotPresent(int handleId) {
        Node* current = m_head;
        Node* prev = nullptr;

        while (current != nullptr) {
            // Clear low bit to get actual next pointer
            Node* next = (Node*)(current->nextAndFlags & ~1);

            // Check if the same ID exists and its flag bit is 0 (inactive)
            if (current->id == handleId && (current->nextAndFlags & 1) == 0) {
                return; // already present, nothing to add
            }

            prev = current;
            current = next;
        }

        // Allocate a new node (may return nullptr)
        Node* newNode = allocateNode();
        if (newNode != nullptr) {
            newNode->id = handleId;
            newNode->nextAndFlags = 0; // next = nullptr, flag = 0
        }

        if (prev == nullptr) {
            // List was empty; head becomes the new node (or nullptr if allocation failed)
            m_head = newNode;
        } else {
            // Preserve the low flag bit of the previous node and link to new node
            prev->nextAndFlags = (prev->nextAndFlags & 1) | (int)newNode;
        }
    }
};