// FUNC_NAME: resolveManagedObject
void resolveManagedObject(void)
{
    // Get pointer to some internal object (likely a member pointer within a larger structure)
    int* pMember = (int*)FUN_004a8f00();  // Potentially GetActivePlayer or GetManagerInstance

    // Compute the enclosing object by subtracting the member offset (0x58)
    int* pOwner;
    if (pMember == (int*)0) {
        pOwner = (int*)0;
    }
    else {
        // The pointer points to a member at offset +0x58 from the base
        pOwner = (int*)((uint)pMember - 0x58);
    }

    // Call the actual handler with the owner pointer and a global parameter
    FUN_00796ba0(pOwner, *(int*)0x00d5ccf8);  // DAT_00d5ccf8 is a global offset/pointer

    return;
}