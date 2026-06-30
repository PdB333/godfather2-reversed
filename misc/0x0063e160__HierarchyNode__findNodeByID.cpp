// FUNC_NAME: HierarchyNode::findNodeByID
void HierarchyNode::findNodeByID(int id, int* outResult, int flags)
{
    // outResult layout: [0]=status, [1]=index, [2]=?, [3]=?, [4]=?
    if (this == nullptr)
    {
        outResult[3] = -1;
        outResult[4] = -1;
        outResult[0] = 7;          // Not found
        outResult[1] = 0xFF;       // Sentinel index
        return;
    }

    // m_childCount at offset 0x34 (int* [0xd])
    int childCount = this->m_childCount; // param_1[0xd]
    int idx = childCount - 1;
    if (idx >= 0)
    {
        // m_childIndices array at offset 0x2b4 (int* +0xad)
        int* pIndex = &this->m_childIndices[childCount]; // point one past end
        do
        {
            // Access global table at (*(this->m_pSomeBase + 0x18))
            // Each entry is 12 bytes, first field is an ID
            int* tableBase = *(int**)(this->m_pSomeBase + 0x18);
            if (id == *(int*)(tableBase + (*pIndex) * 3)) // 3 ints per entry
            {
                // Found at this level
                if (idx >= 0) // always true here
                {
                    outResult[3] = -1;
                    outResult[4] = -1;
                    outResult[0] = 5;          // Found directly
                    outResult[1] = idx;        // Index in local array
                    if (flags != 0)
                        return;
                    // Call post-process for local found
                    FUN_0063e140(); // processFoundAtThisLevel
                    return;
                }
                break;
            }
            idx--;
            pIndex--;
        } while (idx >= 0);
    }

    // Not found in current node's children, recurse into child subtree
    // m_pChild at offset 0x8 (int* [2])
    this->m_pChild->findNodeByID(id, outResult, 0);

    if (outResult[0] == 7) // Still not found after recursion
    {
        if (flags != 0)
        {
            int newIndex = FUN_00642a50(); // some allocation/index generation
            outResult[1] = newIndex;
            return;
        }
    }
    else
    {
        // Found in subtree, call helper to update status and index
        int resultFromHelper = FUN_0063e000(this, id, outResult);
        outResult[0] = 6;
        outResult[1] = resultFromHelper;
    }
}