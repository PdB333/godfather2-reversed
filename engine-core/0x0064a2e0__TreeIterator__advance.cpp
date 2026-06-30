// FUNC_NAME: TreeIterator::advance
// Function address: 0x0064a2e0
// Description: Advances the iterator to the next element in a tree structure.
// Returns pointer to output structure (this+0x0C) if valid element found, else NULL.
// The tree is a linked structure of nodes (TreeNode) each containing a linked list of children (TreeChild).
// Only nodes with flags >= 2 (i.e., low bit not set and at least bit1 set) are considered valid.
// The additionalFilter parameter is ANDed with the stored filterMask to control which children are included:
//   bit1 (2) = include children with low bit clear? bit2 (4) = include children with low bit set?
// The endSentinel is a pointer to a sentinel node; traversal stops when the node pointer equals endSentinel+4.
// The output fields are populated from the current child.

class TreeIterator {
public:
    // Iterator state (relative offsets):
    uint filterMask;            // +0x00: base filter mask
    TreeNode* currentNode;      // +0x04: current node being traversed
    TreeChild* currentChild;    // +0x08: current child within the node

    // Output structure (start at offset 0x0C):
    struct Output {
        uint* dataPtr;          // +0x0C: pointer to data from child's first child? (child->data->???)
        TreeChild* child;       // +0x10: pointer to current child
        uint childFlagsCleared; // +0x14: child->flags & 0xFFFFFFFE (low bit cleared)
        uint childField2;       // +0x18: child->field2 (third uint in child)
        uint childSize;         // +0x1C: (childFlagsCleared - childField2) + child->field0
        char direction;         // +0x20: traversal direction hint (2 or 4)
    };

    // Advance the iterator. Returns pointer to output, or NULL if no more elements.
    Output* advance(uint additionalFilter, TreeNode* endSentinel);
};

// Node structure (not fully known, only used offsets):
struct TreeNode {
    uint field0;        // +0x00 (not directly used)
    uint flags;         // +0x04: node flags (bit0 = ? ignore; must have other bits set to be valid)
    uint padding[2];    // +0x08, +0x0C
    TreeChild* firstChild; // +0x10: first child in linked list
    TreeNode* sibling;  // +0x18: next sibling node
};

// Child structure (offsets from child pointer):
struct TreeChild {
    uint field0;        // +0x00: some value (used in size calculation)
    uint flags;         // +0x04: flags (bit0 used for filtering, others for size)
    uint field2;        // +0x08: used in size calculation
    int padding;        // +0x0C (assumed)
    TreeChild* next;    // +0x10: next child in linked list
};

TreeIterator::Output* TreeIterator::advance(uint additionalFilter, TreeNode* endSentinel) {
    if (this == nullptr) {
        return nullptr;
    }

    uint combinedMask = additionalFilter & filterMask;
    TreeNode* endNodeAddr = endSentinel + 4; // sentinel address for termination

    // Current node
    uint nodeAddr = reinterpret_cast<uint>(currentNode);
    uint endAddr = reinterpret_cast<uint>(endNodeAddr);

    while (nodeAddr != endAddr) {
        TreeNode* node = currentNode;
        // Check if node is valid (flags & 0xFFFFFFFE) != 0 i.e., low bit cleared and some other bit set
        if ((node->flags & 0xFFFFFFFE) == 0) {
            // Node is invalid; skip to next sibling
            do {
                currentNode = reinterpret_cast<TreeNode*>(node->sibling);
                nodeAddr = reinterpret_cast<uint>(currentNode);
                if (nodeAddr == endAddr) break;
            } while ((currentNode->flags & 0xFFFFFFFE) == 0);
            currentChild = nullptr;
        } else {
            // Node is valid; find a suitable child
            TreeChild* child;
            if (currentChild == nullptr) {
                child = node->firstChild;
            } else {
                child = reinterpret_cast<TreeChild*>(currentChild->next);
            }

            currentChild = child;

            // Iterate through children of this node until we find one that matches the filter
            while (child != node) { // child != node ensures we don't go past the end? Actually it compares pointers of different types; in assembly uVar3 != uVar1 where uVar1 is node address, so child pointer compared to node pointer. Child struct is different, but comparison by address is valid because they are different objects.
                // Check if combinedMask includes both bits (2 and 4) -> accept all
                if ((combinedMask & 6) == 6) break;

                // Get the low bit of child's flags
                uint childLowBit = child->flags & 1;

                // Determine if child is acceptable based on mask bits
                if ((combinedMask & 2) != 0) {
                    // bit1 set: accept only if childLowBit != 0
                    if (childLowBit != 0) break;
                } else if ((combinedMask & 4) != 0) {
                    // bit2 set: accept only if childLowBit == 0
                    if (childLowBit == 0) break;
                }
                // If neither bit, skip child and move to next
                child = reinterpret_cast<TreeChild*>(reinterpret_cast<uint>(child->next));
                currentChild = child;
            }

            if (currentChild != node) {
                // Found a matching child that is not the sentinel (node)
                if ((node->flags & 0xFFFFFFFE) != 0 && currentChild != node) {
                    break;
                }
            }

            // If child points back to node, no children found; skip to next sibling
            if ((currentNode->flags & 0xFFFFFFFE) == 0 || currentNode == currentChild) {
                // goto invalid case
                do {
                    currentNode = reinterpret_cast<TreeNode*>(currentNode->sibling);
                    nodeAddr = reinterpret_cast<uint>(currentNode);
                    if (nodeAddr == endAddr) break;
                } while ((currentNode->flags & 0xFFFFFFFE) == 0);
                currentChild = nullptr;
            }
        }
        // Update nodeAddr for loop
        nodeAddr = reinterpret_cast<uint>(currentNode);
    }

    if (currentNode == endNodeAddr) {
        return nullptr;
    }

    // Populate output fields from current child
    Output* out = reinterpret_cast<Output*>(this + 3); // offset 0x0C
    out->dataPtr = *reinterpret_cast<uint**>(currentNode->firstChild); // dereference firstChild's data? Actually assembly: **(uint**)(param_1[1] + 0x10) i.e., **(uint**)(currentNode + 0x10). So it treats currentNode->firstChild as a pointer to a pointer to uint.
    out->child = currentChild;
    out->childFlagsCleared = currentChild->flags & 0xFFFFFFFE;
    out->childField2 = currentChild->field2;
    out->childSize = (out->childFlagsCleared - currentChild->field2) + currentChild->field0;
    out->direction = ( ( (*(reinterpret_cast<byte*>(&currentChild->flags)) & 1) == 0 ) ? 4 : 2 );
    // The direction assignment: (low byte bit0 == 0) ? 4 : 2
    // Actually decompiled: if (lowbit == 0) then direction = 4 else 2. So direction = 2 + 2*(lowbit == 0)
    return out;
}
// Note: The exact semantics of mask bits and traversal order are reverse-engineered from the assembly.
// The child comparison (child != node) is unusual; it uses the node pointer as a sentinel for the end of the child list.
// The code has been cleaned up for readability but preserves the original logic.