// FUNC_NAME: NodeManager::attachChildren

// This function iterates over a list of child nodes and attaches each to a parent node.
// For each child, it sets a child pointer (based on type) to an embedded sub-node within the child.
// If the child already has that pointer set, the function returns early.
// Then, if a specific flag in the child (depending on type) is zero, it calls the notification function.
// Offsets are relative to this (NodeManager object).

class TreeNode;

class NodeManager {
public:
    // +0x1C: some condition/flag
    int m_conditionFlag; 
    
    // +0x2C: number of children in the array
    int m_childCount; 
    
    // +0x30: pointer to array of TreeNode pointers
    TreeNode** m_childArray; 
    
    // +0x3C: another count (used to determine uVar3)
    int m_auxCount; 
    
    // +0x40: value passed to notification function
    void* m_notificationParam; 

    // Member function (__thiscall) that processes children
    void attachChildren();
};

class TreeNode {
public:
    // +0x04: type identifier (byte)
    uint8_t m_type; 
    
    // +0x20: flag for types < 10
    int m_flagLow; 
    
    // +0x24: child pointer for types < 10 (points to embedded node at +0x30)
    TreeNode* m_childLow; 
    
    // +0x28: flag for types >= 10
    int m_flagHigh; 
    
    // +0x2C: child pointer for types >= 10 (points to embedded node at +0x40)
    TreeNode* m_childHigh; 
    
    // +0x30: embedded sub-node (used when type < 10)
    // (treated as TreeNode* when linked)
    // +0x40: embedded sub-node (used when type >= 10)
};

// Forward declaration of notification function (FUN_00580ec0)
void notifyChildAttached(void* param);

void NodeManager::attachChildren() {
    if (this == nullptr) {
        return;
    }

    void* notifParam = nullptr;
    if (m_conditionFlag != 0 && m_auxCount > 0) {
        notifParam = m_notificationParam;
    }

    if (m_childCount <= 0) {
        return;
    }

    for (int i = 0; i < m_childCount; i++) {
        TreeNode* child = m_childArray[i];
        uint8_t type = child->m_type; // only low byte

        if (type < 10) {
            // For types 0-9, set the low child pointer to the embedded node at +0x30
            if (child->m_childLow != nullptr) {
                // Already linked, abort entire process
                return;
            }
            child->m_childLow = reinterpret_cast<TreeNode*>(reinterpret_cast<char*>(child) + 0x30);
        } else {
            // For types 10 and above, set the high child pointer to embedded node at +0x40
            if (child->m_childHigh != nullptr) {
                return;
            }
            child->m_childHigh = reinterpret_cast<TreeNode*>(reinterpret_cast<char*>(child) + 0x40);
        }

        // Check the appropriate flag field for zero
        uint flagValue;
        if (type < 10) {
            flagValue = child->m_flagLow;
        } else {
            flagValue = child->m_flagHigh;
        }

        // Mask off the upper 4 bits (28 bits used)
        if ((flagValue & 0x0FFFFFFF) == 0) {
            notifyChildAttached(notifParam);
        }
    }
}

// Note: notifyChildAttached corresponds to FUN_00580ec0. Its purpose is unknown,
// but likely triggers an event or initialization for the attached child.