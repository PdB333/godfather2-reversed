// FUNC_NAME: SimManager::update
void __thiscall SimManager::update(int thisPtr)
{
    int iVar1;
    float fVar2;
    char cVar3;
    int iVar4;
    float10 fVar5;
    float deltaTime;
    undefined4 local_c;
    undefined4 local_8;
    undefined1 local_4;

    // Retrieve the object associated with this+0x2134 (likely a handle/index)
    iVar4 = FUN_006b0ee0(*(undefined4 *)(thisPtr + 0x2134));
    if (iVar4 != 0) {
        fVar5 = (float10)FUN_007352b0();           // Get game delta time (80-bit float)
        deltaTime = (float)fVar5;
        if ((float10)DAT_00d5f378 <= fVar5) {      // If delta exceeds a threshold, log warning
            FUN_00894c90(0xd1a7f352);
        }
        // Check if a pointer at +0x1f50 is valid and its flag at +0x3c (bit 0) is set
        if ((*(int *)(thisPtr + 0x1f50) != 0) &&
           ((*(byte *)(*(int *)(thisPtr + 0x1f50) + 0x3c) & 1) != 0)) {
            deltaTime = deltaTime * _DAT_00d5ca64; // Apply global time scale
            FUN_00894c90(0x63650a64);              // Log the scale application
        }
        // Dereference a global pointer (likely a singleton) and verify its structure
        iVar1 = **(int **)(DAT_012233a0 + 4);
        if ((((iVar1 != 0) && (iVar1 != 0x1f30)) && (*(int *)(iVar1 + -0x58) != 0)) &&
           (*(int *)(iVar1 + -0x58) != 0x48)) {
            fVar2 = (float)*(int *)(iVar4 + 200);   // Get some value from the retrieved object (offset 200)
            if (*(int *)(iVar4 + 200) < 0) {
                fVar2 = fVar2 + DAT_00e44578;       // Adjust negative values
            }
            FUN_008c09a0(fVar2 * deltaTime, 1);    // Scale and send to some system
        }
        // Check bit 3 of the bitfield at +0x1f98
        if (((*(uint *)(thisPtr + 0x1f98) >> 3 & 1) != 0) && (cVar3 = FUN_0071fa00(), cVar3 == '\0')) {
            FUN_00894c90(0xc2370d9e);              // Log if condition fails
        }
    }
    iVar4 = FUN_00806440();                          // Check some global state (e.g., menu active)
    if (iVar4 != 1) {
        *(undefined4 *)(thisPtr + 0x2138) = 0x637b907; // Store a hash/timestamp
        FUN_008c74d0(0x637b907);                     // Notify system
        FUN_007196a0(*(undefined4 *)(thisPtr + 0x2138)); // Process the hash
    }
    local_c = DAT_0112a658;                          // Likely a constant or global state
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c, 0);                      // Reset or initialize a local structure
    return;
}
```