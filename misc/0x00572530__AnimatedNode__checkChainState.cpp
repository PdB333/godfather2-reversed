// FUNC_NAME: AnimatedNode::checkChainState
// Address: 0x00572530
// Follows a linked chain (offset +0x124) for chainLength steps from this’s first node,
// then checks if the target node has flags & 0x2000003 or its float at +0x24 <= global threshold.

extern float g_chainDistanceThreshold;

class AnimatedNode {
public:
    // +0x124: next node pointer (sibling / child)
    // +0x10:  flags (bits 0,1,25 used)
    // +0x24:  float (distance or parameter)
    bool __thiscall checkChainState(int chainLength);
};

bool __thiscall AnimatedNode::checkChainState(int chainLength)
{
    AnimatedNode* currentNode = nullptr;

    // Guard: null this or negative length -> false
    if (this == nullptr || chainLength < 0)
        return false;

    // Start traversal from the node pointed to by this->field_0x124
    currentNode = *(AnimatedNode**)((uint8*)this + 0x124);

    // Walk the chain chainLength times, stopping early on null
    for (int i = 0; i < chainLength; i++)
    {
        if (currentNode == nullptr)
            break;
        currentNode = *(AnimatedNode**)((uint8*)currentNode + 0x124);
    }

    // If we reached a valid node, evaluate the condition
    if (currentNode != nullptr)
    {
        uint32 flags = *(uint32*)((uint8*)currentNode + 0x10);
        float value  = *(float*)((uint8*)currentNode + 0x24);

        return (flags & 0x2000003) != 0 || value <= g_chainDistanceThreshold;
    }

    return false;
}