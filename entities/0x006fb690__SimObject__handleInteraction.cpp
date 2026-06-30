// FUNC_NAME: SimObject::handleInteraction
// Address: 0x006fb690
// This function processes an interaction action, resolving the action's target and optionally sending a message to the actor's target.
// It takes a "this" pointer to a SimObject (or derived), an action ID (or event type), a controller index, and an optional output pointer.
// Offsets: +0x60 actorGUID (16 bytes), +0x70 isLocalFlag, +0x74 targetObjectID, +0x78 targetName, +0x8c field_8c, +0x90 actionGUID (16 bytes)

int __fastcall SimObject::handleInteraction(int this, int actionId, int controllerIndex, int* outResult) {
    char* targetName;
    int* targetObjectID;
    int* actorPtr;
    int iVar2;
    int* piVar3;
    int* piVar4;
    int uVar5;
    int unaff_EBX = controllerIndex; // mapped from unaff_EBX (likely edx)
    int unaff_ESI = actionId;       // mapped from unaff_ESI (likely stack param)
    int iStack_b4 = controllerIndex; // iStack_b4 is actually the same as unaff_EBX? But careful: decompiler shows iStack_b4 used as index, unaff_EBX as pointer. So likely different.
    // Actually, re-examine: The decompiler shows iStack_b4 used in array index, unaff_EBX used as pointer write. So they might be distinct parameters.
    // Let's assume the function has 4 parameters: this, param_2 (unaff_EBX), param_3 (unaff_ESI), param_4 (iStack_b4).
    // But the decompiler has iStack_b4 as a local variable that is never assigned, implying it's actually a parameter passed on stack.
    // To simplify, I'll keep the original register names and treat them as parameters.

    // Initial check: if actionGUID is not a specific invalid GUID and not zero, try to find the action object
    if ( (*(int*)(this + 0x90) != -0x45245246 || *(int*)(this + 0x94) != -0x41104111 || 
          *(int*)(this + 0x98) != -0x153ea5ab || *(int*)(this + 0x9c) != -0x6eeff6ef) &&
         (*(int*)(this + 0x90) != 0 || *(int*)(this + 0x94) != 0 ||
          *(int*)(this + 0x98) != 0 || *(int*)(this + 0x9c) != 0) ) 
    {
        actorPtr = findObjectByGUID((int*)(this + 0x90), 0); // FUN_00446100
        if (actorPtr != 0 && (*(byte*)(actorPtr + 0x40) & 1) != 0) {
            iVar2 = getGameManager(); // FUN_008e33f0
            if (iVar2 != 0) {
                targetObjectID = (int*)(iVar2 + 0x118);
                targetName = (char*)(iVar2 + 0x11c);
                if (targetObjectID != 0) goto LAB_006fb727;
            }
        }
    }
    // If no valid action target, use the object's own target
    targetObjectID = *(int**)(this + 0x74);
LAB_006fb727:
    // If target name is not set, try object's targetName field, else use default string
    if ((targetName == 0) || (*targetName == '\0')) {
        targetName = *(char**)(this + 0x78);
        if (targetName == 0) {
            targetName = &DAT_0120546e; // default string constant
        }
    }

    // Resolve the actor from the object's actor GUID at +0x60
    piVar3 = (int*)findObjectByGUID((int*)(this + 0x60), 0); // FUN_00446100
    if (piVar3 != 0) {
        int local_a0 = 0;
        char cVar1 = (**(code**)(*piVar3 + 0x10))(0x38523fc3, &local_a0); // virtual call with hash
        int uStack_b0 = 0;
        piVar4 = (int*)(-(uint)(cVar1 != '\0') & uStack_a8); // uStack_a8 is from stack, likely uninitialized-> bug? Probably this is a parameter
        cVar1 = (**(code**)(*piVar3 + 0x10))(0x369ac561, &uStack_b0); // another virtual call
        if (cVar1 != '\0') {
            if (*(char*)(this + 0x70) != '\0') { // isLocal? 
                FUN_00737940(iStack_b4, unaff_ESI); // likely send feedback to UI
                return 1;
            }
            FUN_0072d290(); // likely handle AI response
            return 1;
        }
        if (piVar4 != 0) {
            if (*(char*)(this + 0x70) == '\0') {
                FUN_004df600(); // AI handling
            }
            else {
                iVar2 = FUN_00471610(); // get some object info
                // Build a message block on stack using global values
                int uStack_64 = _DAT_00d5780c; // global constant
                int uStack_78 = _DAT_00d5780c;
                int uStack_8c = _DAT_00d5780c;
                int local_a0 = _DAT_00d5780c;
                int uStack_94 = 0;
                int uStack_90 = 0;
                int uStack_98 = 0;
                int uStack_9c = 0;
                int uStack_84 = 0;
                int uStack_7c = 0;
                int uStack_80 = 0;
                int uStack_88 = 0;
                int uStack_74 = 0;
                int uStack_70 = *(int*)(iVar2 + 0x30);
                int uStack_6c = *(int*)(iVar2 + 0x34);
                int uStack_68 = *(int*)(iVar2 + 0x38);
                char auStack_60[92];
                FUN_0044b4e0(auStack_60, &local_a0); // serialize or process the block
                int uStack_a8 = *(int*)(this + 0x8c); // field_8c
                targetName = 0;
                targetObjectID = 0;
                uVar5 = (**(code**)(*piVar4 + 0x58))(0, piVar4, 0xffffffff, &targetName); // virtual send
                uVar5 = FUN_0045c740(&stack0xffffff48, *(int*)(&DAT_00e51588 + iStack_b4 * 4), auStack_60, uVar5);
                FUN_00414db0(uVar5); // process result
                if (unaff_EBX != 0) {
                    *(int*)(unaff_EBX + 8) = 0; // set output result to 0
                    return 1;
                }
            }
            return 1;
        }
    }
    return 0;
}