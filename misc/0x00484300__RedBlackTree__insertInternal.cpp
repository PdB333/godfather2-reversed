// FUNC_NAME: RedBlackTree::insertInternal
void RedBlackTree::insertInternal(int *thisPtr, int **outNode, char insertLeft, int *parentNode, int *keyValue)
{
    char cVar1;
    int *piVar2;
    int *piVar3;
    int *piVar4;
    int *piVar5;
    int iVar6;
    int *piVar7;
    uint local_3c;
    uint local_28;
    
    // Check for size overflow (size > 0x1ffffffd)
    if (0x1ffffffd < *(uint *)(thisPtr + 8)) {
        // Throw "map/set<T> too long"
        throwException(&local_24, "map/set<T> too long", 0x13);
    }
    
    iVar6 = *(int *)(thisPtr + 4);  // header node
    piVar3 = (int *)allocateNode();  // FUN_00485090
    
    if (piVar3 != (int *)0x0) {
        *piVar3 = iVar6;                    // parent = header
        piVar3[1] = (int)parentNode;        // left = ? (hint)
        piVar3[2] = iVar6;                  // right = header
        piVar3[3] = *keyValue;              // key
        piVar3[4] = keyValue[1];            // value
        // Initialize color and sentinel flags
        *(char *)(piVar3 + 5) = 0;          // color = red
        *(char *)((int)piVar3 + 0x15) = 0;  // not sentinel
    }
    
    *(int *)(thisPtr + 8) = *(int *)(thisPtr + 8) + 1;  // increment size
    
    // Insert into tree relative to parentNode
    if (parentNode == *(int **)(thisPtr + 4)) {
        // Inserting at root
        *(int **)(thisPtr + 4) = piVar3;
        **(int **)(thisPtr + 4) = piVar3;
        *(int **)(*(int *)(thisPtr + 4) + 8) = piVar3;
    }
    else if (insertLeft == '\0') {
        // Insert as right child
        parentNode[2] = piVar3;
        if (parentNode == *(int **)(*(int *)(thisPtr + 4) + 8)) {
            *(int **)(*(int *)(thisPtr + 4) + 8) = piVar3;
        }
    }
    else {
        // Insert as left child
        *parentNode = piVar3;
        if (parentNode == *(int **)(thisPtr + 4)) {
            **(int **)(thisPtr + 4) = (int)piVar3;
        }
    }
    
    cVar1 = *(char *)(piVar3[1] + 0x14);  // check sentinel flag
    piVar7 = piVar3;
    
    // Red-black tree fixup loop
    do {
        if (cVar1 != '\0') {  // if parent is sentinel (root case)
            *(char *)(*(int *)(*(int *)(thisPtr + 4) + 4) + 0x14) = 1;  // set root color to black
            *outNode = &thisPtr;
            outNode[1] = piVar3;
            return;
        }
        
        piVar4 = piVar7 + 1;
        piVar5 = (int *)*piVar4;
        piVar2 = (int *)piVar5[1];
        
        if (piVar5 == (int *)*piVar2) {  // Case: parent is left child of grandparent
            iVar6 = piVar2[2];  // uncle (right child of grandparent)
            if (*(char *)(iVar6 + 0x14) != '\0') {  // uncle is black
                if (piVar7 == (int *)piVar5[2]) {  // Case: node is right child
                    rotateLeft(thisPtr);  // FUN_00484c10 (left rotation)
                    piVar7 = piVar5;
                }
                // Recolor and rotate
                *(char *)(*piVar4 + 0x14) = 1;
                *(char *)(*(int *)(*piVar4 + 4) + 0x14) = 0;
                piVar4 = *(int **)(*piVar4 + 4);
                piVar5 = (int *)*piVar4;
                *piVar4 = piVar5[2];
                if (*(char *)(piVar5[2] + 0x15) == '\0') {
                    *(int **)(piVar5[2] + 4) = piVar4;
                }
                piVar5[1] = piVar4[1];
                if (piVar4 == *(int **)(*(int *)(thisPtr + 4) + 4)) {
                    *(int **)(*(int *)(thisPtr + 4) + 4) = piVar5;
                    piVar5[2] = (int)piVar4;
                }
                else {
                    piVar2 = (int *)piVar4[1];
                    if (piVar4 == (int *)piVar2[2]) {
                        piVar2[2] = (int)piVar5;
                        piVar5[2] = (int)piVar4;
                    }
                    else {
                        *piVar2 = (int)piVar5;
                        piVar5[2] = (int)piVar4;
                    }
                }
                goto LAB_RotationDone;
            }
LAB_RecolorCase:
            *(char *)(piVar5 + 5) = 1;
            *(char *)(iVar6 + 0x14) = 1;
            *(char *)(*(int *)(*piVar4 + 4) + 0x14) = 0;
            piVar7 = *(int **)(*piVar4 + 4);
        }
        else {  // Case: parent is right child of grandparent
            iVar6 = *piVar2;  // uncle (left child of grandparent)
            if (*(char *)(iVar6 + 0x14) == '\0') {  // uncle is red
                // Recolor and move up
                *(char *)(piVar5 + 5) = 1;
                *(char *)(iVar6 + 0x14) = 1;
                *(char *)(*(int *)(*piVar4 + 4) + 0x14) = 0;
                piVar7 = *(int **)(*piVar4 + 4);
                continue;
            }
            if (piVar7 == (int *)*piVar5) {  // Case: node is left child
                rotateRight(thisPtr);
                piVar7 = piVar5;
            }
            // Recolor and rotate
            *(char *)(piVar7[1] + 0x14) = 1;
            *(char *)(*(int *)(piVar7[1] + 4) + 0x14) = 0;
            piVar4 = *(int **)(piVar7[1] + 4);
            piVar5 = (int *)piVar4[2];
            piVar4[2] = *piVar5;
            if (*(char *)(*piVar5 + 0x15) == '\0') {
                *(int **)(*piVar5 + 4) = piVar4;
            }
            piVar5[1] = piVar4[1];
            if (piVar4 == *(int **)(*(int *)(thisPtr + 4) + 4)) {
                *(int **)(*(int *)(thisPtr + 4) + 4) = piVar5;
            }
            else {
                piVar2 = (int *)piVar4[1];
                if (piVar4 == (int *)*piVar2) {
                    *piVar2 = (int)piVar5;
                }
                else {
                    piVar2[2] = (int)piVar5;
                }
            }
            *piVar5 = (int)piVar4;
LAB_RotationDone:
            piVar4[1] = (int)piVar5;
        }
        cVar1 = *(char *)(piVar7[1] + 0x14);
    } while( true );
}