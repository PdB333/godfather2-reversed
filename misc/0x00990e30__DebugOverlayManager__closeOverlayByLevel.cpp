// FUNC_NAME: DebugOverlayManager::closeOverlayByLevel
uint DebugOverlayManager::closeOverlayByLevel(uint levelId)
{
    // Offset +0x60 points to head of a linked list of overlay nodes.
    // Each node: +0x4 = next pointer, +0x40 = unique index, +0x44 = level ID (short)
    OverlayNode* node = *(OverlayNode**)((uint)this + 0x60);
    if (node != nullptr)
    {
        while (node->levelId != (short)levelId)
        {
            if (levelId < (uint)node->levelId)
            {
                return 2;
            }
            node = node->next;
            if (node == nullptr)
            {
                return 2;
            }
        }
        // Build command strings: "_level%u" and "%u"
        char levelStr[32];
        char indexStr[32];
        sprintf(levelStr, "_level%u", levelId);
        sprintf(indexStr, "%u", node->index); // +0x40
        // Execute command to close the overlay: "Close _level<levelId> 1 <index>"
        // The function at 0x005a04a0 is likely a script command dispatcher.
        FUN_005a04a0("Close", 0, levelStr, 1, indexStr);
    }
    return 2;
}