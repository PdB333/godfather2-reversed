// FUNC_NAME: LinkedList::reorderNode
// Address: 0x004ca5a0
// This function repositions a node in a linked list or tree-like structure.
// It appears to move a node relative to its predecessor or adjust links
// based on flags in an auxiliary structure.
//
// Structure layout (from offsets):
// param_1 (int*) - pointer to a node with:
//   +0: pPrevOrAnchor (points to another node or anchor)
//   +4: pNext (next node in list)
// param_2 (int) - container object with:
//   +0x1c: pointer to head pointer (head is at +4 of that pointer)
//
// The node's predecessor (iVar1) has:
//   +0: unknown
//   +4: pNext (will be overwritten)
//   +8: pAuxStruct (points to an auxiliary structure with:
//       +0x00: unknown
//       +0x04: pBackLink (set to param_1 if flag is zero)
//       ...
//       +0x15: flag (byte)

void __thiscall LinkedList::reorderNode(int* param_1, int param_2)
{
    int* iVar1;      // predecessor node
    int* piVar2;     // next node

    iVar1 = (int*)*param_1;                     // iVar1 = param_1->pPrevOrAnchor
    *param_1 = *(int*)(iVar1 + 8);               // param_1->pPrevOrAnchor = iVar1->pAuxStruct

    // Check flag in auxiliary structure pointed by iVar1->pAuxStruct
    if (*(char*)(*(int*)(iVar1 + 8) + 0x15) == '\0') {
        // Update back pointer in auxiliary structure
        *(int**)(*(int*)(iVar1 + 8) + 4) = param_1;
    }

    // Update predecessor's next pointer
    *(int*)(iVar1 + 4) = param_1[1];            // iVar1->pNext = param_1->pNext

    // Check if param_1 is the head of the list
    if (param_1 == *(int**)(*(int*)(param_2 + 0x1c) + 4)) {
        // Update head to predecessor
        *(int*)(*(int*)(param_2 + 0x1c) + 4) = (int)iVar1;
        // Link predecessor and param_1
        *(int**)(iVar1 + 8) = param_1;          // iVar1->pAuxStruct = param_1
        param_1[1] = (int)iVar1;                // param_1->pNext = iVar1
        return;
    }

    piVar2 = (int*)param_1[1];                  // piVar2 = param_1->pNext
    if (param_1 == (int*)piVar2[2]) {           // if param_1 equals piVar2->someFieldAt+2
        piVar2[2] = (int)iVar1;                 // piVar2->someFieldAt+2 = iVar1
        *(int**)(iVar1 + 8) = param_1;
        param_1[1] = (int)iVar1;
        return;
    }

    // Default case: update next node's first field
    *piVar2 = (int)iVar1;                       // piVar2->pPrevOrAnchor = iVar1
    *(int**)(iVar1 + 8) = param_1;
    param_1[1] = (int)iVar1;
    return;
}