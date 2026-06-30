// FUNC_NAME: InvokeWithContext
void __cdecl InvokeWithContext(void* param1, void* param2, void* param3, void* param4)
{
    // Temporary context structure passed to internal function
    // +0x00: someGlobal (DAT_00e445dc) - global pointer used as context
    // +0x04: functionTable (PTR_LAB_00dcf974) - pointer to a vtable or function pointer table
    struct Context {
        void* someGlobal;      // +0x00 (offset 0)
        void** functionTable;  // +0x04 (offset 4)
    } context;

    // Initialize context with known global references
    context.someGlobal = (void*)0x00e445dc;           // DAT_00e445dc - likely some shared state
    context.functionTable = (void**)0x00dcf974;       // PTR_LAB_00dcf974 - function pointer table

    // Call internal function with reordered arguments and context pointer
    // FUN_00c09cc0( param2, param1, param3, &context )
    // param4 is ignored (only assigned to local_4 but never used)
    FUN_00c09cc0(param2, param1, param3, &context);
}