// FUNC_NAME: Entity::updateComponents
void __thiscall Entity::updateComponents() {
    // this pointer at param_1 (ecx)
    float local_20, local_1c, local_18, local_14;
    int iVar1;
    float *pfVar3;
    unsigned int uVar2;

    // Pre-update synchronization
    entityPreUpdate();

    // Destroy obsolete components (pointers at +0xFC, +0x104, +0x10C, +0x114)
    if (*(int *)(this + 0xFC) != 0) {
        componentRelease(*(int *)(this + 0xFC));
    }
    if (*(int *)(this + 0x104) != 0) {
        componentRelease(*(int *)(this + 0x104));
    }
    if (*(int *)(this + 0x10C) != 0) {
        componentRelease(*(int *)(this + 0x10C));
    }
    if (*(int *)(this + 0x114) != 0) {
        componentRelease(*(int *)(this + 0x114));
    }

    // Update sound component if present (+0xC0 is component ptr, +0xD0 data)
    if (*(int *)(this + 0xC0) != 0) {
        updateSoundComponent(*(int *)(this + 0x14), *(int *)(this + 0xC0), (float *)(this + 0xD0), 2);
    }

    // Update animation component (+0xA4 ptr, +0xB0 data)
    if (*(int *)(this + 0xA4) != 0) {
        updateAnimationComponent(*(int *)(this + 0x14), *(int *)(this + 0xA4), (float *)(this + 0xB0));
    }

    // Update effect component (+0xF0 ptr, +0xF4 data)
    if (*(int *)(this + 0xF0) != 0) {
        updateEffectComponent(*(int *)(this + 0x14), *(int *)(this + 0xF0), (float *)(this + 0xF4));
    }

    // Collision update if either collision slot occupied (+0x11C, +0x120)
    if ((*(int *)(this + 0x11C) != 0) || (*(int *)(this + 0x120) != 0)) {
        updateCollisionComponent();
    }

    // Additional component (+0x12C = 300 decimal)
    if (*(int *)(this + 300) != 0) {
        updateEffectComponent(*(int *)(this + 0x10), *(int *)(this + 300), (float *)(this + 0x130));
    }

    // Visual/scale component (+0x1E0 and +0x1E4)
    if (*(int *)(this + 0x1E0) != 0) {
        if (*(int *)(this + 0x1E4) == 0) {
            pfVar3 = (float *)&DAT_011f6680;   // global zero/null vector
            uVar2 = *(unsigned int *)(this + 0x10);
        } else {
            uVar2 = *(unsigned int *)(this + 0x10);
            pfVar3 = &local_20;
            local_20 = 0.0f;
            local_1c = 0.0f;
            local_18 = 0.0f;
            local_14 = 0.0f;
        }
        updateAnimationComponent(uVar2, *(int *)(this + 0x1E0), pfVar3);
    }

    // Scale factor update using lookup table
    if ((*(int *)(this + 0x1E4) != 0) && (*(unsigned int *)(this + 0x100) < 0x1000)) {
        iVar1 = *(unsigned int *)(this + 0x100) * 0x38; // element size 0x38
        if (iVar1 != -0x11a0f28) { // sentinel check
            local_20 = DAT_00e2cd54 / (float)(*(unsigned short *)(&DAT_011a0f2a + iVar1));
            local_1c = DAT_00e2cd54 / (float)(*(unsigned short *)(&DAT_011a0f2c + iVar1));
            local_18 = local_20;
            local_14 = local_1c;
            updateAnimationComponent(*(int *)(this + 0x14), *(int *)(this + 0x1E4), &local_20);
        }
    }
}