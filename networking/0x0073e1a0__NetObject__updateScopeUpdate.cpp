// FUNC_NAME: NetObject::updateScopeUpdate
// Address: 0x0073e1a0
// Role: This function appears to handle scope updates for a networked object. It checks whether the object's scope object differs from the current ghost manager's scope, and if so, builds a bitstream packet and sends it.

// Known classes from context: NetObject, GhostManager, BitStream, NetSession.
// Offsets documented.

void __fastcall NetObject::updateScopeUpdate(int this, int param2) { // param2 may be a pointer to an event or context (unaff_EDI)
    char cVar1;
    int* piVar2;
    int iVar3;
    int param2_local = param2; // unaff_EDI is likely a second parameter (EDX in fastcall)
    undefined*** pppStack_34;
    undefined1 uStack_30;
    undefined** ppStack_2c;
    undefined4 uStack_28;
    int aiStack_24[5];
    undefined1 uStack_10;
    undefined4 uStack_c;

    // Check if the object's scope pointer is valid (+0x5c)
    if ((*(int*)(this + 0x5c) != 0) &&
        // Get the global network session manager
        (piVar2 = (int*)FUN_0043b870(DAT_01131018), piVar2 != (int*)0x0) &&
        // Call virtual function at vtable+0x34 (likely getGhostManager or getConnectionManager)
        (iVar3 = (*(code**)(*piVar2 + 0x34))(), iVar3 != 0)) {
        // Call the same virtual again to get a valid pointer
        iVar3 = (*(code**)(*piVar2 + 0x34))();
        // Check the connection list at offset +0xc and compute the container object by subtracting 0x48
        if ((*(int*)(iVar3 + 0xc) != 0) &&
            (piVar2 = (int*)(*(int*)(iVar3 + 0xc) + -0x48), piVar2 != (int*)0x0) &&
            // Compare the container with the scope object stored in this object (+0x5c)
            (piVar2 != *(int**)(this + 0x5c))) {
            // Initialize a pointer to receive an interface
            pppStack_34 = (undefined***)0x0;
            // Query interface from the container object (virtual at +0x10 with identifier 0x55859efa)
            cVar1 = (*(code**)(*piVar2 + 0x10))(0x55859efa, &pppStack_34);
            if ((cVar1 != '\0') && (param2_local != 0)) {
                // Build a bitstream on the stack
                aiStack_24[4] = 0;
                aiStack_24[3] = 0;
                aiStack_24[2] = 0;
                ppStack_2c = &PTR_FUN_00d5dbbc; // BitStream vtable
                aiStack_24[0] = 0;
                aiStack_24[1] = 0;
                uStack_10 = 0;
                uStack_c = DAT_01205228; // Some global constant
                uStack_28 = 0x8b284db6; // Possibly a checksum or signature
                // Call to send or process the event (param2_local)
                FUN_0044b210(param2_local);
                pppStack_34 = &ppStack_2c;
                uStack_30 = 0;
                // Get the scope object's internal buffer or offset
                if (*(int*)(this + 0x5c) == 0) {
                    iVar3 = 0;
                } else {
                    iVar3 = *(int*)(this + 0x5c) + 0x3c; // +0x3c likely offset to a serializable field
                }
                // Write something to the bitstream (stack buffer)
                FUN_00408bf0(&stack0xffffffc8, iVar3, 0);
                // Cleanup bitstream if allocated
                if (aiStack_24[0] != 0) {
                    FUN_004daf90(aiStack_24);
                }
            }
        }
    }
    return;
}