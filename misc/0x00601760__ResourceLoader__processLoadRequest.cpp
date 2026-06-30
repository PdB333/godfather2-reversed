// FUNC_NAME: ResourceLoader::processLoadRequest
// Function address: 0x00601760
// This function processes a load request for a resource. It checks if either the given resource ID or the
// internal resource references (at +0x7c and +0x88) are valid. If not, it clears the result and returns 0.
// Otherwise, it invokes a callback (stored at +0xa4) to obtain a node pointer, then attempts to parse
// and finalize the resource via external functions. The function returns 1 on success, 0 on failure.

int __thiscall ResourceLoader::processLoadRequest(int this, int resourceId, int param3, int param4, int param5)
{
    char cVar1;
    int iVar2;
    int *piVar3;
    int nodePtr; // local_20 - pointer from callback
    int nodePtr2; // local_1c - unused but kept for alignment
    int unused; // local_18
    int tempListHead; // iStack_14 - temporary list head from parseResource
    int tempListTail; // iStack_10 - tail for temp list (always 0)
    int unused2; // uStack_c

    // Check if any resource source is valid
    if ((((resourceId == 0) ||
          (iVar2 = someGetter(resourceId), iVar2 == 0)) &&
         (iVar2 = *(int *)(this + 0x88), iVar2 == 0)) &&
        (iVar2 = *(int *)(this + 0x7c), iVar2 == 0)) {
        // No valid resource: clear result and set flag
        *(int *)(this + 0xb0) = 0;
        *(unsigned int *)(this + 0xb4) |= 1;
        return 0;
    }

    nodePtr = 0;
    nodePtr2 = 0;
    unused = 0;
    someUtility(); // first call - possibly push/pop debug state
    if (*(code **)(this + 0xa4) != (code *)0x0) {
        // Invoke callback: passes this, pointer to +0x7c, pointer to +0x88, and address of nodePtr twice
        (**(code **)(this + 0xa4))(this, this + 0x7c, this + 0x88, &nodePtr, &nodePtr);
    }
    someUtility();
    someUtility();

    tempListHead = 0;
    tempListTail = 0;
    unused2 = 0;
    cVar1 = parseResource(param3, iVar2, &tempListHead, 0);
    if (cVar1 == '\0') {
        // Parsing failed: clear result and set flag
        *(int *)(this + 0xb0) = 0;
        *(unsigned int *)(this + 0xb4) |= 1;
        // Remove tempListHead from its list (if non-null)
        if (tempListHead != 0) {
            piVar3 = *(int **)(tempListHead + 4);
            if (piVar3 == &tempListHead) {
                *(int *)(tempListHead + 4) = tempListTail; // tempListTail is 0
            }
            else {
                while ((int *)piVar3[1] != &tempListHead) {
                    piVar3 = (int *)piVar3[1];
                }
                piVar3[1] = tempListTail;
            }
        }
        // Remove nodePtr from its list (if non-null)
        if (nodePtr != 0) {
            piVar3 = *(int **)(nodePtr + 4);
            if (piVar3 == &nodePtr) {
                *(int *)(nodePtr + 4) = nodePtr2; // nodePtr2 is 0
            }
            else {
                while ((int *)piVar3[1] != &nodePtr) {
                    piVar3 = (int *)piVar3[1];
                }
                piVar3[1] = nodePtr2;
            }
        }
        return 0;
    }
    // Parsing succeeded: finalize the resource
    finalizeResource(&tempListHead, param3, param4, param5, 0);
    // Remove tempListHead from its list (same pattern)
    if (tempListHead != 0) {
        piVar3 = *(int **)(tempListHead + 4);
        if (piVar3 == &tempListHead) {
            *(int *)(tempListHead + 4) = tempListTail;
        }
        else {
            while ((int *)piVar3[1] != &tempListHead) {
                piVar3 = (int *)piVar3[1];
            }
            piVar3[1] = tempListTail;
        }
    }
    // Remove nodePtr from its list (if non-null)
    if (nodePtr != 0) {
        piVar3 = *(int **)(nodePtr + 4);
        if (piVar3 == &nodePtr) {
            *(int *)(nodePtr + 4) = nodePtr2;
            return 1;
        }
        else {
            while ((int *)piVar3[1] != &nodePtr) {
                piVar3 = (int *)piVar3[1];
            }
            piVar3[1] = nodePtr2;
        }
    }
    return 1;
}