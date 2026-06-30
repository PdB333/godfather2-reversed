// FUNC_NAME: TextureStageManager::initialize
void __fastcall TextureStageManager::initialize(int *thisPtr)
{
    // Call virtual getters for texture stage data
    int stage0Handle = (**(int (__thiscall **)(int *))(*thisPtr + 0x48))();  // gets first stage base
    (**(void (__thiscall **)(int *))(*thisPtr + 0x54))();                    // some initialization step
    (**(void (__thiscall **)(int *))(*thisPtr + 0x44))();                    // likely stage setup call
    (**(void (__thiscall **)(int *))(*thisPtr + 0x40))();                    // another setup
    int stage1Handle = (**(int (__thiscall **)(int *))(*thisPtr + 0x3c))();  // may be alternative source
    if (stage1Handle != 0) {
        int globalHandle = FUN_0060a380();   // create shared handle (e.g., material system)
        thisPtr[4] = globalHandle;           // +0x10: store global handle
    }
    if (stage0Handle != 0) {
        int dupHandle = FUN_0060a2e0(stage0Handle);  // duplicate or resolve handle
        thisPtr[5] = dupHandle;               // +0x14: store resolved handle
    }

    FUN_006127d0();   // global ref count or init

    thisPtr[0x41] = thisPtr[5];  // +0x104: store resolved handle as first stage base

    // Get stage1 and stage2 handles via virtual calls
    int stage2Handle = (**(int (__thiscall **)(int *))(*thisPtr + 0x4c))();  // second stage base
    int stage2Dup = FUN_0060a2e0(stage2Handle);
    thisPtr[0x42] = stage2Dup;     // +0x108: store second stage base

    int stage3Handle = (**(int (__thiscall **)(int *))(*thisPtr + 0x50))();  // third stage base
    int stage3Dup = FUN_0060a2e0(stage3Handle);
    thisPtr[0x43] = stage3Dup;     // +0x10C: store third stage base

    // Get global texture coordinate parameter indices
    thisPtr[0x2a] = FUN_0060a580(thisPtr[4], "transU");  // +0xA8: transU param
    thisPtr[0x2b] = FUN_0060a580(thisPtr[4], "transV");  // +0xAC: transV param

    // Setup three texture stages with apttexture and kDelta parameters
    int *stageBasePtr = &thisPtr[0x2c];  // +0xB0: start of stage array
    *stageBasePtr = thisPtr[0x41];       // first stage base (from stage0)
    stageBasePtr[3] = thisPtr[0x42];     // second stage base (offset +0xBF? Actually +0x2c+3 = +0x2f)
    stageBasePtr[6] = thisPtr[0x43];     // third stage base (offset +0x32)

    for (int i = 0; i < 3; i++) {
        int *currentStage = stageBasePtr + i * 3;  // each stage occupies 3 ints: base, apttexture, kDelta
        // Get parameter indices for this stage
        currentStage[1] = FUN_0060a580(*currentStage, "apttexture");
        currentStage[2] = FUN_0060a580(*currentStage, "kDelta");
    }

    thisPtr[0x44] = 0;  // +0x110: initialize some flag to zero
}