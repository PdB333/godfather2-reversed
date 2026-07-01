// FUNC_NAME: GodfatherGameManager::initializeSubsystems
void __thiscall GodfatherGameManager::initializeSubsystems(void *this)
{
    int *piVar1;
    
    // Initialize three sub-objects at offsets 0x6cc, 0x6d0, 0x71c
    piVar1 = (int *)((char *)this + 0x6cc); // +0x6cc: some object (e.g., CryHash or Array)
    FUN_005c3960(piVar1);
    FUN_005c3c70(piVar1);
    piVar1 = (int *)((char *)this + 0x6d0); // +0x6d0: another similar object
    FUN_005c3960(piVar1);
    FUN_005c3c70(piVar1);
    piVar1 = (int *)((char *)this + 0x71c); // +0x71c: third object
    FUN_005c3960(piVar1);
    FUN_005c3c70(piVar1);
    
    // Call vtable function at offset 0x68 on sub-object at index 0x675
    (*(void (__thiscall **)(void *))(*((int *)this + 0x675) + 0x68))((void *)*((int *)this + 0x675));
    
    // Call function FUN_005c1820 multiple times (likely memory or debug)
    FUN_005c1820();
    FUN_005c1820();
    
    // More vtable calls at +0x68 for various subsystems
    (*(void (__thiscall **)(void *))(*((int *)this + 0x624) + 0x68))((void *)*((int *)this + 0x624));
    (*(void (__thiscall **)(void *))(*((int *)this + 0x60a) + 0x68))((void *)*((int *)this + 0x60a));
    
    // Many repeated FUN_005c1820 calls
    FUN_005c1820();
    FUN_005c1820();
    FUN_005c1820();
    FUN_005c1820();
    FUN_005c1820();
    FUN_005c1820();
    FUN_005c1820();
    
    // Direct init calls for various subsystems
    FUN_009911f0(); // e.g., AudioSystem::init
    FUN_00991e10();
    FUN_00929d70();
    
    // Vtable calls at +0xa8 for some subsystems
    (*(void (__thiscall **)(void *))(*((int *)this + 0x3cc) + 0xa8))((void *)*((int *)this + 0x3cc));
    (*(void (__thiscall **)(void *))(*((int *)this + 0x3fe) + 0xa8))((void *)*((int *)this + 0x3fe));
    
    // More vtable calls at +0x68
    (*(void (__thiscall **)(void *))(*((int *)this + 0x3b0) + 0x68))((void *)*((int *)this + 0x3b0));
    FUN_00983600();
    (*(void (__thiscall **)(void *))(*((int *)this + 0x39b) + 0x68))((void *)*((int *)this + 0x39b));
    (*(void (__thiscall **)(void *))(*((int *)this + 0x32c) + 0xa8))((void *)*((int *)this + 0x32c));
    (*(void (__thiscall **)(void *))(*((int *)this + 0x16d) + 0xa8))((void *)*((int *)this + 0x16d));
    (*(void (__thiscall **)(void *))(*((int *)this + 0x26d) + 0x68))((void *)*((int *)this + 0x26d));
    (*(void (__thiscall **)(void *))(*((int *)this + 0x1bb) + 0x68))((void *)*((int *)this + 0x1bb));
    FUN_005c1820();
    (*(void (__thiscall **)(void *))(*((int *)this + 0xc3) + 0x68))((void *)*((int *)this + 0xc3));
    (*(void (__thiscall **)(void *))(*((int *)this + 0xe0) + 0x68))((void *)*((int *)this + 0xe0));
    (*(void (__thiscall **)(void *))(*((int *)this + 0x521) + 0x68))((void *)*((int *)this + 0x521));
    (*(void (__thiscall **)(void *))(*((int *)this + 0x4dd) + 0x68))((void *)*((int *)this + 0x4dd));
    (*(void (__thiscall **)(void *))(*((int *)this + 0xa3) + 0x68))((void *)*((int *)this + 0xa3));
    (*(void (__thiscall **)(void *))(*((int *)this + 0x60) + 0x68))((void *)*((int *)this + 0x60));
    // Call vtable at +0x68 from the first vtable pointer (this[0])
    (*(void (__thiscall **)(void *))(*((int *)this) + 0x68))(this);
    
    // Sequence of direct init calls
    FUN_0094b070();
    FUN_0094f6b0();
    FUN_0093de40();
    FUN_00993fa0();
    FUN_0097dd40();
    FUN_00953360();
    FUN_00938ba0();
    FUN_00949b90();
    FUN_0094f030();
    FUN_0093fa30();
    FUN_0090dda0();
    FUN_00922de0();
    FUN_00973fe0();
    
    // Set up vtable pointers for first subsystem group (offset 0x660, 0x664, 0x673)
    *((int *)this + 0x660) = (int)&PTR_FUN_00d85f70; // +0x660: vtable pointer for first subsystem
    *((int *)this + 0x664) = (int)&PTR_LAB_00d85f4c; // +0x664: data pointer
    // Note: original code sets +0x673 twice, likely a bug in decompiler or intentional overwrite.
    // We keep the last write.
    *((int *)this + 0x673) = (int)&PTR_LAB_00d85f48; // +0x673: data pointer for first subsystem
    *((int *)this + 0x673) = (int)&PTR_LAB_00d85d80; // overwrites above
    DAT_0113005c = 0; // global flag
    FUN_005c16e0(); // likely debug or memory
    
    // More direct init
    FUN_0090fbf0();
    FUN_009833f0();
    FUN_00938710();
    
    // Set up vtable pointers for second subsystem group (offset 0x5f2, 0x5f6, 0x605)
    *((int *)this + 0x5f2) = (int)&PTR_FUN_00d85db8;
    *((int *)this + 0x5f6) = (int)&PTR_LAB_00d85d90;
    *((int *)this + 0x605) = (int)&PTR_LAB_00d85d8c;
    *((int *)this + 0x605) = (int)&PTR_LAB_00d85d74;
    DAT_0112a9d0 = 0; // another global flag
    FUN_005c16e0();
    
    // More init
    FUN_0094fae0();
    FUN_00915f40();
    FUN_009130c0();
    FUN_00956cc0();
    FUN_0092dce0();
    FUN_009622a0();
    FUN_0094e380();
    FUN_0092a830();
    FUN_00990920();
    FUN_00992480();
    FUN_00929ea0();
    FUN_009513e0();
    FUN_0095acd0();
    FUN_009377a0();
    
    // Set up vtable pointers for third subsystem group (offset 0x39b, 0x39f, 0x3ae)
    *((int *)this + 0x39b) = (int)&PTR_FUN_00d85e48;
    *((int *)this + 0x39f) = (int)&PTR_LAB_00d85e24;
    *((int *)this + 0x3ae) = (int)&PTR_LAB_00d85e20;
    *((int *)this + 0x3ae) = (int)&PTR_LAB_00d85d78;
    DAT_0112fc8c = 0;
    FUN_005c16e0();
    
    // Final batch of init
    FUN_0091f820();
    FUN_00920fb0();
    FUN_00911190();
    FUN_00959020();
    FUN_0097f0a0();
    
    // Fourth subsystem group (offset 0x154, 0x158, 0x167)
    *((int *)this + 0x154) = (int)&PTR_FUN_00d85ee0;
    *((int *)this + 0x158) = (int)&PTR_LAB_00d85eb8;
    *((int *)this + 0x167) = (int)&PTR_LAB_00d85eb4;
    *((int *)this + 0x167) = (int)&PTR_LAB_00d85d7c;
    DAT_0112a9cc = 0;
    FUN_005c16e0();
    
    // More init
    FUN_009776b0();
    FUN_00985830();
    FUN_00928770();
    FUN_00943710();
    FUN_0093bd90();
    return;
}