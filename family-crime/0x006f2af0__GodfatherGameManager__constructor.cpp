// FUNC_NAME: GodfatherGameManager::constructor
// Address: 0x006f2af0
// Role: Constructor for the main game manager singleton. Initializes vtable, allocator, and calls internal allocation routine.

undefined4 * __thiscall GodfatherGameManager::constructor(undefined4 *this)
{
    int *allocator;
    undefined4 allocateResult;
    undefined4 local_arguments[3]; // zeroed output buffer for allocate call

    g_pGameManager = this;             // +0x0 global singleton pointer
    *this = &vtable_GodfatherGameManager; // PTR_FUN_00d605d8
    local_arguments[0] = 0;
    local_arguments[1] = 0;
    local_arguments[2] = 0;

    allocator = (int *)createAllocator();   // FUN_004dddd0 – creates memory allocator instance
    allocateResult = allocateFromAllocator(local_arguments, allocator); // FUN_004265d0 – allocate memory, returns handle
    this[4] = allocateResult;               // +0x10 handle or pointer
    this[5] = allocator;                    // +0x14 allocator pointer

    // Call virtual function at index 2 on allocator (likely initialize or register)
    ((code **)(*allocator + 8))();           // (**(code **)(*allocator + 8))()

    this[2] = 0; // +0x08
    this[1] = 0; // +0x04
    this[3] = 0; // +0x0C
    return this;
}