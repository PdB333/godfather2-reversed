// FUNC_NAME: TargetingManager::updateTargetSelection

bool __fastcall TargetingManager::updateTargetSelection(int *this)
{
    int iVar1;
    float fVar2;
    float *pfVar3;
    int iVar4;
    float10 fVar5;
    float fVar6;
    bool result;
    float timeDelta;
    float vec3 [3];
    int stack_ec;
    float stack_f4;
    float stack_f0;
    int stack_ec2;
    float stack_e8;
    float stack_e4;
    float position [2];
    int **iteratorPtr;
    float threshold;
    float threshold2;
    int iteratorStruct;
    float stack_b4;
    int stack_b0;
    int stack_a4;
    int stack_84;
    int stack_74;
    char buffer [96];

    // Get time delta from vtable (+0x278)
    fVar5 = (float10)(**(code **)(*this + 0x278))();
    timeDelta = (float)fVar5;

    // Get game time or physics time (FUN_00471610 likely returns some global struct)
    iVar1 = FUN_00471610();
    stack_f4 = (float)*(undefined8 *)(iVar1 + 0x30);
    stack_f0 = (float)((ulonglong)*(undefined8 *)(iVar1 + 0x30) >> 0x20);
    stack_f0 += DAT_00d5c454;
    stack_ec = CONCAT44(stack_e8, *(undefined4 *)(iVar1 + 0x38));

    // Get current position (vtable +0x4c)
    (**(code **)(*this + 0x4c))(position);
    if (position[0] < 0.0f) {
        stack_f4 = *(float *)(DAT_01223480 + 0x60) * position[0] + stack_f4;
    }
    stack_e4 = stack_f0;
    stack_ec = CONCAT44(stack_f4 - stack_f0, /* unk */);

    // Some kind of raycast or query function (FUN_00542650)
    FUN_00542650(&stack_f4, &stack_ec, 2, this[0x20c], 0, 0);

    // Initialize iterator structure
    stack_b0 = 0xffffffff;
    stack_a4 = 0xffffffff;
    iteratorPtr = &PTR_FUN_00e32a8c;
    stack_74 = 0;
    stack_b4 = _DAT_00d5780c;
    stack_84 = 0;
    threshold = _DAT_00d5780c;

    // Iterate over something (hash map or list)
    FUN_009e5ed0(buffer, &iteratorPtr);
    result = false;
    if (stack_74 == 0) {
        return false;
    }

    fVar6 = stack_b4 * stack_f4;
    iVar1 = *(char *)(stack_74 + 0x10) + stack_74;
    if (iVar1 == 0) {
LAB_008098d8:
        iVar4 = stack_74;
        fVar2 = -4.999167e+37f; // sentinel value
        if (iVar1 != 0) {
            pfVar3 = (float *)FUN_0054c080(vec3, iVar1);
            goto LAB_008098ef;
        }
    } else {
        FUN_004af8c0(vec3, 0x2001);
        fVar2 = 0.0f;
        if (vec3[0] != 0.0f) {
            fVar2 = vec3[0];
        }
        if (fVar2 == 0.0f) goto LAB_008098d8;
        iVar1 = FUN_004025a0(*(undefined4 *)((int)fVar2 + 0x1c));
        iVar4 = stack_74;
        if (iVar1 == 0) {
            vec3[0] = -4.999167e+37f;
            pfVar3 = vec3;
        } else {
            vec3[0] = *(float *)(iVar1 + 0x2c);
            pfVar3 = vec3;
        }
LAB_008098ef:
        fVar2 = *pfVar3;
    }

    // Compare with current target
    if ((fVar2 == -4.999167e+37f) ||
        ((fVar2 != (float)this[0x720] && (((uint)this[0x6e5] >> 0x19 & 1) == 0)))) {
        if ((_DAT_00d5780c <= fVar6) && (((uint)this[0x6e5] >> 0x11 & 1) == 0)) goto LAB_00809936;
        this[0x720] = (int)fVar2; // Update current target
    }
    result = true;

LAB_00809936:
    iVar1 = FUN_00541470(*(undefined4 *)(iVar4 + 0x1c));
    if ((iVar1 == 1) && (fVar6 < _DAT_00d5780c)) {
        // Call some vtable function (+0x274) — maybe notify about target change?
        (**(code **)(*this + 0x274))();
    }
    return result;
}