// FUNC_NAME: Player::Player
void __thiscall Player::Player(void *this) {
    // Set primary vtable pointer at offset 0x00
    *(int *)this = (int)&PTR_FUN_00d60fa8;
    
    // Set interface vtable pointers at various offsets
    *(int *)((char *)this + 0x3C) = (int)&PTR_LAB_00d60f98;   // +0x3C
    *(int *)((char *)this + 0x48) = (int)&PTR_LAB_00d60f94;   // +0x48
    *(int *)((char *)this + 0x50) = (int)&PTR_LAB_00d60f90;   // +0x50
    
    // Initialize sub-object at offset 0x54 (likely a base class or component)
    FUN_004086d0((int *)((char *)this + 0x54));  // Sub-object constructor step 1
    FUN_00408310((int *)((char *)this + 0x54));  // Sub-object constructor step 2
    
    // Override interface vtable at +0x50 after sub-object init
    *(int *)((char *)this + 0x50) = (int)&PTR_LAB_00e32854;   // +0x50 updated
    
    // Global initialization routine
    FUN_0046c640();
}