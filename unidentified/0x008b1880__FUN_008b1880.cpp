// FUNC_NAME: SomeClass::constructor
undefined4* __thiscall SomeClass(void* this, byte deleteOnFailure)
{
    // Set vtable at offset 0x0 (first virtual function table)
    *(void**)this = &PTR_FUN_00d7ab60;                    // +0x00 vtable
            
    // Set second virtual function table at offset 0x3C
    *(void**)((int)this + 0x3C) = &PTR_LAB_00d7ab50;     // +0x3C vtable2
        
    // Set third virtual function table at offset 0x48
    *(void**)((int)this + 0x48) = &PTR_LAB_00d7ab4c;     // +0x48 vtable3
        
    // Initialize subobject at offset 0x50
    initSubObject1((int)this + 0x50);                    // FUN_004086d0
    initSubObject1_2((int)this + 0x50);                  // FUN_00408310
    initSubObject2((int)this + 0x58);                    // FUN_00408310 (different offset)
    
    // Global initialization routine
    globalInit();                                         // FUN_0046c640
    
    // If the object was allocated via new, free it on failure (though constructor succeeded)
    if ((deleteOnFailure & 1) != 0) {
        operatorDelete(this, 0x60);                      // FUN_0043b960, size 0x60
    }
    return this;
}