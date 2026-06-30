// FUNC_NAME: Entity::checkActionAllowance
uint __thiscall Entity::checkActionAllowance(void* this, void* context) {
    char cVar1;
    undefined4 in_EAX;
    int iVar2;
    uint uVar3;
    byte bVar4;
    undefined4 uVar5;
    undefined4 local_c;

    // Check bit 5 of byte at this+0x8a; if clear, call initialization function
    if ((*(byte*)((uintptr_t)this + 0x8a) & 0x20) == 0) {
        in_EAX = FUN_006e6700(); // Likely initializes some global state
    }
    
    // Compute bVar4 = inverted (byte at this+0x89 >> 4)
    bVar4 = ~(*(byte*)((uintptr_t)this + 0x89) >> 4);
    
    // If bit 0 of bVar4 is clear, return early with combined value
    if ((bVar4 & 1) == 0) {
        return CONCAT31((int3)((uint)in_EAX >> 8), bVar4) & 0xffffff01;
    }
    
    // Read state from context at offset 0x24c4
    uVar3 = *(uint*)((uintptr_t)context + 0x24c4);
    if (uVar3 == 0 || uVar3 == 0x48) {
        goto LAB_006e7552;
    }
    
    // Check first condition
    cVar1 = FUN_007167a0(); // Some condition check
    if (cVar1 == '\0') {
        cVar1 = FUN_007174e0(); // Alternate condition
        local_c = 0;
        if (cVar1 != '\0') {
            goto LAB_006e74dd;
        }
    } else {
LAB_006e74dd:
        local_c = 1;
    }
    
    // Compute parameters for FUN_006e64a0
    iVar2 = FUN_00471610(); // Get something like player index or time
    cVar1 = FUN_00717b00(); // Get boolean flag
    uVar5 = _DAT_00d5780c; // Global variable
    if (*(int*)((uintptr_t)context + 0x21b8) != 0) {
        uVar5 = *(undefined4*)(*(int*)((uintptr_t)context + 0x21b8) + 0x5c);
    }
    
    // Call helper function
    uVar3 = FUN_006e64a0(iVar2 + 0x30, local_c, cVar1 == '\0', uVar5);
    if ((char)uVar3 == '\0') {
        return uVar3;
    }

LAB_006e7552:
    return CONCAT31((int3)(uVar3 >> 8), bVar4) & 0xffffff01;
}