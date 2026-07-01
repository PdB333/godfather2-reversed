// FUNC_NAME: ListManager::destroyAllNodes

void __thiscall ListManager::destroyAllNodes(int this)
{
    int* piVar1;
    int iVar2;
    int* piVar3;

    // Set abort flag to 0 (continue loop)
    *(int*)(this + 0x44) = 0;
    // Set active flag to 1 (destroying)
    *(char*)(this + 0x48) = 1;

    do {
        // If head is null, exit loop
        if (*(int*)(this + 0x4c) == 0) break;

        // Get current head node
        piVar1 = *(int**)(this + 0x4c);
        piVar3 = (int*)0x0;

        if (piVar1 != (int*)0x0) {
            // Advance head to next node
            iVar2 = *piVar1;  // piVar1[0] is next pointer
            *(int*)(this + 0x4c) = iVar2;

            piVar3 = piVar1;

            if (iVar2 == 0) {
                // If next is null, set tail to null
                *(int*)(this + 0x50) = 0;
            } else {
                // Else, set next node's prev to null
                *(int*)(iVar2 + 4) = 0;
                // Detach current node from list
                *piVar1 = 0;
            }
        }

        // Release the node (decrement refcount or similar)
        FUN_008f0c00(piVar3);

        if (piVar3 != (int*)0x0) {
            // If the node has an embedded object at offset 0x20, destroy it
            if (piVar3[8] != 0) {
                FUN_004daf90(piVar3 + 8); // +0x20 embedded object destructor
            }
            // Free the node memory
            FUN_009c8eb0(piVar3); // operator delete
        }
    } while (*(int*)(this + 0x44) == 0); // Continue while abort flag is 0

    // Clear active flag
    *(char*)(this + 0x48) = 0;
}