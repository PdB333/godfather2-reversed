// FUNC_NAME: RedBlackTree::insertNode
void __fastcall RedBlackTree::insertNode(int param_1, int *param_2, int *param_3)
{
    int *piVar1;
    int iVar2;
    int *piVar3;
    int iVar4;
    int iVar5;
    
    iVar4 = *param_2;
    piVar1 = *(int **)(iVar4 + 0xc);  // +0x0C: right child pointer
    iVar2 = *(int *)(iVar4 + 4);      // +0x04: parent pointer
    *(int *)(iVar4 + 0xc) = piVar1[2]; // +0x08: left child pointer
    if (piVar1[2] != 0) {
        *(int *)(piVar1[2] + 4) = *param_2;
    }
    piVar1[2] = *param_2;
    *(int **)(*param_2 + 4) = piVar1;
    piVar3 = (int *)*param_2;
    if ((int *)piVar3[3] == (int *)0x0) {  // +0x0C: right child
        iVar4 = -1;
    }
    else {
        iVar4 = *(int *)piVar3[3];
    }
    if ((int *)piVar3[2] == (int *)0x0) {  // +0x08: left child
        iVar5 = -1;
    }
    else {
        iVar5 = *(int *)piVar3[2];
    }
    if (iVar4 <= iVar5) {
        iVar4 = iVar5;
    }
    *piVar3 = iVar4 + 1;  // +0x00: node value/key
    if ((int *)*param_2 == (int *)0x0) {
        iVar4 = -1;
    }
    else {
        iVar4 = *(int *)*param_2;
    }
    if ((int *)piVar1[3] == (int *)0x0) {  // +0x0C: right child
        iVar5 = -1;
    }
    else {
        iVar5 = *(int *)piVar1[3];
    }
    if (iVar4 <= iVar5) {
        iVar4 = iVar5;
    }
    *piVar1 = iVar4 + 1;  // +0x00: node value/key
    piVar1[1] = iVar2;    // +0x04: parent pointer
    if (iVar2 != 0) {
        if (*(int *)(iVar2 + 8) == *param_2) {  // +0x08: left child
            *(int **)(iVar2 + 8) = piVar1;
            *param_2 = (int)piVar1;
            return;
        }
        *(int **)(iVar2 + 0xc) = piVar1;  // +0x0C: right child
        *param_2 = (int)piVar1;
        return;
    }
    *param_3 = (int)piVar1;
    *param_2 = (int)piVar1;
    return;
}