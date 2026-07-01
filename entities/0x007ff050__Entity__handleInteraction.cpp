// FUNC_NAME: Entity::handleInteraction
// Function address: 0x007ff050
// Handles interaction with an object (use/activate). param_2: 1=simple use, 2=complex use with flag setting.
// Field offsets: +0x7a7 = pointer to current interactable object (or 0x48 sentinel for none)
//                +0x1c4 = interaction data (transform?)
//                +0x74  = flags (bit 0x400000 set on success)
//                +0x39e = flags (bit 0x80 set on success)

void __thiscall Entity::handleInteraction(int interactionType)
{
    int *pInteractableObjPtr; // piVar1
    bool canInteract;         // cVar2
    int *pBaseObj;            // piVar3
    int objPtr;               // iVar5
    int someObj;              // iVar6
    int someTransform;        // uVar4

    // Stack buffers for function calls
    char buffer1[12];   // auStack_50
    char buffer2[8];    // auStack_2c
    char buffer3[12];   // auStack_20
    int dummy1;         // uStack_44
    int dummy2;         // uStack_34
    int dummy3;         // uStack_24
    int globalVal;      // uStack_14, from _DAT_00d5780c

    pInteractableObjPtr = this + 0x7a7; // &(this->interactableObjPtr)

    // Early exit if no valid interactable object
    if (*pInteractableObjPtr == 0 || *pInteractableObjPtr == 0x48)
        return;

    // Pre-interaction setup
    FUN_00707a40(); // likely some global pre-action

    // Get base object pointer (vtable offset -0x48)
    if (*pInteractableObjPtr == 0)
        pBaseObj = nullptr;
    else
        pBaseObj = (int *)(*pInteractableObjPtr - 0x48);

    // Call vtable function at offset 0x7c (e.g., onInteractStart)
    (*(code **)(*pBaseObj + 0x7c))();

    // Handle specific interaction types
    if (interactionType == 1 || interactionType == 2)
    {
        // Check if interaction is allowed via vtable function at offset 0x184
        if (*pInteractableObjPtr == 0)
            pBaseObj = nullptr;
        else
            pBaseObj = (int *)(*pInteractableObjPtr - 0x48);
        canInteract = (**(code **)(*pBaseObj + 0x184))();
        if (canInteract)
        {
            // Prepare buffer for interaction data (global value)
            dummy1 = 0;
            dummy2 = 0;
            dummy3 = 0;
            globalVal = _DAT_00d5780c; // global variable

            // Call vtable function at offset 0x90 to get interaction data
            (**(code **)(*this + 0x90))(buffer1, this + 0x1c4, 1);

            objPtr = *pInteractableObjPtr;

            if (interactionType == 1)
            {
                // Simple interaction: get transform from object and apply
                if (objPtr == 0)
                    pBaseObj = nullptr;
                else
                    pBaseObj = (int *)(objPtr - 0x48);
                objPtr = *pBaseObj;
                // Note: apiStack_64[0] is likely a misidentified variable; assume it's some global or this
                // Using a placeholder: assume it's a pointer from a previous call or global
                // For reconstruction, we'll call with nullptr and ignore result
                someTransform = (**(code **)(*((int*)0) + 0x58))(0, 0, 0); // FIXME: likely wrong
                (**(code **)(objPtr + 0x170))(buffer2, someTransform);
            }
            else // interactionType == 2
            {
                // Complex interaction: find an entity by ID and set flags
                if (objPtr == 0)
                    pBaseObj = nullptr;
                else
                    pBaseObj = (int *)(objPtr - 0x48);

                // Find entity by ID (0xf26fb813)
                int *foundEntity = nullptr;
                canInteract = (**(code **)(*pBaseObj + 0x10))(0xf26fb813, &foundEntity);

                if (canInteract &&
                    this != nullptr &&
                    (objPtr = FUN_006bc8b0(this), objPtr != 0) &&
                    (canInteract = FUN_009b11f0(), canInteract) &&
                    (objPtr = FUN_00625050(0x8aeb8c80, 0), objPtr != 0) &&
                    (someObj = FUN_0073b460(), someObj != 0) &&
                    (someObj = FUN_006ad790(*(int *)(someObj + 0xc), 0x36cac259), someObj != 0) &&
                    (canInteract = FUN_0070b4d0(buffer3, someObj), canInteract))
                {
                    // Set flags on success
                    *(unsigned int *)(objPtr + 0x74) |= 0x400000;
                    *(unsigned short *)((int)this + 0x39e) |= 0x80;
                }
            }
            goto cleanup;
        }
    }

    // Fallback: call another pre-action and then a function on the base object
    FUN_00707610();
    if (*pInteractableObjPtr == 0)
        objPtr = 0;
    else
        objPtr = *pInteractableObjPtr - 0x48;
    FUN_004088c0(objPtr + 0x3c);

cleanup:
    // Clean up the interactable object pointer
    if (*pInteractableObjPtr != 0)
    {
        FUN_004daf90(pInteractableObjPtr);
        *pInteractableObjPtr = 0;
    }
    return;
}