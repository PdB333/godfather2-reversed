// FUNC_NAME: Entity::updateState
void __fastcall Entity::updateState(int thisPtr)
{
    int iVar1;
    int iVar2;
    char cVar3;
    undefined4 uVar4;
    int esiVal; // unaff_ESI - preserved from caller, likely a context pointer
    int *piVar5;
    undefined4 localStack94[15];
    char localStack58[84]; // 84 bytes buffer

    iVar1 = *(int *)(thisPtr + 0xc4); // +0xC4: pointer to some subobject (e.g., AI component)
    if ((iVar1 == 0) || (piVar5 = (int *)(iVar1 + -0x48), piVar5 == (int *)0x0)) {
        // If subobject missing or derived pointer invalid
        if (((*(uint *)(*(int *)(thisPtr + 0x10) + 0x14) & 0x1000) != 0) && // +0x10 -> +0x14: some global flag (e.g., game paused)
            (*(int *)(thisPtr + 0xb4) != 0)) {                              // +0xB4: some pointer (e.g., target)
            // Set bit 17 (0x20000) if not set
            if ((*(uint *)(thisPtr + 0xc) & 0x20000) == 0) { // +0xC: flags
                *(uint *)(thisPtr + 0xc) = *(uint *)(thisPtr + 0xc) | 0x20000;
                FUN_0051b120(); // Likely sets some global state (e.g., busy or blocking)
            }
            // Clear bit 18 (0x40000)
            *(uint *)(thisPtr + 0xc) = *(uint *)(thisPtr + 0xc) & 0xfffbffff;
        }
        *(undefined4 *)(thisPtr + 0xb4) = 0;
        FUN_0051d230(0); // Probably clears a related state
    }
    else {
        *(int **)(thisPtr + 0xb4) = piVar5; // Store derived pointer
        uVar4 = (**(code **)(*piVar5 + 0x58))(); // Virtual call (offset 0x58 -> 23rd method?) returns some value
        *(undefined4 *)(thisPtr + 0x84) = uVar4; // Store at +0x84
        localStack94[0] = 0;
        cVar3 = (**(code **)(*piVar5 + 0x10))(0xae986323, localStack94); // Virtual call with hash 0xae986323 (likely an ID)
        // esiVal is expected to be set by caller (e.g., a player or world context)
        if ((((cVar3 != '\0') && (esiVal != 0)) && (iVar2 = *(int *)(esiVal + 0x218), iVar2 != 0)) && ((*(uint *)(iVar2 + 0x10) & 0x4480000) == 0)) {
            // Conditions indicate a valid state: copy data from subobject +0x88 to buffer, then call some functions
            FUN_0044b4e0(localStack58, iVar1 + 0x88); // Copy 84 bytes from iVar1+0x88 to local buffer (maybe animation params)
            FUN_00577b30(iVar2); // Process object at iVar2 (e.g., update animation)
            FUN_00417560(); // Possibly schedule or execute something
            return;
        }
        // If condition fails, check global flag again
        if ((*(uint *)(*(int *)(thisPtr + 0x10) + 0x14) & 0x1000) != 0) {
            if ((*(uint *)(thisPtr + 0xc) & 0x20000) == 0) {
                *(uint *)(thisPtr + 0xc) = *(uint *)(thisPtr + 0xc) | 0x20000;
                FUN_0051b120();
            }
            *(uint *)(thisPtr + 0xc) = *(uint *)(thisPtr + 0xc) & 0xfffbffff;
            return;
        }
    }
    return;
}