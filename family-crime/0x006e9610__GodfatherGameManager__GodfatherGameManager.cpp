// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
GodfatherGameManager * __thiscall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager *this, int arg0, void *arg1)
{
    // Local struct for initialization (three ints)
    int localStruct[3] = { 0, 0, 0 };

    // Global singleton pointer (DAT_011298cc)
    g_pGodfatherGameManager = this;

    // Field initialization (temporary vtable assignment at +0x04 overwritten later)
    this->field04 = (void *)0x00e2f19c;   // +0x04  PTR_FUN_00e2f19c
    this->field08 = 1;                    // +0x08
    this->field0C = 0;                    // +0x0C
    this->field10 = 0;                    // +0x10
    this->field14 = arg1;                 // +0x14  stores the screen/controller object

    // Set vtable pointers (multiple inheritance)
    *(int *)this = (int)&PTR_FUN_00d5fd04;       // +0x00  primary vtable
    *(int *)((int)this + 4) = (int)&PTR_LAB_00d5fcf4; // +0x04  secondary vtable (overwrites previous)

    // Call initialization function with arg0, arg1, and pointer to local struct
    FUN_006e9060(arg0, arg1, localStruct);

    // Call virtual function at offset 8 (vtable index 2) on the object pointed to by arg1
    // Typically an Init() or Start() method
    (*(void (__thiscall **)(void))(*(int *)arg1 + 8))(arg1);

    return this;
}