// FUNC_NAME: GameStateManager::applyStateSettings
// Function at 0x0042f860 - Configures game state settings and transitions based on state type.
// Uses a virtual table from base class to perform polymorphic operations.

void GameStateManager::applyStateSettings(int param_1)
{
    char cVar1;
    int *piVar2;
    uint uVar3;

    // Obtain vtable pointer from base class (FUN_00432cd0 likely returns a reference to vtable)
    piVar2 = (int *)FUN_00432cd0(this, param_1);

    // Current state type at offset +0x39f8
    uVar3 = *(uint *)(this + 0x39f8);

    // Set two options based on state type
    if (uVar3 == 1) {
        // Option 1 = 2, Option 2 = 1
        *(uint *)(this + 0x108c) = 2;
        *(uint *)(this + 0x1090) = 1;
    } else {
        // Option 1 = 1, Option 2 = 2
        *(uint *)(this + 0x108c) = 1;
        *(uint *)(this + 0x1090) = 2;
    }

    // Modify state type if it's 0 or 3 -> becomes 1; otherwise clear lower byte
    if ((uVar3 == 0) || (uVar3 == 3)) {
        uVar3 = 1;
    } else {
        uVar3 = uVar3 & 0xffffff00;
    }

    // Virtual function calls through vtable (indices: 2, 3, 8, etc.)
    VirtualFunc* vtable = (VirtualFunc*)piVar2;

    vtable[2](this + 0x1120, this + 0x10e0, uVar3);   // vtable[2] at offset 0x8
    vtable[3]();                                        // vtable[3] at offset 0xc
    vtable[8](param_1);                                 // vtable[8] at offset 0x20
    cVar1 = vtable[10](param_1, this + 0x10d0);        // vtable[10] at offset 0x28

    if (cVar1 == '\0') {
        FUN_00430790(this, 0, 0, 0);                   // Handle negative case
    } else {
        vtable[6]();                                    // vtable[6] at offset 0x18

        // Clamp resolution globals (DAT_012058d0 = width, DAT_00f15988 = height?)
        if (DAT_012058d0 < 7) {
            DAT_012058d0 = 7;
        }
        if (7 < DAT_00f15988) {
            DAT_00f15988 = 7;
        }
        _DAT_011f39f4 = 0;                              // e.g., windowed mode flag

        if (DAT_012058d0 < 0x16) {
            DAT_012058d0 = 0x16;
        }
        if (0x16 < DAT_00f15988) {
            DAT_00f15988 = 0x16;
        }
        _DAT_011f3a30 = 1;                              // e.g., v-sync enabled

        vtable[11](param_1, 0, 0);                      // vtable[11] at offset 0x2c
        vtable[13]();                                   // vtable[13] at offset 0x34
        FUN_00412f90(*(uint *)(this + 0x108c));         // Option 1 as parameter

        if (DAT_012058d0 < 7) {
            DAT_012058d0 = 7;
        }
        if (7 < DAT_00f15988) {
            DAT_00f15988 = 7;
        }
        _DAT_011f39f4 = 1;                              // restore/change flag

        vtable[7]();                                    // vtable[7] at offset 0x1c
    }

    vtable[4]();                                        // vtable[4] at offset 0x10

    // Final clamping
    if (DAT_012058d0 < 0x16) {
        DAT_012058d0 = 0x16;
    }
    if (0x16 < DAT_00f15988) {
        DAT_00f15988 = 0x16;
    }
    _DAT_011f3a30 = 1;

    return;
}