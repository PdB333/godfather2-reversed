// FUNC_NAME: PathGraph::findEdgeForTransition
uint __thiscall PathGraph::findEdgeForTransition(PathGraph *this, void *transitionData)
{
    uint count = *(uint *)((int)this + 0x0c); // +0x0c: number of nodes/edges
    if (count == 0)
    {
        return 0xffffffff;
    }
    if (count == 1)
    {
        return 0;
    }

    uint current = *(uint *)((int)this + 0x04); // +0x04: current index (cursor)
    uint next;
    if (current < count - 1) 
        next = current + 1;
    else
        next = 0;

    // Check the edge between current and next against the transition data
    uint *nodeArray = *(uint **)((int)this + 0x08); // +0x08: array of node pointers
    bool match = FUN_00821840(transitionData, nodeArray[current] + 4, nodeArray[next] + 4);
    if (match)
    {
        return current;
    }

    // Full scan from start
    for (uint i = 0; i < count; i++)
    {
        uint j;
        if (i < count - 1)
            j = i + 1;
        else
            j = 0;

        match = FUN_00821840(transitionData, nodeArray[i] + 4, nodeArray[j] + 4);
        if (match)
        {
            return i;
        }
    }
    return 0xffffffff;
}