// FUNC_NAME: ResourceManager::shutdown
void __thiscall ResourceManager::shutdown(void *this)
{
    // First, set vtable to base class (PTR_FUN_00e30b64)
    *(int *)this = (int)&PTR_FUN_00e30b64;
    // Set vtable entries at offsets +0x0C and +0x10
    *(int *)((int)this + 0x0C) = (int)&PTR_LAB_00e30b74;
    *(int *)((int)this + 0x10) = (int)&PTR_LAB_00e30b78;

    // Call some static cleanup functions (likely reference count decrement or deletion)
    FUN_004086d0(&DAT_012067b4);
    FUN_004086d0(&DAT_01206778);

    // Release the first internal object (if non-null)
    if (g_pResourceList1 != (int *)0x0)
    {
        FUN_009c8f10(*g_pResourceList1);   // Dereference and call virtual destructor?
        FUN_009c8eb0(g_pResourceList1);    // Free memory
    }
    // Release the second internal object (if non-null)
    if (g_pResourceList2 != (int *)0x0)
    {
        FUN_009c8f10(*g_pResourceList2);
        FUN_009c8eb0(g_pResourceList2);
    }

    // Clear a field in the global game instance (offset 0x94) – likely a pointer or flag
    *(int *)(DAT_012234a8 + 0x94) = 0;
    g_pResourceList1 = (int *)0x0;

    // Change vtable to "cleanup" version
    *(int *)((int)this + 0x10) = (int)&PTR_LAB_00e30b50;
    *(int *)((int)this + 0x0C) = (int)&PTR_LAB_00e30b8c;

    g_pResourceList2 = (int *)0x0;
    g_bSomeShutdownFlag = 0;               // Global flag indicating shutdown done

    // Final cleanup call (e.g. deallocate singletons, close handles)
    FUN_004083d0();
}