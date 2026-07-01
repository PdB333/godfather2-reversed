// FUNC_NAME: SceneNode::initializeNodeTransform
void __fastcall SceneNode::initializeNodeTransform(int this)
{
    // Structure offsets (relative to this):
    // +0x50: pParentNode (pointer to parent scene node)
    // +0x58: pVtableOrInterface (pointer to vtable)
    // +0x5c: localPositionX (float)
    // +0x60: localPositionY (float)
    // +0x64: localPositionAltX (float, used when bit7 of flags is set)
    // +0x68: localPositionAltY (float)
    // +0x70: flags (bit0-31, bit2 set at end, bit7 used for alternative position)
    // +0x80-0xBC: localTransform (4x4 matrix, 16 floats)
    // +0xC0-0xFC: worldTransform (4x4 matrix)
    // Beyond 0xFC: other fields (e.g., at 0x100? Not shown)

    undefined4 uVar1;
    char cVar2;
    int iVar3;
    int* piVar4;
    float fVar5;
    double dVar6;
    char* pcStack_104;
    float fStack_f4;
    float fStack_f0;
    float fStack_ec;
    float fStack_e8;
    float local_e4[3];
    undefined1 auStack_d8[8];
    undefined4 uStack_d0;
    undefined4 uStack_cc;
    undefined1 auStack_c8[8];
    undefined1 auStack_c0[8];
    undefined1 auStack_b8[8];
    undefined4 local_b0;
    undefined4 local_ac;
    undefined4 local_a8[2];
    undefined1 auStack_a0[56];
    undefined1 auStack_68[8];
    undefined1 auStack_60[92];

    local_b0 = 0;
    local_ac = _DAT_00d5780c;  // Identity constant (likely 1.0f or 0)
    local_a8[0] = 0;
    local_e4[0] = 0.0f;
    pcStack_104 = "m_root";

    // Call virtual function at vtable+0x94 - likely getRootTransform or attach to root
    (*(code**)(*(int**)(this + 0x58) + 0x94))(local_e4);

    uStack_d0 = 0;
    uStack_cc = 0;

    // Decide which position fields to use based on flag bit7
    if ((*(uint*)(this + 0x70) >> 7 & 1) == 0) {
        fStack_f4 = *(float*)(this + 0x5c);
        fStack_f0 = *(float*)(this + 0x60);
    } else {
        fStack_f4 = *(float*)(this + 100);      // +0x64
        fStack_f0 = *(float*)(this + 0x68);
    }

    // Obtain base class pointer (offset -0x48 from parent's this)
    if (*(int*)(this + 0x50) == 0) {
        piVar4 = (int*)0x0;
    } else {
        piVar4 = (int*)(*(int*)(this + 0x50) + -0x48);
    }
    // Call virtual function at vtable+0x1ec on base - likely updateSomeTransform
    (*(code**)(*piVar4 + 0x1ec))(&fStack_f4, &uStack_d0);

    // Copy data? (function at 0x45f8d0)
    FUN_0045f8d0(auStack_60, &stack0xffffff08, 1);

    // Get some global time/engine data
    iVar3 = FUN_00471610();
    dVar6 = (double)*(float*)(iVar3 + 0x20);

    // Get a function pointer or state
    FUN_00b9a9fa();

    // Check if this node is the root
    cVar2 = FUN_008754b0(&stack0xffffff04);
    if (cVar2 == '\0') {
        fVar5 = (float)dVar6 + DAT_00d5f00c;   // Some offset
    } else {
        fVar5 = (float)dVar6 - DAT_00d5f00c;
    }

    // Compute something with the float and arrays
    FUN_0056c040(fVar5, auStack_c0, auStack_a0);

    // Initialize worldTransform matrix (at +0xC0) to identity-like pattern
    uVar1 = _DAT_00d5780c;
    *(undefined4*)(this + 200) = 0;           // +0xC8
    *(undefined4*)(this + 0xc4) = 0;
    *(undefined4*)(this + 0xc0) = 0;
    *(undefined4*)(this + 0xcc) = uVar1;       // +0xCC
    *(undefined4*)(this + 0xd8) = 0;
    *(undefined4*)(this + 0xd4) = 0;
    *(undefined4*)(this + 0xd0) = 0;
    *(undefined4*)(this + 0xdc) = uVar1;       // +0xDC
    *(undefined4*)(this + 0xe8) = 0;
    *(undefined4*)(this + 0xe4) = 0;
    *(undefined4*)(this + 0xe0) = 0;
    *(undefined4*)(this + 0xec) = uVar1;       // +0xEC
    *(undefined4*)(this + 0xf8) = 0;
    *(undefined4*)(this + 0xf4) = 0;
    *(undefined4*)(this + 0xf0) = 0;
    *(undefined4*)(this + 0xfc) = uVar1;       // +0xFC

    // Get base pointer again
    if (*(int*)(this + 0x50) == 0) {
        piVar4 = (int*)0x0;
    } else {
        piVar4 = (int*)(*(int*)(this + 0x50) + -0x48);
    }
    // Call virtual function at vtable+0xa4 on base
    (*(code**)(*piVar4 + 0xa4))(&fStack_f0, &stack0xffffff08);

    // Compute delta of positions
    fStack_e8 = fStack_f4;
    local_e4[0] = fStack_f0;
    fStack_ec = unaff_EBX;   // uninitialized? Actually unaff_EBX is likely a register that was not set.
    FUN_00884f30(&fStack_ec);
    *(float*)(this + 0xf0) = fStack_ec - unaff_EBX;
    *(float*)(this + 0xf4) = fStack_e8 - fStack_f4;
    *(float*)(this + 0xf8) = local_e4[0] - fStack_f0;

    // Call some transform composition functions
    FUN_00885c50(this + 0xc0, auStack_c8, &pcStack_104);
    FUN_0056d530(local_a8, auStack_b8);
    FUN_0056d530(auStack_68, auStack_d8);
    FUN_0056ce40(auStack_d8, auStack_d8);
    FUN_0056cba0(auStack_d8, auStack_b8, (undefined4*)(this + 0xe0));
    FUN_0056ce80(auStack_d8, this + 0xf0, this + 0xf0);

    // Initialize localTransform matrix (at +0x80) to identity
    uVar1 = _DAT_00d5780c;
    *(undefined4*)(this + 0x80) = _DAT_00d5780c;
    *(undefined4*)(this + 0x84) = 0;
    *(undefined4*)(this + 0x88) = 0;
    *(undefined4*)(this + 0x8c) = 0;
    *(undefined4*)(this + 0x90) = 0;
    *(undefined4*)(this + 0x94) = uVar1;
    *(undefined4*)(this + 0x98) = 0;
    *(undefined4*)(this + 0x9c) = 0;
    *(undefined4*)(this + 0xa0) = 0;
    *(undefined4*)(this + 0xa4) = 0;
    *(undefined4*)(this + 0xa8) = uVar1;
    *(undefined4*)(this + 0xac) = 0;
    *(undefined4*)(this + 0xb0) = 0;
    *(undefined4*)(this + 0xb4) = 0;
    *(undefined4*)(this + 0xb8) = 0;
    *(undefined4*)(this + 0xbc) = uVar1;

    // Get base pointer again
    if (*(int*)(this + 0x50) == 0) {
        iVar3 = 0;
    } else {
        iVar3 = *(int*)(this + 0x50) + -0x48;
    }
    // Call virtual function at vtable+0x80 on base - likely setLocalTransform
    (*(code**)(*(int**)(this + 0x58) + 0x80))(iVar3, &stack0xffffff00, &stack0xffffff04, 0, this + 0x80);

    // Mark node as initialized (bit2 set)
    *(uint*)(this + 0x70) = *(uint*)(this + 0x70) | 4;
    return;
}