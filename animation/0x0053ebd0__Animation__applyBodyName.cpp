// FUNC_NAME: Animation::applyBodyName

void Animation::applyBodyName(int this) // param_1 is 'this' pointer
{
    char cVar1;
    char *pcVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    int local_34;
    int local_30;
    undefined4 local_2c;
    undefined4 local_28;
    undefined4 local_24;
    undefined4 local_20;
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;

    iVar4 = this + 0x10; // +0x10: base pointer for blending or slot
    if (*(char *)(this + 0x28) == '\x01') { // +0x28: blend mode indicator (1 = additive? or override 1)
        iVar3 = *(char *)(this + 0x20) + iVar4; // +0x20: slot index for first override
    }
    else {
        iVar3 = 0;
    }
    if (*(char *)(this + 0x28) == '\x02') {
        local_34 = *(char *)(this + 0x20) + iVar4; // +0x20: slot index for second override
    }
    else {
        local_34 = 0;
    }

    // Attempt to allocate or open a resource (0x2001 and 0x2000 are resource IDs)
    if ((iVar4 != 0) && (*(char *)(this + 0x20) + iVar4 != 0)) {
        FUN_004af8c0(&local_30, 0x2001); // likely allocator for body model data
        iVar5 = 0;
        if (local_30 != 0) {
            iVar5 = local_30;
        }
        if (iVar5 != 0) goto LAB_0053ec62;
    }
    iVar5 = 0;
    if ((iVar4 != 0) && (*(char *)(this + 0x20) + iVar4 != 0)) {
        FUN_004af8c0(&local_30, 0x2000); // alternative resource ID
        iVar5 = 0;
        if (local_30 != 0) {
            iVar5 = local_30;
        }
    }

LAB_0053ec62:
    // Determine source of body transformation data
    if (iVar3 == 0) {
        if (local_34 == 0) {
            local_34 = this;
        }
        iVar4 = *(int *)(local_34 + 0x18); // +0x18: offset to bone/animation matrix
        local_30 = *(int *)(iVar4 + 0x30);
        local_2c = *(undefined4 *)(iVar4 + 0x34);
        local_28 = *(undefined4 *)(iVar4 + 0x38);
        local_24 = *(undefined4 *)(iVar4 + 0x3c);
    }
    else {
        local_30 = *(int *)(iVar3 + 0x110);
        local_2c = *(undefined4 *)(iVar3 + 0x114);
        local_28 = *(undefined4 *)(iVar3 + 0x118);
        local_24 = *(undefined4 *)(iVar3 + 0x11c);
    }

    if (iVar5 == 0) {
        // Fallback: use placeholder transformation (magic constants)
        local_20 = 0xbadbadba;
        local_1c = 0xbeefbeef;
        local_18 = 0xeac15a55;
        local_14 = 0x91100911;

        if ((*(char *)(DAT_01223480 + 0x28) != '\0') &&
            (iVar4 = FUN_00ab5130(&DAT_00e2d728), iVar4 != -2)) {
            _DAT_0103b270 = 0;
        }

        pcVar2 = *(char **)(this + 0x70); // +0x70: body name string
        if (pcVar2 == (char *)0x0) {
            pcVar2 = "nullBodyName";
        }
        FUN_00540430(DAT_01223480, &local_30, pcVar2); // Apply body name to global manager

        if (*(char *)(DAT_01223480 + 0x28) != '\0') {
            FUN_00ab51e0(1);
            _DAT_0103b274 = 0;
        }
    }
    else {
        // Use virtual dispatch on the allocated resource
        (**(code **)(*(int *)(iVar5 + 0x3c) + 8))(); // vtable call (second slot)

        if ((DAT_012067c4 != 0) && (cVar1 = FUN_00402080(&DAT_012067c4), cVar1 == '\0')) {
            _DAT_012067c8 = _DAT_012067c8 + 1;
            FUN_004084d0(&DAT_012067c4, 0x8000);
            return;
        }
    }
    return;
}