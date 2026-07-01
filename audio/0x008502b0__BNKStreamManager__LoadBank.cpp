// FUNC_NAME: BNKStreamManager::LoadBank
void __fastcall BNKStreamManager::LoadBank(int this) // __fastcall with this in ecx (or __thiscall)
{
    int iVar1;
    undefined4 uVar2;
    int *piVar3;
    char *puVar4;
    char *puVar5;
    char local_870[12]; // Three ints used by FUN_004b4c90
    char *local_864[2];
    code *pcStack_85c;
    uint local_854;
    uint local_850;
    int local_8;

    // Set bank type to 3 (maybe streaming, preloaded, etc.)
    *(int *)(this + 0x84) = 3;

    FUN_0088d680(); // Global audio system init

    // Set bit 2 in global flag (DAT_011298d4 + 0x10)
    *(uint *)(DAT_011298d4 + 0x10) |= 4;

    // General initialization calls
    FUN_004e0620(0);
    FUN_00455be0(1);

    // Allocate a bank creation structure (size 0x48)
    iVar1 = FUN_009c8e50(0x48);
    if (iVar1 == 0) {
        uVar2 = 0;
    } else {
        // Initialize the structure with position data (this+0xa0, this+0xa4)
        local_870[0] = 0;
        local_870[4] = 0;
        local_870[8] = 0;
        uVar2 = FUN_004b4c90(*(int *)(this + 0xa0), *(int *)(this + 0xa4), &local_870, 0);
    }
    // Store the result for later use (e.g., bank handle)
    *(int *)(this + 0x9c) = uVar2;

    // Register a callback function for this bank
    FUN_004b4c00(FUN_0084f9c0, this);

    // Additional stream initialization
    FUN_004b1f30();

    // Prepare flags for the load operation
    local_8 = *(int *)(this + 0x9c);
    local_850 = DAT_011298d0;
    // Extract bits from flags at +0x90: bit4 inverted -> bit9, bit1 -> bit0
    local_854 = ((~(*(uint *)(this + 0x90) >> 3) & 1) << 9);
    if ((*(uint *)(this + 0x90) >> 1 & 1) != 0) {
        local_854 |= 1;
    }

    // Get category string from index (this+0x94)
    uVar2 = FUN_009c7df0(*(int *)(this + 0x94));

    // Get path components, default to empty string if null
    puVar4 = *(char **)(this + 0x60);
    if (puVar4 == (char *)0x0) {
        puVar4 = &DAT_0120546e; // empty string
    }
    puVar5 = *(char **)(this + 0x70);
    if (puVar5 == (char *)0x0) {
        puVar5 = &DAT_0120546e;
    }

    // Build the full bank file path: basePath/category/filename
    FUN_004d4a60(local_864, 1, "%s/%s/%s", puVar5, uVar2, puVar4);

    // Possibly allocate or open the file
    FUN_004d5900(1);

    // Default to empty string if path construction failed
    if (local_864[0] == (char *)0x0) {
        local_864[0] = &DAT_0120546e;
    }

    // Load the bank file from the constructed path
    FUN_004b24f0(local_864[0]);

    // Reset the ready/loaded flag
    *(int *)(this + 0x8c) = 0;

    // Get system manager and call its virtual function with flags
    piVar3 = (int *)FUN_004b4230();
    *(int **)(this + 0x98) = piVar3;
    (**(code **)(*piVar3 + 4))(&local_854);

    // Release temporary strings
    FUN_00408680(&DAT_01218020);
    FUN_00408680(&DAT_012069b4);

    // Free the allocated structure if needed
    if (local_870[8] != 0) {
        (*pcStack_85c)(local_870[8]); // cleanup callback
    }
    return;
}