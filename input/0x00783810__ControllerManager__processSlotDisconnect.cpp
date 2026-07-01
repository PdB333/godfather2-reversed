// FUNC_NAME: ControllerManager::processSlotDisconnect
void __thiscall ControllerManager::processSlotDisconnect(int param_2)
{
    undefined4 uVar1;
    char cVar2;
    int iVar3;
    uint uVar4;

    // param_2 likely points to a controller state or player info struct
    uVar1 = *(undefined4 *)(param_2 + 0x88); // +0x88: controller ID or handle to match
    uVar4 = 0;
    if (*(int *)(this + 0x68) != 0) { // +0x68: number of active slots
        do {
            // slot array at this+0x64, each entry 8 bytes (pointer + auxiliary data)
            iVar3 = *(int *)(*(int *)(this + 100) + uVar4 * 8); // first 4 bytes: slot object pointer
            // Check if slot is valid and matches the provided ID
            if (((iVar3 == 0) ||
                 // offset -0x48? Probably a misinterpretation; often sub-object at +0x48
                 (iVar3 = iVar3 + -0x48, iVar3 == 0)) ||
                (cVar2 = compareSlotID(iVar3, uVar1), cVar2 == '\0')) {
                uVar4 = uVar4 + 1;
            }
            else {
                // Found matching slot – remove it
                removeSlotByIndex(uVar4);
            }
        } while (uVar4 < *(uint *)(this + 0x68)); // iterate all slots
    }
    // Check bit 1 of flags at this+0x74 (e.g., 0x02 = "hasActiveConnection")
    if ((*(uint *)(this + 0x74) >> 1 & 1) != 0) {
        notifyDisconnect(*(undefined4 *)(param_2 + 0x54)); // +0x54: session/connection identifier
    }
    return;
}