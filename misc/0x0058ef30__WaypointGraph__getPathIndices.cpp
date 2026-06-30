// FUNC_NAME: WaypointGraph::getPathIndices
bool WaypointGraph::getPathIndices(int* outIndices, int startIndex)
{
    // outIndices is expected to be an array of 4 ints
    // th is the "this" pointer (unaff_EDI)
    // m_graph at +0x70 points to a graph structure
    // m_currentNodeIndex at +0x74 is the current node (short)
    outIndices[0] = startIndex;

    int index1, index2, index3;

    // Step 1: compute index1 from startIndex using current node's adjacency
    if (m_currentNodeIndex < 0)
    {
        index1 = -1;
    }
    else
    {
        // m_currentNodeIndex is a valid index
        GraphHeader* graph = (GraphHeader*)m_graph; // +0x70
        int nodeCount = graph->nodeCount; // +0x18
        if (m_currentNodeIndex >= nodeCount || startIndex < 0)
        {
            index1 = -1;
        }
        else
        {
            NodeRecord* nodeRecord = (NodeRecord*)(graph->nodeRecords + m_currentNodeIndex * sizeof(NodeRecord)); // +0x1c base
            // nodeRecord->adjCount at +0x8, nodeRecord->adjTable at +0xc
            if (startIndex >= nodeRecord->adjCount)
            {
                index1 = -1;
            }
            else
            {
                int* adjEntry = (int*)(nodeRecord->adjTable + startIndex * kAdjEntrySize); // each entry is 0x10 bytes
                index1 = *adjEntry; // first 4 bytes of entry are neighbor index
            }
        }
    }
    outIndices[1] = index1;

    // Step 2: compute index2 from index1 using current node's adjacency
    if (m_currentNodeIndex < 0)
    {
        index2 = -1;
    }
    else
    {
        GraphHeader* graph = (GraphHeader*)m_graph;
        int nodeCount = graph->nodeCount;
        if (m_currentNodeIndex >= nodeCount || index1 < 0)
        {
            index2 = -1;
        }
        else
        {
            NodeRecord* nodeRecord = (NodeRecord*)(graph->nodeRecords + m_currentNodeIndex * sizeof(NodeRecord));
            if (index1 >= nodeRecord->adjCount)
            {
                index2 = -1;
            }
            else
            {
                int* adjEntry = (int*)(nodeRecord->adjTable + index1 * kAdjEntrySize);
                index2 = *adjEntry;
            }
        }
    }
    outIndices[2] = index2;

    // Step 3: compute index3 from index2
    if (m_currentNodeIndex < 0)
    {
        index3 = -1;
    }
    else
    {
        GraphHeader* graph = (GraphHeader*)m_graph;
        int nodeCount = graph->nodeCount;
        if (m_currentNodeIndex >= nodeCount || index2 < 0)
        {
            index3 = -1;
        }
        else
        {
            NodeRecord* nodeRecord = (NodeRecord*)(graph->nodeRecords + m_currentNodeIndex * sizeof(NodeRecord));
            if (index2 >= nodeRecord->adjCount)
            {
                index3 = -1;
            }
            else
            {
                int* adjEntry = (int*)(nodeRecord->adjTable + index2 * kAdjEntrySize);
                index3 = *adjEntry;
            }
        }
    }
    outIndices[3] = index3;

    // Validate that all four indices are non-negative, then perform additional checks
    if (startIndex >= 0 && index1 >= 0 && index2 >= 0 && index3 >= 0)
    {
        // FUN_0058dd70 likely checks some state; called four times in sequence
        // If any returns false, the overall function fails
        if (!isValidForTraversal()) return false;
        if (!isValidForTraversal()) return false;
        if (!isValidForTraversal()) return false;
        return isValidForTraversal();
    }
    return false;
}