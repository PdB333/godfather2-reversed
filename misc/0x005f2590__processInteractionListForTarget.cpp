// FUNC_NAME: processInteractionListForTarget
void processInteractionListForTarget(int targetId)
{
    int* pNode = (int*)DAT_011a0ef0; // Global head of linked list

    // Iterate through all nodes in the list
    while (pNode != nullptr)
    {
        // Check if this node matches the target (offset +0x60) and state (offset +0x68) is 2 or 4
        if ((pNode[0x60 / 4] == targetId) && 
            ((pNode[0x68 / 4] == 4) || (pNode[0x68 / 4] == 2)))
        {
            // Call debug/audio cue function with data from offsets +0x100 (byte), +0x5c (dword), +0x65 (byte)
            FUN_005dbc10(*(byte*)((int)pNode + 0x100), *(int*)((int)pNode + 0x5c), *(byte*)((int)pNode + 0x65));

            // Set some state to active (1) – possibly marking as processed
            FUN_005f3640(pNode, 1);

            // Copy a value from +0x88 to +0x8c (likely a timer or progress)
            *(int*)((int)pNode + 0x8c) = *(int*)((int)pNode + 0x88);

            // Reset a byte at +0x67 to 0xFF (e.g., timeout flag)
            *(byte*)((int)pNode + 0x67) = 0xFF;

            // Call debug/audio cue again after modifications
            FUN_005dbc10(*(byte*)((int)pNode + 0x100), *(int*)((int)pNode + 0x5c), *(byte*)((int)pNode + 0x65));
        }

        // Move to next node (+0x04)
        pNode = (int*)*(pNode + 1); // pNode[1] is offset +4
    }
}