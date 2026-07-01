// FUNC_NAME: PlayerF2FSM::updateF2FAnimations
void __fastcall PlayerF2FSM::updateF2FAnimations(int this)
{
    int iVar1;
    int *piVar2;
    float fVar3;
    int iVar5;
    int loopCount;
    float local_1d8;
    float fStack_1d4;
    float fStack_1d0;
    float fStack_1cc;
    // ... (large stack array declarations omitted for brevity)
    float fStack_9c;
    char auStack_98[48];
    int uStack_68;
    int uStack_64;
    int uStack_60;
    int uStack_5c;
    char auStack_58[84];

    local_1d8 = 0.0f;
    // Get blend value from animation system (0xAE986323 is likely a hash for "blend" or similar)
    (**(code **)(**(int **)(this + 0xc) + 0x10))(0xae986323, &local_1d8);

    // Initialize some state
    uStack_cc = 0;
    uStack_bc = 0;
    uStack_ac = 0;
    fStack_9c = _DAT_00d5780c; // likely a constant like 1.0f or 0.0f

    // Update animation system
    FUN_00471610(); // likely AnimationManager::update
    FUN_00994960(); // likely some animation state update

    loopCount = 0;
    // Iterate through animation slots (each 0xC0 bytes)
    if (0 < *(int *)(this + 0x38)) {
        iVar5 = 0;
        do {
            piVar2 = (int *)(*(int *)(this + 0x34) + iVar5);
            FUN_00aa1c50(piVar2 + 4); // likely getAnimationState or similar

            iVar1 = *piVar2; // animation state pointer
            // Copy animation data from state
            uStack_10c = *(int *)(iVar1 + 0xfc);
            uStack_128 = *(int *)(iVar1 + 0xe0);
            uStack_124 = *(int *)(iVar1 + 0xe4);
            uStack_120 = *(int *)(iVar1 + 0xe8);
            uStack_11c = *(int *)(iVar1 + 0xec);
            uStack_118 = *(int *)(iVar1 + 0xf0);
            uStack_114 = *(int *)(iVar1 + 0xf4);
            uStack_110 = *(int *)(iVar1 + 0xf8);
            uStack_188 = *(int *)(iVar1 + 0x100);
            uStack_184 = *(int *)(iVar1 + 0x104);
            uStack_180 = *(int *)(iVar1 + 0x108);
            uStack_17c = *(int *)(iVar1 + 0x10c);
            uStack_138 = *(int *)(iVar1 + 0x110);
            uStack_134 = *(int *)(iVar1 + 0x114);
            uStack_130 = *(int *)(iVar1 + 0x118);
            uStack_ec = *(int *)(iVar1 + 0x11c);

            // Copy to output arrays
            uStack_108 = uStack_188;
            uStack_104 = uStack_184;
            uStack_100 = uStack_180;
            uStack_fc = uStack_17c;
            uStack_f8 = uStack_138;
            uStack_f4 = uStack_134;
            uStack_f0 = uStack_130;
            uStack_dc = uStack_10c;

            FUN_00aa1fc0(auStack_58); // likely processAnimationData

            // Initialize blend weights
            uStack_1bc = 0;
            uStack_1ac = 0;
            uStack_19c = 0;
            fStack_18c = _DAT_00d5780c;

            FUN_00aa1a10(&uStack_178); // likely computeBlendWeights

            // Copy blend results
            uStack_1c8 = uStack_178;
            uStack_1c4 = uStack_174;
            uStack_1c0 = uStack_170;
            uStack_1b8 = uStack_168;
            uStack_1b4 = uStack_164;
            uStack_1b0 = uStack_160;
            uStack_1a8 = uStack_158;
            uStack_1a4 = uStack_154;
            uStack_1a0 = uStack_150;
            uStack_198 = uStack_148;
            uStack_194 = uStack_144;
            uStack_190 = uStack_140;

            // Reset and recompute
            uStack_16c = 0;
            uStack_15c = 0;
            uStack_14c = 0;
            fStack_13c = _DAT_00d5780c;

            FUN_009948e0(&uStack_178); // likely applyAnimationBlend

            // Copy again
            uStack_1c8 = uStack_178;
            uStack_1c4 = uStack_174;
            uStack_1c0 = uStack_170;
            uStack_1b8 = uStack_168;
            uStack_1b4 = uStack_164;
            uStack_1b0 = uStack_160;
            uStack_1a8 = uStack_158;
            uStack_1a4 = uStack_154;
            uStack_1a0 = uStack_150;
            uStack_198 = uStack_148;
            uStack_194 = uStack_144;
            uStack_190 = uStack_140;

            fStack_18c = _DAT_00d5780c;
            uStack_1bc = 0;
            uStack_1ac = 0;
            uStack_19c = 0;

            FUN_00aa1a80(&uStack_1c8); // likely finalizeAnimation
            FUN_00aa3930(auStack_98); // likely applyToSkeleton

            // Normalize blend direction vector
            fVar3 = fStack_1cc * fStack_1cc + fStack_1d0 * fStack_1d0 + fStack_1d4 * fStack_1d4 + local_1d8 * local_1d8;
            if (fVar3 == 0.0f) {
                fVar3 = 0.0f;
            } else {
                fVar3 = _DAT_00d5780c / SQRT(fVar3);
            }
            local_1d8 = fVar3 * local_1d8;
            fStack_1d4 = fStack_1d4 * fVar3;
            fStack_1d0 = fStack_1d0 * fVar3;
            fStack_1cc = fStack_1cc * fVar3;

            // Apply blend to animation target
            FUN_0055ab30(&local_1d8, piVar2[0x29]); // likely setAnimationBlend

            iVar1 = piVar2[0x29];
            *(int *)(iVar1 + 0x10) = uStack_68;
            *(int *)(iVar1 + 0x14) = uStack_64;
            *(int *)(iVar1 + 0x18) = uStack_60;
            *(int *)(iVar1 + 0x1c) = uStack_5c;

            FUN_0045ee00(piVar2[0x29], 1); // likely enableAnimation

            iVar5 += 0xc0; // advance to next slot
            loopCount++;
        } while (loopCount < *(int *)(this + 0x38));
    }

    // Update face animation
    iVar5 = 0;
    FUN_00461070(*(int *)(this + 0x6c)); // likely updateFaceAnimation

    // Disable unused animations
    if (0 < *(int *)(this + 0x60)) {
        do {
            FUN_0045ee00(*(int *)(*(int *)(this + 100) + iVar5 * 4), 0); // disableAnimation
            iVar5++;
        } while (iVar5 < *(int *)(this + 0x60));
    }
    return;
}