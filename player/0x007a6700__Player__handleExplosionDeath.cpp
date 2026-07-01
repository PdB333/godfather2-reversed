// FUNC_NAME: Player::handleExplosionDeath

void __fastcall Player::handleExplosionDeath(int this)
{
    char cVar1;
    float* pMatrix;
    int spawnParams[5]; // offset 0x0: pointer (maybe callback), others: unknown
    int outputBuffer[4]; // 16 bytes, output of effect spawn
    float matrix[16]; // 4x4 matrix (transform)
    int* paramPtr;
    int effectFlags[1]; // likely flags for effect spawn
    int spawnResult;

    // Check if the game is in a state where this can happen (e.g., not paused)
    cVar1 = isGameActive(); // FUN_00481620
    if (cVar1 == 0) {
        return;
    }

    // Check if the player is dead (or if this is a multiplayer state where explosion is allowed)
    cVar1 = isPlayerDead(); // FUN_00481660 - returns true if player is dead or in a state that disables explosion?
    if (cVar1 != 0) {
        return;
    }

    // Bit 0xe (14) of flags at offset 0x24a4: possibly "hasExploded" flag
    if ((*(uint*)(this + 0x24a4) >> 0xe & 1) != 0) {
        return;
    }

    // Get the camera (or player) transform from the render manager (or CameraManager)
    // FUN_004262f0(0) returns a pointer to a struct containing 16 floats (4x4 matrix) at +0x40..+0x7c
    {
        void* someManager = getSomeManager(); // FUN_004262f0(0)
        float* pSourceMatrix = (float*)((int)someManager + 0x40);
        for (int i = 0; i < 16; i++) {
            matrix[i] = pSourceMatrix[i];
        }
        // Actually the decompiled code directly reads 16 floats from consecutive addresses using multiple undefined4 assignments.
        // We'll just copy the memory.
    }

    // Prepare effect spawn parameters
    // local_84 is an array of 5 ints. Struct layout:
    // +0: pointer (maybe callback object)
    // +4: something (set to 0)
    // +8: something (set to 0)
    // +12: something (set to 0)
    // +16: global constant _DAT_00d5780c (some ID or flag)
    spawnParams[0] = 0; // will be set later if effect spawn returns a pointer
    spawnParams[1] = 0;
    spawnParams[2] = 0;
    spawnParams[3] = 0;
    spawnParams[4] = s_globalExplodeID; // _DAT_00d5780c (unknown global)

    // local_70 = 5; flags for spawn function (e.g., effect type)
    effectFlags[0] = 5;

    // Register/load the "char_expld" effect template
    loadEffectTemplate("char_expld"); // FUN_004eacb0

    // Spawn the effect:
    // Param1: pointer to spawnParams (input/output)
    // Param2: outputBuffer (receives handle or pointer to effect instance)
    // Param3: pointer to matrix array
    // Param4: 0x1ff (511) - possibly effect ID or const
    // Param5: 4 - priority
    // Param6: pointer to effectFlags
    spawnResult = spawnEffect(spawnParams, outputBuffer, matrix, 0x1ff, 4, effectFlags); // FUN_004df3c0

    // Play sound/attach audio to the spawned effect
    playEffectSound(spawnResult); // FUN_00414db0

    // If the spawn returned a non-null pointer in spawnParams[0], clear its +8 field
    if (spawnParams[0] != 0) {
        *(int*)(spawnParams[0] + 8) = 0; // possibly clearing a callback or ref count
    }

    // Set the "hasExploded" flag to prevent re-triggering
    *(uint*)(this + 0x24a4) |= 0x4000; // bit 0x4000 = 2^14
}