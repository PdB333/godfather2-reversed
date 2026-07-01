// FUNC_NAME: TreeNode::buildMergeCache
// Function at 0x00877240: Builds a cached merged node from two child linked lists
// This appears to be a red-black tree or similar structure where left and right subtrees
// are merged into a single node for faster access. Checks if already cached.

void TreeNode::buildMergeCache()
{
    // Profile entry (likely debug/profiling)
    FUN_005403e0(0xcf);

    // Get pointer to merge slot from this+0x18 (offset 24)
    MergeSlot *slot = reinterpret_cast<MergeSlot*>(this->mergeSlotPtr);
    TreeNode *existingMerge = slot->mergeNode;

    if (existingMerge != nullptr)
    {
        // Already exists, increment generation counter if valid
        if (slot->validCount != 0)
        {
            slot->generationCount++;  // +0x06
        }
        FUN_00540410(); // Profile exit
        return;
    }

    // Allocate new merge node (size 0x18 = 24 bytes)
    TlsGetValue(DAT_01139810);  // TLS context (likely for thread-safe allocation)
    MergeNode *newNode = reinterpret_cast<MergeNode*>(FUN_00aa2680(sizeof(MergeNode), 0xb));

    // Initialize MergeNode header
    newNode->size = sizeof(MergeNode);          // +0x04: 0x18
    newNode->refCount = 1;                      // +0x06: 1
    newNode->vtable = &PTR_LAB_00d765d4;        // +0x00: vtable pointer

    // Traverse left child list to find rightmost node
    TreeNode *leftHead = this->leftChildList;   // +0x00
    TreeNode *leftTraverse = leftHead;
    while (leftTraverse->next != nullptr)       // +0x0c: next pointer
    {
        leftHead = leftTraverse;
        leftTraverse = leftTraverse->next;
    }
    newNode->rightmostLeft = leftHead;          // +0x08: store last node
    newNode->leftHeadData = *reinterpret_cast<int*>(this->leftChildList + 4); // +0x0c: data from head+4

    // Traverse right child list to find rightmost node
    TreeNode *rightHead = this->rightChildList; // +0x04
    TreeNode *rightTraverse = rightHead;
    while (rightTraverse->next != nullptr)
    {
        rightHead = rightTraverse;
        rightTraverse = rightTraverse->next;
    }
    newNode->rightmostRight = rightHead;        // +0x10
    newNode->rightHeadData = *reinterpret_cast<int*>(this->rightChildList + 4); // +0x14

    // Store newly created node in merge slot
    slot->mergeNode = newNode;                  // +0x08

    FUN_00540410(); // Profile exit
    return;
}