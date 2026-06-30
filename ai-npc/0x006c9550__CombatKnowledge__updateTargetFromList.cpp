// FUNC_NAME: CombatKnowledge::updateTargetFromList
void __thiscall CombatKnowledge::updateTargetFromList(int this, int threatManager)
{
    int lastNode;
    int iterNode;
    int targetID[2];
    
    // Get the head of the linked list at threatManager+0x24
    lastNode = *(int *)(threatManager + 0x24);
    // Traverse the list using next pointer at offset 0xC to find the last node
    for (iterNode = *(int *)(*(int *)(threatManager + 0x24) + 0xC);
         iterNode != 0;
         iterNode = *(int *)(iterNode + 0xC))
    {
        lastNode = iterNode;
    }
    
    targetID[0] = 0;
    // Check if the last node has a non-zero byte at offset 0x10 (likely a flag)
    // Then call a function that resolves an ID (e.g., getTargetTypeID)
    if ( (*(char *)(lastNode + 0x10) + lastNode != 0) && FUN_004af8c0(targetID, 0x2001) && targetID[0] != 0 )
    {
        // targetID[0] now holds the resolved ID
    }
    
    // Compare the resolved ID with three stored IDs at this+0x30, 0x34, 0x38
    // If the ID doesn't match any of them (or the stored IDs are zero), clear the threat list
    if ( ((*(int *)(this + 0x30) == 0) || (targetID[0] != *(int *)(this + 0x30))) &&
         ((*(int *)(this + 0x34) == 0) || (targetID[0] != *(int *)(this + 0x34))) &&
         ((*(int *)(this + 0x38) == 0) || (targetID[0] != *(int *)(this + 0x38))) )
    {
        FUN_00a64940(threatManager);
    }
    return;
}