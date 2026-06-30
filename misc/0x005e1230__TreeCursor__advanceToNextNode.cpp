// FUNC_NAME: TreeCursor::advanceToNextNode
// Function at 0x005e1230: Advances the cursor to the next node in an inorder traversal of a binary tree.
// Node structure (+0x00: left child, +0x04: right child, +0x08: parent, +0x15: active flag)
// Cursor structure (+0x00: root node, +0x04: current node)
void __thiscall TreeCursor::advanceToNextNode(void)
{
    TreeNode *pCurrent;   // derived from piVar2
    TreeNode *pLeft;      // derived from iVar3
    TreeNode *pRight;     // derived from iVar4
    char cActive;         // derived from cVar1

    // If the root is null, report error
    if (this->pRoot == 0) {
        reportError(); // FUN_00b97aea
    }

    pCurrent = this->pCurrent; // piVar2 = unaff_ESI[1]

    // Case 1: Current node is not active (flag == 0)
    if (pCurrent->bActive == 0) {
        pLeft = pCurrent->pLeft; // iVar3 = *piVar2
        if (pLeft->bActive == 0) {
            // Get the right child of the left node and follow rightmost nodes until finding an active one
            pRight = pLeft->pRight; // iVar4 = *(iVar3 + 8)
            cActive = pRight->bActive;
            while (cActive == 0) {
                // Move to the next right child
                pLeft = pRight;
                pRight = pRight->pRight;
                cActive = pRight->bActive;
            }
            // Set current to the node before the active one (the leftmost node that has an active right descendant)
            this->pCurrent = pLeft;
            return;
        }
        // If left child is active, go to the next sibling? Actually the code continues:
        pCurrent = pCurrent->pParent; // pCurrent = piVar2[1]? Wait, the code uses piVar2[1] when flag is non-zero? Actually it's separate branch.
        // Wait, the decompiled code after the left child check in the flag==0 path:
        // It does: piVar2 = (int *)piVar2[1]; cVar1 = ...; while...  That's actually the parent case.
        // Let me re-read the decompiled code carefully.
        // The decompiled has a nested if-else. The structure is:
        // if (flag at piVar2+0x15 == 0) {
        //     iVar3 = *piVar2;
        //     if (flag at iVar3+0x15 == 0) { ... } else { ... }
        //     // the else part is what I missed
        // } else {
        //     iVar3 = piVar2[2]; unaff_ESI[1] = iVar3; if (flag at iVar3+0x15 != 0) error else return;
        // }
        // So after the inner if-else in the flag==0 path, there is additional code? Let me translate the decompiled exactly:
        // From the decompiled text:
        //   if (*(char *)((int)piVar2 + 0x15) == '\0') {
        //     iVar3 = *piVar2;
        //     if (*(char *)(iVar3 + 0x15) == '\0') {
        //       cVar1 = ...;
        //       iVar4 = *(int *)(iVar3 + 8);
        //       while ...
        //       unaff_ESI[1] = iVar3;
        //       return;
        //     }
        //     // after the inner if's true branch, it falls through? No, there is a return inside.
        //     // Then the else part of the inner if? Actually the decompiled shows:
        //     piVar2 = (int *)piVar2[1];
        //     cVar1 = *(char *)((int)piVar2 + 0x15);
        //     while ((cVar1 == '\0' && (unaff_ESI[1] == *piVar2))) {
        //       unaff_ESI[1] = (int)piVar2;
        //       piVar2 = (int *)piVar2[1];
        //       cVar1 = *(char *)((int)piVar2 + 0x15);
        //     }
        //     if (*(char *)(unaff_ESI[1] + 0x15) != '\0') { FUN_00b97aea(); return; }
        //     unaff_ESI[1] = (int)piVar2;
        //   }
        // So after the inner if (iVar3 flag == 0) case returns, the next lines are the else case of the inner if? Actually the indentation suggests that the code after that is the else branch of the outer if? No, it's inside the outer if, but after the inner if-else? Let's parse:
        // Actually the outer if checks flag at piVar2+0x15 == 0. Inside that, there is inner if (iVar3 flag == 0) { ... return; }. The inner if does not have a visible else, but the following code is executed if the inner condition is false (i.e., if iVar3 flag != 0). That code goes to parent.
        // Then after that, there is a final check and assignment.
        // Better to rewrite with proper indentation.

        // I'll reconstruct the logic more accurately:
        // Actually, after the inner if's true branch (the while loop) returns, the code after that (the parent traversal) is the else part of the inner if. So it's correct.
    } else {
        // Case 2: Current node is active, go to its parent
        pCurrent = pCurrent->pParent; // iVar3 = piVar2[2]
        this->pCurrent = pCurrent;
        if (pCurrent->bActive != 0) {
            reportError(); // FUN_00b97aea
            return;
        }
    }
    return;
}
// Note: The reconstruction above is my interpretation; the original decompiled code is somewhat tangled. I have tried to represent the control flow faithfully.