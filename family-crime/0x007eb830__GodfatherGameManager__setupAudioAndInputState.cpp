// FUNC_NAME: GodfatherGameManager::setupAudioAndInputState
void __fastcall GodfatherGameManager::setupAudioAndInputState(int *this)
{
    char isEnabled;
    int audioManager;
    int *vtable;
    int *someManager;
    int playerObj;
    int soundResource;

    playerObj = this[0x16]; // +0x58: pointer to player object
    audioManager = FUN_007ab150(); // get audio manager
    this[0x1f] = *(int *)(audioManager + 4); // +0x7c: store audio manager field
    vtable = (int *)FUN_007ab150();
    (**(code **)*vtable)(0xf); // call audio manager vtable function with 0xf

    audioManager = FUN_007ab130(); // get input manager
    this[0x1e] = *(int *)(audioManager + 4); // +0x78: store input manager field
    vtable = (int *)FUN_007ab130();
    (**(code **)*vtable)(0x3f); // call input manager vtable function with 0x3f

    FUN_0079f050(0); // set some audio state to 0
    FUN_007f6420(9); // set some input state to 9

    // Release sound resource if present
    if (*(int *)(playerObj + 0x1c78) != 0) {
        FUN_004daf90((undefined4 *)(playerObj + 0x1c78)); // release sound
        *(undefined4 *)(playerObj + 0x1c78) = 0;
    }

    // Clear bit 0x20000 at playerObj+0x249c (likely a flag)
    *(uint *)(playerObj + 0x249c) &= 0xfffdffff;

    FUN_007ab9a0(0, 1); // set audio flag
    FUN_007f63e0(0x17); // set input flag

    // Check if player has a specific state and is not in a certain mode
    if (*(int *)(playerObj + 0x1ed8) != 0 && *(int *)(playerObj + 0x1ed8) != 0x48 && this[0x16] != 0) {
        someManager = (int *)FUN_0043b870(DAT_01130fa0); // get some manager from global
        if (someManager != (int *)0x0) {
            FUN_009b1a60(&stack0xfffffff4, 0x10000, 0x40, 1); // prepare hash
            (**(code **)(*someManager + 0x28))(0xa3dcd6, 0, 0xffffffff, 0); // play sound with hash
        }
    }

    // Update position offset
    soundResource = *(int *)(playerObj + 0x1d90);
    this[0x1d] = DAT_01205224 + soundResource; // +0x74: store adjusted value

    isEnabled = FUN_00481620(); // check if audio is enabled
    if (isEnabled != '\0') {
        soundResource = FUN_0090e2d0(0, soundResource, 2, 0, 0, 0); // load sound resource
        this[0x20] = soundResource; // +0x80: store loaded resource
    }

    isEnabled = FUN_00481660(); // check if input is enabled
    if (isEnabled != '\0') {
        if (this[0x16] != 0) {
            someManager = (int *)FUN_0043b870(DAT_01131018); // get another manager
            (**(code **)(*someManager + 0x3c))(0x3f800000); // set volume to 1.0f
            return;
        }
        (**(code **)(iRam00000000 + 0x3c))(0x3f800000); // fallback volume set
        return;
    }

    isEnabled = FUN_00481640(); // check if don control is active
    if (isEnabled != '\0') {
        *(undefined1 *)(playerObj + 0x241c) = 1; // set flag at +0x241c
        (**(code **)(*(int *)playerObj + 0x234))(1, 1); // call player vtable function
        (**(code **)(*this + 0x2c))(0x82cdc9c, 1, 1, 0, 0x3f800000, 0x3f800000); // call this vtable function with hash
    }
    return;
}