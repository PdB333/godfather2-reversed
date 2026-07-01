// FUNC_NAME: NodeList::removeCurrentNode
void __fastcall NodeList::removeCurrentNode(void *this)
{
    int listPtr;
    int nodeToRemove;
    undefined4 *nextNode;
    int tempNext;
    undefined4 dummy;

    FUN_008ec8c0(&listPtr, &dummy);
    int originalNext = *(int *)((int)this + 0x10);
    if ((listPtr == 0) || (listPtr != (int)this + 0xc)) {
        FUN_00b97aea(); // assert: list pointer invalid
    }
    if (nodeToRemove != originalNext) {
        if (listPtr == 0) {
            FUN_00b97aea(); // assert: list is null
        }
        if (nodeToRemove == *(int *)(listPtr + 4)) {
            FUN_00b97aea(); // assert: node is list head
        }
        nextNode = *(undefined4 **)(nodeToRemove + 0x10); // next pointer at +0x10
        tempNext = 0;
        *(undefined4 **)(nodeToRemove + 0x20) = nextNode; // store next as temp
        if (nextNode != (undefined4 *)0x0) {
            tempNext = nextNode[2]; // offset 8: maybe some node flag or function pointer
            *(undefined4 *)(nodeToRemove + 0x20) = *nextNode; // copy first field of next
        }
        if (tempNext == 0) {
            *(int *)(nodeToRemove + 0x18) = 4; // state to terminate
            if (nodeToRemove == *(int *)(listPtr + 4)) {
                FUN_00b97aea(); // assert: node is head (already checked)
            }
            undefined4 uVar3 = FUN_004059b0(*(undefined4 *)(nodeToRemove + 0xc));
            int iVar2 = FUN_004025a0(uVar3);
            if (iVar2 != 0) {
                FUN_00404c40(iVar2);
                return;
            }
        }
        else {
            do {
                FUN_004088c0(tempNext + 0x3c); // callback on each next node
                nextNode = *(undefined4 **)(nodeToRemove + 0x20);
                tempNext = 0;
                if (nextNode != (undefined4 *)0x0) {
                    tempNext = nextNode[2];
                    *(undefined4 *)(nodeToRemove + 0x20) = *nextNode;
                }
            } while (tempNext != 0);
            *(int *)(nodeToRemove + 0x18) = 3; // state to continue
        }
    }
}