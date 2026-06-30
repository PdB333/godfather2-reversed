// FUNC_NAME: Node::operator=
// Assignment operator for a Node in a doubly-linked list structure with copy semantics.
// The node contains:
//   [0x00]: int m_id
//   [0x04]: Node* m_pPrev (or head pointer) – managed via linked list insertion/cleanup
//   [0x08]: Node* m_pNext (used during assignment to maintain list integrity)
//   [0x0C]: double m_double1
//   [0x14]: double m_double2
//   [0x1C]: int m_extra1
//   [0x20]: int m_extra2
//   [0x24]: int m_extra3
// Total size: 0x28 (40 bytes)

class Node {
public:
    int m_id;           // +0x00
    Node* m_pPrev;      // +0x04
    Node* m_pNext;      // +0x08
    double m_double1;   // +0x0C
    double m_double2;   // +0x14
    int m_extra1;       // +0x1C
    int m_extra2;       // +0x20
    int m_extra3;       // +0x24

    // Assignment operator (copy and manage linked list)
    Node& __thiscall operator=(const Node& other) {
        // Copy first field
        m_id = other.m_id;

        // Handle pointer field with linked list management
        if (this != &other) {
            int newPtr = other.m_pPrev;
            if (m_pPrev != newPtr) {
                if (m_pPrev != nullptr) {
                    releaseNode(&m_pPrev);  // FUN_004daf90: cleanup/dereference
                }
                m_pPrev = (Node*)newPtr;
                if (newPtr != 0) {
                    // Update linked list: adjust next pointer of this node
                    m_pNext = (Node*)((Node*)newPtr)->m_pNext;  // copy next from source's prev? Actually * (newPtr + 4)
                    ((Node*)newPtr)->m_pNext = this;            // set source's next to this
                }
            }
        }

        // Copy the remaining data (two doubles and three ints)
        m_double1 = other.m_double1;
        m_double2 = other.m_double2;
        m_extra1 = other.m_extra1;
        m_extra2 = other.m_extra2;
        m_extra3 = other.m_extra3;

        return *this;
    }

private:
    // Placeholder for the called cleanup function
    void releaseNode(Node** ptr);
};