// FUNC_NAME: CleanupGlobalSingletons
// Function address: 0x00607c30
// Role: Shutdown and delete three global singleton objects by calling their second virtual method (vtable+8, likely cleanup/destructor) and nullifying pointers.

void CleanupGlobalSingletons(void)
{
    // g_pManagerA - first global singleton (e.g., AudioManager)
    if (DAT_01205754 != (int *)0x0) {
        // Call vtable[2] on the object (offset 0x8)
        (**(code **)(*DAT_01205754 + 8))(DAT_01205754);
        DAT_01205754 = (int *)0x0;
    }
    // g_pManagerB - second global singleton (e.g., InputManager)
    if (DAT_01205750 != (int *)0x0) {
        (**(code **)(*DAT_01205750 + 8))(DAT_01205750);
        DAT_01205750 = (int *)0x0;
    }
    // g_pManagerC - third global singleton (e.g., StreamManager)
    if (DAT_012058cc != (int *)0x0) {
        (**(code **)(*DAT_012058cc + 8))(DAT_012058cc);
        DAT_012058cc = (int *)0x0;
    }
}