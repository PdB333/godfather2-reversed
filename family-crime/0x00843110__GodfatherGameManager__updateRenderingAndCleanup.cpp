// FUNC_NAME: GodfatherGameManager::updateRenderingAndCleanup
void __fastcall GodfatherGameManager::updateRenderingAndCleanup(int thisPtr)
{
    int *pNode;
    undefined4 *pListHead;
    
    // Check if rendering is enabled (bit 6 of flags at +0x4c)
    if ((*(uint *)(thisPtr + 0x4c) >> 6 & 1) != 0) {
        // Disable rendering
        FUN_00440c30();
        // Clear the rendering enabled flag
        *(uint *)(thisPtr + 0x4c) = *(uint *)(thisPtr + 0x4c) & 0xffffffbf;
    }
    
    // Get the list of objects to clean up (type 9)
    pListHead = (undefined4 *)FUN_0043c2c0(9);
    
    // Iterate through the linked list and call cleanup on each object
    for (pNode = (int *)*pListHead; pNode != (int *)0x0; pNode = (int *)pNode[1]) {
        // Call cleanup on object at offset +0x3c
        FUN_004088c0(*pNode + 0x3c);
    }
    
    return;
}