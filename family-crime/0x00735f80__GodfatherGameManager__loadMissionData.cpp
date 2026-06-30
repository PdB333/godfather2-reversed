// FUNC_NAME: GodfatherGameManager::loadMissionData
void __thiscall GodfatherGameManager::loadMissionData(int this) {
    char cVar1;
    int iVar2;
    int iVar3;
    undefined4 uVar4;

    // Check bit 26 of flags at +0x1f58 - if not set, proceed with loading
    if ((*(uint *)(this + 0x1f58) >> 0x1a & 1) == 0) {
        // Set the bit to indicate this data is being loaded
        *(uint *)(this + 0x1f58) |= 0x4000000;

        uVar4 = *(undefined4 *)(this + 0x216c);  // Some parameter (e.g., session ID)
        iVar3 = this + 0x214c;                    // Pointer to structure A
        iVar2 = this + 0x213c;                    // Pointer to structure B

        // Call mission/save loader with hash 0x369ac561 (probably a resource key)
        FUN_008e9cb0(0x369ac561, iVar2, iVar3, uVar4, this);

        cVar1 = FUN_008f00d0(iVar2, iVar3, uVar4, this); // Validate loaded data
        if (cVar1 == '\0') {
            // Load failed – clean up the string at +0x3c
            FUN_004088c0(this + 0x3c);
            return;
        }

        // If the state at +0x2178 is set and not 0x48 (e.g., "none"), perform additional setup
        if ((*(int *)(this + 0x2178) != 0) && (*(int *)(this + 0x2178) != 0x48)) {
            FUN_0043b870(DAT_01131010); // Some global dialog or callback
            FUN_009add60(1);            // Set a flag or trigger an event
        }
    }
    return;
}