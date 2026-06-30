// FUNC_NAME: NodePool::getFreeNodeData
// Function at 0x0043ab10: Returns a pointer to the data area of the next free node.
// Uses either a linked list traversal (bit0 clear) or a direct offset (bit0 set).
// If bit0 is set and index is 0, returns a global static buffer.

// Global static storage for fallback (initialized once)
static int g_guardFlag = 0;  // corresponds to _DAT_01223d10
static int g_staticBuffer[4] = {0,0,0,0};  // DAT_01223d00..0c

int* __thiscall NodePool::getFreeNodeData(void)
{
    unsigned char flags = *(unsigned char*)(this + 0x1C);
    int* pNode;
    int tag;

    if ((flags & 1) == 0)
    {
        // Mode 0: Walk the linked list until the sentinel 0x40000000
        pNode = (int*)(this + 0x20);           // head of list
        tag = *(int*)(this + 0x24);           // first tag
        while (tag != 0x40000000)
        {
            pNode = (int*)((int)pNode + *pNode); // jump by self-relative offset
            tag = pNode[1];                    // next tag
        }
        // Return pointer to data area after the two header ints
        return pNode + 2;
    }
    else
    {
        // Mode 1: Direct offset or static fallback
        int index = *(int*)(this + 0x24);
        if (index == 0)
        {
            // Use static buffer, initialize once
            if ((g_guardFlag & 1) == 0)
            {
                g_guardFlag |= 1;
                g_staticBuffer[0] = 0;
                g_staticBuffer[1] = 0;
                g_staticBuffer[2] = 0;
                g_staticBuffer[3] = 0;
            }
            return g_staticBuffer;
        }
        else
        {
            // Compute address from stored offset: base + index + 0x24
            return (int*)(index + 0x24 + (int)this);
        }
    }
}