// FUNC_NAME: Player::updateBusySequence
void __thiscall Player::updateBusySequence(int *this, char param_2, int *param_3, char param_4)
{
    int *pNode;
    char cVar2;
    undefined4 uVar3;
    int *piVar4;
    int *piVar5;
    int iVar6;
    undefined4 *puVar7;
    int iVar8;
    undefined4 uVar9;
    undefined4 *puVar10;
    float10 fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    int iStack_d4;
    int *piStack_d0;
    undefined4 local_cc;
    undefined4 local_c8;
    undefined1 local_c4;
    int aiStack_b8 [4];
    undefined1 auStack_a8 [4];
    undefined1 auStack_a4 [8];
    undefined1 auStack_9c [20];
    undefined8 uStack_88;
    undefined4 uStack_80;
    undefined4 uStack_70;
    undefined4 uStack_6c;
    undefined4 uStack_64;
    undefined4 uStack_5c;
    undefined1 local_50 [76]; // Transform matrix buffer?
    
    // Guard: if busy node pointer at +0x2de is already set, bail out
    if (this[0x2de] != 0) {
        return;
    }
    // If the incoming transform (param_3) is a zero vector, skip
    if ((((*param_3 == 0) && (param_3[1] == 0)) && (param_3[2] == 0)) && (param_3[3] == 0)) {
        return;
    }
    // Begin building a name string using global buffer DAT_0112e064
    FUN_004086d0(&DAT_0112e064);
    FUN_004408c0(this + 0xf, &DAT_0112e064, 0); // Append this->name?
    // If bit 2 in flags at +0x322 is set, apply zero quaternion/reset rotation
    if (((uint)this[0x322] >> 2 & 1) != 0) {
        local_cc = DAT_0112e040; // Identity quaternion?
        local_c8 = 0;
        local_c4 = 0;
        FUN_00408a00(&local_cc, 0);
    }
    // Get current transform (world matrix? or bone)
    uVar3 = FUN_00471610();
    FUN_0044b4e0(local_50, uVar3);
    uVar3 = (**(code **)(*this + 0x58))(0, this, 0xffffffff, 0); // Get parent or bone index
    piVar4 = (int *)FUN_004df330(&piStack_d0, param_3, local_50, uVar3); // Attach node?
    pNode = this + 0x2de;
    // If a busy node already existed, free it
    if (this[0x2de] != 0) {
        *(undefined4 *)(this[0x2de] + 8) = 0;
        *pNode = 0;
    }
    iVar6 = *piVar4;
    *pNode = iVar6;   // Store the new node pointer at +0x2de
    if (iVar6 != 0) {
        *(int **)(iVar6 + 8) = pNode; // Link back to busynode slot
        *piVar4 = 0;
    }
    if (piStack_d0 != (int *)0x0) {
        piStack_d0[2] = 0; // Clear some associated data
    }
    // Determine calling context: camera or this?
    if (**(int **)(DAT_012233a0 + 4) == 0) {
        piStack_d0 = (int *)0x0;
    }
    else {
        piStack_d0 = (int *)(**(int **)(DAT_012233a0 + 4) + -0x1f30); // Camera offset
    }
    piVar5 = (int *)FUN_0043b870(DAT_01131018); // Get global manager
    piVar4 = this;
    if (piVar5 != (int *)0x0) {
        iVar6 = (**(code **)(*piVar5 + 0x34))(); // GetPlayer?
        if ((*(int *)(iVar6 + 0xc) == 0) ||
           (piVar4 = (int *)(*(int *)(iVar6 + 0xc) + -0x48), piVar4 == (int *)0x0)) {
            piVar4 = this;
        }
    }
    // Override context to camera if param_4 is set and camera exists
    if ((param_4 != '\0') && (piStack_d0 != (int *)0x0)) {
        piVar4 = piStack_d0;
    }
    // If we have a busy node, allocate and attach an "ActionBlend" object
    if (*pNode != 0) {
        puVar7 = (undefined4 *)FUN_004eb390(0x24, 0x10); // Allocate size 0x24
        uVar3 = DAT_00d5ccf8;
        puVar10 = (undefined4 *)0x0;
        if (puVar7 != (undefined4 *)0x0) {
            puVar7[1] = 0;
            *puVar7 = &PTR_FUN_00d61508; // vtable for ActionBlend?
            puVar7[2] = 0;
            puVar7[3] = 0;
            puVar7[4] = 0;
            puVar7[5] = 0;
            puVar7[6] = uVar3;
            puVar10 = puVar7;
        }
        FUN_0070b120(this);        // Init blend for player
        FUN_0070b160(piVar4);      // Apply blend to context (player or camera)
        FUN_004df830(puVar10);     // Attach blend to node
    }
    // Store animation data into local buffer (auStack_a4) using vtable at +0x48
    (**(code **)(*this + 0x48))(auStack_a4);
    // Apply blend parameters: transforms, velocities, and duration
    FUN_0084f270(this, piVar4, auStack_a8, this[0x323], this[0x324], this[0x325], 4, 0);
    // Finalize the blend setup
    FUN_0087aa60();
    // Check distance between two positions (self and something)
    iVar6 = FUN_00471610();
    iVar8 = FUN_00471610();
    fVar12 = *(float *)(iVar8 + 0x30) - *(float *)(iVar6 + 0x30);
    fVar13 = *(float *)(iVar8 + 0x34) - *(float *)(iVar6 + 0x34);
    fVar14 = *(float *)(iVar8 + 0x38) - *(float *)(iVar6 + 0x38);
    if (fVar14 * fVar14 + fVar13 * fVar13 + fVar12 * fVar12 <= DAT_00d62bd0) {
        // Play sound effect (0x1f = footstep? )
        uVar3 = FUN_00799100(0x1f);
        uVar9 = (**(code **)(*(int *)(iStack_d4 + 0x1f30) + 8))(uVar3);
        FUN_00444660(uVar9, uVar3);
    }
    // Check if there is a looping animation (vtable +0xc0 returns duration?)
    fVar11 = (float10)(**(code **)(*this + 0xc0))();
    if (((float10)0 < fVar11) && (cVar2 = (**(code **)(*this + 0x78))(), cVar2 != '\0')) {
        // Execute a hit reaction / knockdown sequence
        FUN_0084dd20();
        iVar6 = (**(code **)(*(int *)this[0x1f0] + 0x34))(); // Get anim state?
        FUN_0044b210(this); // Update positioning?
        FUN_006bf990(iVar6 + 0xc); // Attach to joint?
        iVar8 = FUN_00471610();
        uStack_88 = *(undefined8 *)(iVar8 + 0x30);
        uStack_80 = *(undefined4 *)(iVar8 + 0x38);
        uStack_6c = *(undefined4 *)(iVar6 + 0x30);
        uStack_70 = _DAT_00d76a94; // Some global vector/force
        uStack_64 = 6;
        uStack_5c = DAT_01205224; // Parameter
        FUN_00408bb0(&DAT_0112dd94, this + 0xf, auStack_9c, 0); // Build reaction string
        FUN_0070aaf0(); // Play reaction
    }
    // Notify component at +0x4c about animation event (0x39d41d0f)
    (**(code **)(*(int *)this[0x4c] + 0x48))(0x39d41d0f, 1);
    // Update avatar/vehicle state?
    FUN_0055ba60();
    iVar6 = (**(code **)(*this + 0x1e4))(); // Get current state hash?
    // If param_2 is set and certain conditions hold (no active long animation, not in a forced state)
    if ((((param_2 != '\0') && ((iVar6 == 0 || (iVar6 = FUN_006dc8e0(iVar6, 0x383225a1), iVar6 == 0))))
        && ((iVar6 = FUN_0084daa0(this, 0x383225a1), iVar6 != 0 || (param_4 != '\0')))) &&
        (((uint)this[0x322] >> 0xb & 1) == 0)) {
        // Transition to a new action state
        FUN_00892af0(0);
        FUN_00892be0(this, 1);
        if (param_4 == '\0') {
            uVar3 = 0xd8563e90; // Hash for "idle"?
        }
        else {
            uVar3 = 0x3da31b8c; // Hash for "forced"?
        }
        FUN_00894c40(uVar3, &local_cc); // Set state
        if (aiStack_b8[0] != 0) {
            FUN_004daf90(aiStack_b8);
        }
    }
    // Cleanup: finalize blend, update global timer, free allocated resource pointers
    FUN_0087a9b0();
    this[0x2e2] = DAT_00d764b0; // Store a global timer value
    if (this[0x281] != 0) {
        FUN_004df600(); // Free
    }
    if (this[0x282] != 0) {
        FUN_004df600();
    }
    if (this[0x283] != 0) {
        FUN_004df600();
    }
    if (this[0x2db] != 0) {
        FUN_004df600();
    }
    if (this[0x2dc] != 0) {
        FUN_004df600();
    }
    if (this[0x2dd] != 0) {
        FUN_004df600();
    }
    if (this[0x393] != -1) {
        FUN_0090dff0(this[0x393]); // Release timer ID
        this[0x393] = -1;
    }
    return;
}