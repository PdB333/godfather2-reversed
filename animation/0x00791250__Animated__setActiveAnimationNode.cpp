// FUNC_NAME: Animated::setActiveAnimationNode
// Address: 0x00791250
// Sets the active animation node from a source object (embedded at +0x48 in the source),
// then plays an animation with a given priority on the internal animation state machine.

void __thiscall Animated::setActiveAnimationNode(SomeObject* pSource, int priority)
{
    // +0xa4: pointer to current active animation node (head of list)
    AnimNode** ppActiveNode = reinterpret_cast<AnimNode**>(this + 0xa4);

    // Animation node is at offset 0x48 within the source object
    AnimNode* pNewNode = (pSource != nullptr) ?
        reinterpret_cast<AnimNode*>(reinterpret_cast<char*>(pSource) + 0x48) : nullptr;

    if (*ppActiveNode != pNewNode)
    {
        if (*ppActiveNode != nullptr)
        {
            // Detach old node from the list (FUN_004daf90)
            detachAnimationNode(ppActiveNode);
        }
        *ppActiveNode = pNewNode;

        if (pNewNode != nullptr)
        {
            // +0xa8: store the previous link of the new node
            *reinterpret_cast<AnimNode**>(this + 0xa8) = pNewNode->prev;
            // Set node's prev to point back to the list head pointer
            pNewNode->prev = reinterpret_cast<AnimNode*>(ppActiveNode);
        }
    }

    // Set flag bit 17 (0x20000) to indicate an active node is present
    *reinterpret_cast<uint32_t*>(this + 0x5c) |= 0x20000;

    // Stop any current animation (FUN_008eadd0) on state machine at +0x7c
    stopAllAnimations(reinterpret_cast<void*>(this + 0x7c));

    // If bit 19 (0x80000) is set, ensure minimum priority of 3
    if ((priority < 3) && ((*reinterpret_cast<uint32_t*>(this + 0x5c) >> 19) & 1))
    {
        priority = 3;
    }

    // Play animation with given priority (FUN_008f0bb0)
    playAnimation(reinterpret_cast<void*>(this + 0x7c), priority, this, 0);
}