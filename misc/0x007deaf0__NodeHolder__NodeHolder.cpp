// FUNC_NAME: NodeHolder::NodeHolder
// Function address: 0x007deaf0
// Role: Constructor for an object that holds two linked list nodes tied to a parent object's event lists.
// The object at +0x58 points to a parent (likely a manager) with two linked lists at offsets 0x74c and 0x24b4.
// The nodes are stored at +0x74 and +0x7C (each 0x48 bytes?).

class NodeHolder {
public:
    // Vtable pointer set to PTR_LAB_00d6f6dc (assumed global vtable)
    // +0x00: vtable pointer

    // +0x58: pointer to parent manager (e.g., SimManager or GodfatherGameManager)
    void* m_parentManager;

    // +0x74: first node pointer (linked list node A)
    void* m_nodeA;          // offset 0x74
    // +0x78: next pointer for node A's list? (used for linked list linking)
    void* m_nodeANext;      // offset 0x78
    // +0x7C: second node pointer (linked list node B)
    void* m_nodeB;          // offset 0x7C
    // +0x80: next pointer for node B's list?
    void* m_nodeBNext;      // offset 0x80

    // Other fields likely present but not used here.

    __thiscall NodeHolder* NodeHolder() {
        // Base constructor call
        NodeHolder::baseConstructor();

        // Set vtable
        this->vtable = &PTR_LAB_00d6f6dc;

        // Initialize linked list nodes to null
        m_nodeA = nullptr;
        m_nodeANext = nullptr;
        m_nodeB = nullptr;
        m_nodeBNext = nullptr;

        // --- Node A setup (from parent at offset 0x74c) ---
        int* ptrFromParentA = *(int**)((char*)m_parentManager + 0x74c);
        int nodeAValue;
        if (ptrFromParentA == nullptr) {
            nodeAValue = 0;
        } else {
            nodeAValue = (int)ptrFromParentA - 0x48;
        }
        // Guard against sentinel (0x48)
        if (nodeAValue == 0) {
            nodeAValue = 0;
        } else {
            nodeAValue += 0x48;
        }

        if (m_nodeA != nodeAValue) {
            if (m_nodeA != 0) {
                // Remove old node from list (linked list removal)
                NodeHolder::removeNode(&m_nodeA);
            }
            m_nodeA = (void*)nodeAValue;
            if (nodeAValue != 0) {
                // Link into parent's list: set next pointer
                m_nodeANext = *(void**)(nodeAValue + 4);
                *(int**)(nodeAValue + 4) = &m_nodeA;
            }
        }

        // --- Node B setup (from parent at offset 0x24b4) ---
        int* ptrFromParentB = *(int**)((char*)m_parentManager + 0x24b4);
        int nodeBValue;
        if (ptrFromParentB == nullptr) {
            nodeBValue = 0;
        } else {
            nodeBValue = (int)ptrFromParentB - 0x48;
        }
        if (nodeBValue == 0) {
            nodeBValue = 0;
        } else {
            nodeBValue += 0x48;
        }

        if (m_nodeB != nodeBValue) {
            if (m_nodeB != 0) {
                NodeHolder::removeNode(&m_nodeB);
            }
            m_nodeB = (void*)nodeBValue;
            if (nodeBValue != 0) {
                m_nodeBNext = *(void**)(nodeBValue + 4);
                *(int**)(nodeBValue + 4) = &m_nodeB;
            }
        }

        // Debug logging
        NodeHolder::logMessage(0x27);  // message ID

        bool someFlag = NodeHolder::checkDebugFlag();  // FUN_00481660
        if (someFlag) {
            int value = (int)m_nodeB;
            if (value == 0 || value == 0x48) {
                value = 0;
            } else {
                value += 0x10;  // offset to some field inside node
            }
            NodeHolder::someDebugFunc(value);  // FUN_004a8ec0
            // Build log arguments
            int local_1c;   // uninitialized except byte set
            *((char*)&local_1c + 3) = 1;  // set highest byte to 1
            // Other arguments (local_20, local_24, local_c, local_4) uninitialized
            NodeHolder::debugPrint(3, 0x500000001, local_20, local_24, local_c, local_4); // FUN_0079fb90
        }

        return this;
    }

    // Placeholder for base constructor
    void baseConstructor();  // FUN_007ab5e0

    // Linked list removal (takes pointer to node pointer)
    void removeNode(void** nodePtr); // FUN_004daf90

    // Log a message
    void logMessage(int msgId); // FUN_007f63e0

    // Check some debug flag
    bool checkDebugFlag(); // FUN_00481660

    // Some debug operation
    void someDebugFunc(int value); // FUN_004a8ec0

    // Debug print with level and arguments
    void debugPrint(int level, int arg1, int arg2, int arg3, long long arg4, int arg5); // FUN_0079fb90
};