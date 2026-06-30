// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __fastcall GodfatherGameManager::GodfatherGameManager(unsigned int *thisPtr)
{
    // Set the primary vtable pointer (at offset 0)
    *thisPtr = &_vtable_GodfatherGameManager;   // PTR_FUN_00d5e880

    // Set additional function table pointers at various offsets
    thisPtr[0xf] = (unsigned int)_vtable_BaseClassA;   // PTR_LAB_00d5e870 (+0x3C)
    thisPtr[0x12] = (unsigned int)_vtable_BaseClassB;   // PTR_LAB_00d5e86c (+0x48)
    thisPtr[0x14] = (unsigned int)_vtable_BaseClassC;   // PTR_LAB_00d5e868 (+0x50)
    thisPtr[0x15] = (unsigned int)_vtable_BaseClassD;   // PTR_LAB_00d5e808 (+0x54)
    thisPtr[0x16] = (unsigned int)_vtable_BaseClassE;   // PTR_LAB_00d5e7a0 (+0x58)

    // Initialize sub-object at offset 0x188 (0x62*4)
    // FUN_004086d0 is likely a constructor for a base class component
    FUN_004086d0((unsigned int*)(thisPtr + 0x62));
    FUN_00408310((unsigned int*)(thisPtr + 0x62));

    // Initialize static singleton objects
    FUN_004086d0(&_staticSingletonA);   // DAT_0120e93c
    FUN_004086d0(&_staticSingletonB);   // DAT_0112a628
    FUN_004086d0(&_staticSingletonC);   // DAT_0112a600

    // Call a global initialization routine
    FUN_0046ea20();
}