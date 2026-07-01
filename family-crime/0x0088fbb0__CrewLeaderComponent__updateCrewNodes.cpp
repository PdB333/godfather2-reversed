// FUNC_NAME: CrewLeaderComponent::updateCrewNodes
void __thiscall CrewLeaderComponent::updateCrewNodes(uint updateFlags)
{
    bool bAllNodesAreMax;
    uint nodeState;
    uint minPriority;
    uint tempMask;
    uint maskA;
    uint maskB;
    CrewNode *maxPriorityNode;
    CrewNode *currNode;
    CrewNode *minPriorityNode;

    if (*(int *)(this + 0x1c0) == 0) // +0x1c0: m_bUpdateEnabled
    {
        minPriorityNode = 0;
        maxPriorityNode = 0;
        currNode = this;
        do
        {
            nodeState = *(uint *)(currNode + 0x1a8); // +0x1a8: m_stateFlags
            if ((updateFlags & nodeState) == 0)
            {
                // Node not matching update flags – set to idle state
                tempMask = (gStateMaskHigh | gStateMaskMid | gStateMaskLow) & *(uint *)(currNode + 0x1d4); // +0x1d4: m_blendMask
                setNodeState(0, tempMask);
            }
            else
            {
                if ((nodeState & 7) == 0) // lower 3 bits indicate priority presence
                {
                    tempMask = 0;
                    nodeState = (gStateMaskHigh | gStateMaskMid | gStateMaskLow) & *(uint *)(currNode + 0x1d4);
                    setNodeState(nodeState, tempMask);
                }
                else
                {
                    // Find min and max priority nodes
                    if (minPriorityNode == 0 || nodeState < *(uint *)(minPriorityNode + 0x1a8))
                    {
                        minPriorityNode = currNode;
                    }
                    if (maxPriorityNode == 0 || *(uint *)(maxPriorityNode + 0x1a8) < nodeState)
                    {
                        maxPriorityNode = currNode;
                    }
                }
            }
            currNode = *(CrewNode **)(currNode + 0x1c4); // +0x1c4: m_nextNode
        } while (currNode != 0);

        if (minPriorityNode == 0)
        {
            minPriority = 0;
        }
        else
        {
            minPriority = *(uint *)(minPriorityNode + 0x1a8);
        }

        bAllNodesAreMax = true;
        currNode = this;
        do
        {
            nodeState = *(uint *)(currNode + 0x1a8);
            if (currNode != minPriorityNode && (nodeState & 7) != 0)
            {
                bAllNodesAreMax = bAllNodesAreMax && (currNode == maxPriorityNode);
                if (currNode == maxPriorityNode)
                {
                    maskA = gStateMaskHigh;
                    maskB = gStateMaskMid;
                }
                else
                {
                    maskA = gStateMaskMid;
                    maskB = gStateMaskHigh;
                }
                setNodeState(*(uint *)(currNode + 0x1d4) & maskA,
                             *(uint *)(currNode + 0x1d4) & (gStateMaskLow | maskB));
            }
            if ((nodeState & 0x37) != 0 && *(int **)(currNode + 0x130) != 0) // +0x130: m_vtable
            {
                // Call vtable method at offset 0x44 (e.g., onPriorityChange) with callback ID
                (**(code **)(**(int **)(currNode + 0x130) + 0x44))(0xd5f82c42, minPriority);
            }
            currNode = *(CrewNode **)(currNode + 0x1c4);
        } while (currNode != 0);

        if (minPriorityNode != 0)
        {
            maskA = gStateMaskLow;
            maskB = gStateMaskMid;
            if (bAllNodesAreMax)
            {
                maskA = gStateMaskLow | gStateMaskMid;
                maskB = 0;
            }
            if (minPriorityNode == maxPriorityNode)
            {
                maskA = maskA | gStateMaskHigh;
            }
            else
            {
                maskB = maskB | gStateMaskHigh;
            }
            setNodeState(*(uint *)(minPriorityNode + 0x1d4) & maskA,
                         *(uint *)(minPriorityNode + 0x1d4) & maskB);
        }
    }
}