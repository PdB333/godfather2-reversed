// FUNC_NAME: Sentient::checkActionEligibility
undefined4 __fastcall Sentient::checkActionEligibility(int this)
{
    int *pInteractableArray;
    int *pInteractableBase;
    int *pOwnerObject;
    
    pInteractableArray = *(int **)(this + 0x2178); // game object array or interaction list
    if (((pInteractableArray != (int *)0x0) && ((int *)((int)pInteractableArray - 0x48) != (int *)0x0)) && ((*(uint *)(pInteractableArray + 5) >> 0x13 & 1) != 0)) {
        // +0x14 = bit 19 check: likely "isActiveOrAvailable"
        pOwnerObject = (int *)getContainingObject((int)pInteractableArray - 0x48);
        if (*(char *)(pOwnerObject + 0x1a4) == '\0') {
            // +0x1a4 = Boolean flag (e.g., "isBusy" or "isInUse")
            return 1;
        }
    }
    return 0;
}