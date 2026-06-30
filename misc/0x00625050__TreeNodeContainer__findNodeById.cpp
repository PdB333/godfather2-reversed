// FUNC_NAME: TreeNodeContainer::findNodeById
// Function at 0x00625050 - Recursive tree node search by ID
// Searches a tree (children at +0x20, siblings at +0x28) for a node with matching virtual ID

class TreeNodeContainer; // Forward declaration

// Node structure with vtable and tree links
struct Node {
    // vtable pointer at offset 0x00
    virtual int getID() = 0; // vtable index 0: returns node ID

    // Tree structure offsets (relative to Node*)
    // +0x20: pointer to first child (Node*)
    // +0x28: pointer to next sibling (Node*)
    // Note: offsets are in bytes, but we'll use raw access
};

class TreeNodeContainer {
public:
    Node* m_rootNode; // +0x4, root of the search tree

    // Recursive search: startNode can be nullptr to begin from root
    // targetId is the ID to find (compared via node->getID())
    Node* findNodeById(int targetId, Node* startNode = nullptr) {
        // If no starting node provided, use the root
        if (startNode == nullptr) {
            startNode = m_rootNode;
            if (startNode == nullptr) {
                return nullptr;
            }
        }

        // Check if current node matches target ID
        int nodeId = startNode->getID();
        if (nodeId == targetId) {
            return startNode;
        }

        // Traverse children: get first child at offset 0x20
        Node* child = *(Node**)((char*)startNode + 0x20);
        if (child != nullptr) {
            // Recursively search each child and its siblings
            while (true) {
                // Save next sibling before recursion (at offset 0x28)
                Node* nextSibling = *(Node**)((char*)child + 0x28);
                Node* found = findNodeById(targetId, child);
                if (found != nullptr) {
                    return found;
                }
                if (nextSibling == nullptr) {
                    break;
                }
                child = nextSibling;
            }
        }
        return nullptr;
    }
};