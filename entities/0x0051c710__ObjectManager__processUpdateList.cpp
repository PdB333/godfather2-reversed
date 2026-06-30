// FUNC_NAME: ObjectManager::processUpdateList
void __cdecl ObjectManager::processUpdateList(uint context, char forceUpdate)
{
    int* piVar4;
    int* piVar3;
    int* piVar2;
    int iVar1;

    // Likely pre-update lock or begin frame
    someBeginFunction(); // FUN_0051bb80

    // Store the forceUpdate flag globally
    gForceUpdateFlag = forceUpdate; // DAT_0120551d

    // Traverse linked list starting from global head
    iVar1 = gNodeListHead; // DAT_01205514
    while (iVar1 != 0) {
        // piVar4 points to the previous node's 'next' field (or head)
        piVar4 = &gNodeListHead; // initially, then updated inside loop

        // Check flag: if node has flag 0x200000 set -> remove from list and deallocate
        if ((*(uint*)(iVar1 + 0xc) & 0x200000) == 0) {
            // Node is not marked for removal; update piVar4 to current node's next pointer
            piVar4 = (int*)(iVar1 + 0x14);
            // Process node if either forceUpdate is false, or node has flag 0x400000 (always process)
            if ((forceUpdate == '\0') || ((*(uint*)(iVar1 + 0xc) & 0x400000) != 0)) {
                processSingleNode(iVar1, context); // FUN_0051abd0
            }
        } else {
            // Node marked for removal: unlink it from the list
            *piVar4 = *(int*)(iVar1 + 0x14); // update previous next pointer
            // Call deallocation helper
            deallocateNode(); // FUN_0051a5e0

            // Move node to a memory pool (appears to be a custom allocator)
            piVar2 = (int*)(gMemoryPool + 0x14); // DAT_01206880 + 0x14
            **(undefined4**)(gMemoryPool + 0x14) = &PTR_LAB_01125180; // set pool base pointer?
            *piVar2 = *piVar2 + 4;
            piVar3 = (int*)(*piVar2 + 3U & 0xfffffffc); // align to 4 bytes
            *piVar2 = (int)piVar3;
            *piVar3 = iVar1; // store node into pool
            *piVar2 = *piVar2 + 4;
        }
        // Advance to next node
        iVar1 = *piVar4;
    }

    // Post-update or commit changes
    someEndFunction(context); // FUN_0052e780
}