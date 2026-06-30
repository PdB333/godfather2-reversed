// FUNC_NAME: TreeNode::hasFlagInSubtree
// Address: 0x006250e0
// Role: Recursively checks if any node in a tree (including this node) has bit0 set at offset 0x14.
// Structure: The tree node has children linked via singly linked list; offset 0x20 = first child, 0x28 = next sibling.
// The flag at +0x14 bit 0 indicates "active" or "marked" state.

class TreeNode {
public:
    // Offsets (relative to this):
    // +0x00: unknown (probably vtable or data)
    // +0x14: flags (byte, bit0 = activeFlag)
    // +0x20: pointer to first child (TreeNode*)
    // +0x28: pointer to next sibling (TreeNode*)

    bool hasFlagInSubtree() {
        // If this node itself has no children (likely bit0 indicates child existence? No, it's a flag on the node)
        if (this == nullptr) {
            return false;
        }

        // Check the flag on this node
        if ((*reinterpret_cast<unsigned char*>(this + 0x14) & 1) != 0) {
            return true;
        }

        // Otherwise, iterate over children (singly linked list starting at first child)
        TreeNode* child = *reinterpret_cast<TreeNode**>(reinterpret_cast<char*>(this) + 0x20);
        while (child != nullptr) {
            if (child->hasFlagInSubtree()) {
                return true;
            }
            child = *reinterpret_cast<TreeNode**>(reinterpret_cast<char*>(child) + 0x28);
        }

        return false;
    }
};