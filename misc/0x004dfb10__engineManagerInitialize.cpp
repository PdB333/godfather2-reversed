// FUNC_NAME: engineManagerInitialize
void engineManagerInitialize(void* manager, int param2)
{
    // Store the manager pointer globally (singleton pattern)
    DAT_01194538 = manager;
    
    // Call virtual function at vtable offset +8 (likely initializes subsystems)
    // The vtable pointer is at the start of the manager object.
    (*(void (**)(void))(*(int*)manager + 8))();
    
    // Secondary initialization step (e.g., loads configuration or starts services)
    FUN_004df980(param2);
}