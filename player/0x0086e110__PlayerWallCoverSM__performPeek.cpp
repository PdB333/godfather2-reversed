// FUNC_NAME: PlayerWallCoverSM::performPeek

char __fastcall PlayerWallCoverSM::performPeek(int this)
{
    float *pfVar1;
    int *pVtable;
    float fVar3;
    int iVar4;
    int iSkeleton;
    float10 fVar6;
    char result;
    char peekOutcome; // local_2e
    float peekAnimTime; // local_2c
    float fStack_28; // random float
    undefined4 local_24; // camera target?
    float fStack_c;
    float fStack_8;
    float fStack_4;
    undefined4 local_20; // used in vector
    undefined4 local_1c; // zero
    undefined4 local_18; // zero
    undefined4 local_14; // zero
    undefined4 local_10; // zero
  
    // Global game time pointer (DAT_0112af68)
    iVar4 = DAT_0112af68;
    // Initialize local variables
    local_1c = 0;
    local_20 = 0;
    local_24 = 0;
    local_10 = 0;
    local_14 = 0;
    local_18 = 0;
    result = '\0';
    peekOutcome = '\0';
  
    // Check if current game time (at offset 0x168) is within peek time window
    // and peek action count (at this+0xac) is under limit
    if ((*(float *)(DAT_0112af68 + 0x168) <= DAT_00d5ef84) &&
        (*(uint *)(this + 0xac) <= DAT_01205224)) {
        // Check if this object's cover state flags (at this+0x50) indicate "can peek"
        // Bit 3 at offset 200 (0xC8) from this+0x50
        if ((*(byte *)(*(int *)(this + 0x50) + 200) >> 3 & 1) != 0) {
            // Get the skeleton/animation component (this+0x5c)
            pVtable = *(int **)(this + 0x5c);
            // Get peek animation duration via virtual function at offset 0xC0
            peekAnimTime = (float)pVtable[0x2d6]; // maybe field, not virtual? Actually pVtable[0x2d6] is a field after vtable? Wait: pVtable is pointer to vtable? Actually it's a pointer to an object, first int is vtable pointer. So pVtable[0x2d6] is a field at offset 0x2d6*4 = 0x2D6*4 = 0xB58? That seems large. Re-evaluate: The code does: local_2c = (float)piVar2[0x2d6]; That is piVar2[0x2d6] which is a field of the object pointed by piVar2, not a virtual call. Then virtual calls at 0xc0 and 0xc4. So piVar2 is not the vtable but the object itself. So piVar2 is this+0x5c, which is a pointer to a "Skeleton" or "Animation" object. Then piVar2[0x2d6] is a float field at offset 0x2d6*4 = 0x2D6*4 = 0x2D6*4 = 0x2D6*4? Actually 0x2D6 * 4 = 0x2D6 * 4 = 1200? Let's compute: 0x2D6 = 726, *4 = 2904 bytes. That seems plausible for a large animation data structure. So it's likely "animation duration" or "peek time". Let's keep it as "peekAnimTime".
  
            // Get random float via virtual function at vtable offset 0xC0
            fVar6 = (float10)(**(code **)(*pVtable + 0xc0))();
            fStack_28 = (float)fVar6;
            // Get another random float (or maybe max/min) at vtable offset 0xC4
            fVar6 = (float10)(**(code **)(*pVtable + 0xc4))();
  
            // Call function to check if peek action is allowed (maybe line of sight, etc.)
            // Returns bool in local_2d, sets local_2e (peek outcome)
            result = FUN_008f95e0(&local_24, &local_18, &peekOutcome,
                                  ((float10)fStack_28 <= fVar6 * (float10)peekAnimTime) * '\x02' + '\x01');
  
            if (result != '\0') {
                pVtable = *(int **)(this + 0x5c);
                local_20 = local_20 + DAT_00d58cbc; // accumulate some offset
                if (peekOutcome == '\0') {
                    // Play peek-out animation and camera
                    FUN_0086d460(); // e.g. StartPeekOutAnimation
                    // Add animation via virtual at offset 700 (0x2BC)
                    (**(code **)(*pVtable + 700))(&local_24, &local_18, 1);
  
                    // Get player movement controller and scale speed
                    iSkeleton = FUN_00471610(); // e.g. GetMovementController
                    fVar6 = (float10)FUN_00860e70(); // e.g. GetPeekSpeedMultiplier
                    fStack_c = (float)((float10)*(float *)(iSkeleton + 0x20) * fVar6);
                    fStack_8 = (float)((float10)*(float *)(iSkeleton + 0x24) * fVar6);
                    fStack_4 = (float)(fVar6 * (float10)*(float *)(iSkeleton + 0x28));
  
                    // Set peek target position/direction
                    FUN_005466c0(&fStack_c); // e.g. SetTargetVelocity
                    // Push peek camera
                    FUN_008622a0(); // e.g. PushPeekCamera
                }
                else {
                    // Play stand-up (peek-in) animation and camera
                    FUN_008621d0(); // e.g. PopPeekCamera
                    FUN_0086d430(); // e.g. StartStandUpAnimation
                    (**(code **)(*pVtable + 700))(&local_24, &local_18, 1);
                    FUN_004706f0(0); // e.g. PlaySound(0)
                }
  
                // Common post-peek actions
                FUN_0086cac0(1); // e.g. SetPeekState(1)
                FUN_00766470(0x40); // e.g. SetMovementFlag(0x40)
                FUN_0087d560(1); // e.g. SetAnimState(1)
  
                // If skeleton has weapon visibility flag set
                if (((uint)pVtable[0x322] >> 0x15 & 1) != 0) {
                    FUN_0087bd50(1); // e.g. SetWeaponVisible(1)
                }
  
                FUN_00860340(); // e.g. UpdateRootMotion
  
                // Reset peek timer and count
                fVar3 = _DAT_00d5c458; // maximum peek time
                iSkeleton = *(int *)(this + 0x54);
                *(undefined1 *)(iSkeleton + 0x25) = 0; // clear peck lock flag
                *(undefined1 *)(iSkeleton + 0x24) = 0; // clear another flag
                pfVar1 = (float *)(iVar4 + 0x168);
                if (*pfVar1 <= fVar3 && fVar3 != *pfVar1) {
                    *(float *)(iVar4 + 0x168) = fVar3; // extend peek time
                }
                *(undefined4 *)(this + 0xac) = 0; // reset peek count
  
                FUN_0086cc70(); // e.g. ResumeAnimationBlending
  
                // Clear state flags (bitmask at +0x6c)
                *(uint *)(this + 0x6c) = *(uint *)(this + 0x6c) & 0xffffff1f;
  
                // Clear camera offset/rotation
                *(undefined4 *)(this + 0x98) = 0;
                *(undefined4 *)(this + 0x9c) = 0;
                *(undefined4 *)(this + 0xa0) = 0;
  
                FUN_008f8260(); // e.g. UpdateCoverState
            }
        }
        return result;
    }
    return '\0';
}