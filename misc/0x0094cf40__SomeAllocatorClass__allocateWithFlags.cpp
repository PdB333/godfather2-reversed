// FUNC_NAME: SomeAllocatorClass::allocateWithFlags
undefined4 __thiscall SomeAllocatorClass::allocateWithFlags(
    int this,
    undefined4 param_2,
    undefined4 param_3,
    undefined4 param_4,
    undefined4 param_5,
    undefined4 param_6,
    int param_7,    // cat1
    int param_8,    // cat2
    int param_9,    // cat3
    int param_10,   // cat4
    int param_11,   // cat5
    undefined4 param_12,
    undefined4 param_13,
    undefined4 param_14,
    undefined4 param_15)
{
    undefined4 *puVar1;
    undefined4 result;
    undefined4 *puVar3;
    undefined4 uVar4;
    uint flags;
    
    result = FUN_00949ee0(param_6);  // some preparation/allocation call
    flags = 0;
    
    if (param_8 == 1) {
        flags = 8;
    }
    
    if (param_9 == 1) {
        flags |= 0x20;
    } else if (param_9 == 2) {
        flags |= 0x10;
    }
    
    if (param_7 == 1) {
        flags |= 1;
    } else if (param_7 == 2) {
        flags |= 2;
    } else if (param_7 == 3) {
        flags |= 4;
    }
    
    if (param_10 == 1) {
        flags |= 0x40;
    }
    
    if (param_11 == 0) {
        flags |= 0x200;
    } else if (param_11 == 1) {
        flags |= 0x100;
    }
    
    param_6 = result;
    
    if (*(char *)(DAT_0112af90 + 0x48) == '\0') {  // some global flag check
        flags |= 0x80;
        FUN_00408680(&DAT_011301a8);  // some debug/info output
    }
    
    puVar3 = (undefined4 *)FUN_0094ab00(&param_6);  // get buffer pointer
    
    // Check if allocation is allowed
    if ((*(int *)(this + 0x5c) == 0) &&
        ((*(int *)(this + 0x58) == 0 || ((*(byte *)(this + 0x4c) & 1) == 0)))) {
        FUN_004de190();  // some error/fallback handling
    }
    
    puVar1 = *(undefined4 **)(this + 0x5c);  // free list pointer
    if (puVar1 != (undefined4 *)0x0) {
        uVar4 = *puVar1;
        *(int *)(this + 0x38) += 1;  // increment allocation count
        *(int *)(this + 0x34) -= 1;  // decrement free count
        *(undefined4 *)(this + 0x5c) = uVar4;  // update free list
        
        if (puVar1 != (undefined4 *)0x0) {
            uVar4 = FUN_0094c710(result, param_2, param_3, param_4, param_5,
                                 flags, param_12, param_13, param_14, param_15);  // actual allocation
            *puVar3 = uVar4;
            return result;
        }
    }
    
    *puVar3 = 0;  // allocation failed
    return result;
}