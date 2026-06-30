// FUNC_NAME: ChaseCamera::setLookAtTarget
int ChaseCamera::setLookAtTarget(float param_1, code *param_2) {
    uint uVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    int in_EAX; // this pointer
    int iVar5; // target
    code *in_stack_0000001c;

    // +0x10: flags field, clear bit 25 (0x04000000)
    *(uint *)(in_EAX + 0x10) = *(uint *)(in_EAX + 0x10) & 0xfbffffff;
    iVar5 = 0;
    uVar1 = *(uint *)(in_EAX + 0x10);
    
    // Check if param_1 equals a global float constant (DAT_00e2b05c)
    if (param_1 == DAT_00e2b05c) {
        // +0x60: some pointer field indicating a valid target
        if (*(int *)(in_EAX + 0x60) != 0) {
            *(uint *)(in_EAX + 0x10) = uVar1 | 0x800000; // set bit 23
            iVar5 = FUN_00571690(); // allocate or get target object
            // Clear bit 23, set/clear bit 5
            *(uint *)(in_EAX + 0x10) = uVar1 & 0x20 | *(uint *)(in_EAX + 0x10) & 0xff7fffff;
            uVar2 = DAT_00e2b1a4;
            if (iVar5 != 0) {
                // Initialize lookAt target orientation (4x3 matrix or quaternion)
                // +0x80 to +0x9c: two sets of 4 floats (target position and orientation)
                *(undefined4 *)(in_EAX + 0x98) = 0;
                *(undefined4 *)(in_EAX + 0x94) = 0;
                *(undefined4 *)(in_EAX + 0x90) = 0;
                *(undefined4 *)(in_EAX + 0x9c) = uVar2;
                *(undefined4 *)(in_EAX + 0x88) = 0;
                *(undefined4 *)(in_EAX + 0x84) = 0;
                *(undefined4 *)(in_EAX + 0x80) = 0;
                *(undefined4 *)(in_EAX + 0x8c) = uVar2;
                FUN_00571550(iVar5); // release/reference count decrement
            }
        }
        *(uint *)(in_EAX + 0x10) = *(uint *)(in_EAX + 0x10) & 0xfffffff7; // clear bit 3
        return iVar5;
    }
    
    // Regular path: call some function with param_1
    FUN_005715d0(param_1); // lookAt interpolation setup?
    iVar5 = FUN_00571690(); // allocate or get target object
    
    // Check if callback function pointers are provided (in_stack or param_2)
    if ((in_stack_0000001c != (code *)0x0) || (param_2 != (code *)0x0)) {
        if (iVar5 == 0) goto LAB_005719b9;
        if (in_stack_0000001c == (code *)0x0) {
            (*param_2)(iVar5); // regular callback
        } else {
            (*in_stack_0000001c)(&param_2); // callback with reference
        }
    }
    
    if (iVar5 != 0) {
        // Copy 8 floats from target object (+0x10 to +0x2c) to camera's fields
        // +0x80 to +0x9c: two sets of 4 floats (position and rotation)
        uVar2 = *(undefined4 *)(iVar5 + 0x14);
        uVar3 = *(undefined4 *)(iVar5 + 0x18);
        uVar4 = *(undefined4 *)(iVar5 + 0x1c);
        *(undefined4 *)(in_EAX + 0x80) = *(undefined4 *)(iVar5 + 0x10);
        *(undefined4 *)(in_EAX + 0x84) = uVar2;
        *(undefined4 *)(in_EAX + 0x88) = uVar3;
        *(undefined4 *)(in_EAX + 0x8c) = uVar4;
        uVar2 = *(undefined4 *)(iVar5 + 0x24);
        uVar3 = *(undefined4 *)(iVar5 + 0x28);
        uVar4 = *(undefined4 *)(iVar5 + 0x2c);
        *(undefined4 *)(in_EAX + 0x90) = *(undefined4 *)(iVar5 + 0x20);
        *(undefined4 *)(in_EAX + 0x94) = uVar2;
        *(undefined4 *)(in_EAX + 0x98) = uVar3;
        *(undefined4 *)(in_EAX + 0x9c) = uVar4;
        FUN_00571550(iVar5); // release/reference count decrement
        return iVar5;
    }
    
LAB_005719b9:
    FUN_00577a90(); // error handling or fallback
    return iVar5;
}