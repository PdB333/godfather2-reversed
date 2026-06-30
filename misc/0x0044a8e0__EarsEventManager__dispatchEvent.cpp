// FUNC_NAME: EarsEventManager::dispatchEvent
void __thiscall EarsEventManager::dispatchEvent(void) {
    int *piVar1;
    code *pcVar2;
    uint uVar3;
    undefined4 *puVar4;
    int *piVar5;
    // unaff_ESI is this

    // Check if state is non-zero and not 0x48 (likely an initialization flag)
    if ((*(int *)(this + 0xc) != 0) && (*(int *)(this + 0xc) != 0x48)) {
        // If state is invalid, call a method on the object at this+0x14 (release?)
        if (*(int *)(this + 0xc) != 0) {
            (**(code **)(*(int *)(*(int *)(this + 0xc) - 0x48) + 0x5c))(*(undefined4 *)(this + 0x14), -1);
            return;
        }
        (**(code **)(iRam00000000 + 0x5c))(*(undefined4 *)(this + 0x14), -1);
        return;
    }

    piVar1 = *(int **)(this + 4); // Event ID or key
    uVar3 = 0;
    // Global event manager singleton at 0x1223410
    if (*(uint *)(DAT_01223410 + 0x2d0) != 0) { // Number of registered handlers
        piVar5 = (int *)(DAT_01223410 + 0xd0); // Array of {id, handlerPtr} pairs
        while (*piVar5 != *piVar1) {
            uVar3 = uVar3 + 1;
            piVar5 = piVar5 + 2;
            if (*(uint *)(DAT_01223410 + 0x2d0) <= uVar3) {
                return; // Handler not found
            }
        }
        pcVar2 = (code *)piVar5[1]; // Found handler function pointer
        if (pcVar2 != (code *)0x0) {
            // Prepare context via vtable at this+8
            (**(code **)(**(int **)(*(int *)(this + 8) + 8) + 0x1c))();
            // Stack canaries (debug markers) – will be overwritten by hash
            uStack_28 = 0xbadbadba;
            uStack_24 = 0xbeefbeef;
            uStack_20 = 0xeac15a55;
            uStack_1c = 0x91100911;
            // Get a 16-byte hash from the event ID string handle (this+0x18)
            puVar4 = (undefined4 *)FUN_00449be0(*(undefined2 *)(this + 0x18));
            uStack_28 = *puVar4;
            uStack_24 = puVar4[1];
            uStack_20 = puVar4[2];
            uStack_1c = puVar4[3];
            // Call the handler: handler(eventId, &hash, flags=0, param, actionType=5)
            (*pcVar2)(*piVar1, &uStack_28, 0, *(undefined4 *)(this + 0x14), 5);
        }
    }
    return;
}