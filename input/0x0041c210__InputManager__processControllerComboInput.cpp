// FUNC_NAME: InputManager::processControllerComboInput
void __fastcall InputManager::processControllerComboInput(void* thisPtr, uint32_t param_edx, uint32_t param_stack1, uint32_t param_stack2)
{
    // Global flag enabling combo input processing (DAT_0110b598)
    static bool& s_comboEnabled = *(bool*)0x0110b598;
    // Combo step counter (DAT_0110b59a)
    static uint32_t& s_comboStep = *(uint32_t*)0x0110b59a;
    // Combo parameter slots (DAT_0110b5a4, DAT_0110b5a0, DAT_0110b59c, DAT_0110b5a8, DAT_0110b5ac, DAT_0110b599)
    static uint32_t& s_comboParam1 = *(uint32_t*)0x0110b5a4;
    static uint32_t& s_comboParam2 = *(uint32_t*)0x0110b5a0;
    static uint32_t& s_comboParam3 = *(uint32_t*)0x0110b59c;
    static uint32_t& s_comboParam4 = *(uint32_t*)0x0110b5a8;
    static uint32_t& s_comboParam5 = *(uint32_t*)0x0110b5ac;
    static bool&   s_comboFlag = *(bool*)0x0110b599;

    // Pointer tables for different controller sources
    // These are static arrays of pointers (e.g., controller slot vtables or state objects)
    static void** const s_table1 = (void**)0x0110b490;   // PTR_PTR_0110b490
    static void** const s_table2 = (void**)0x0110b368;   // PTR_PTR_0110b368
    static void** const s_table3 = (void**)0x0110b3a0;   // PTR_PTR_0110b3a0
    static void** const s_table4 = (void**)0x0110b3bc;   // PTR_PTR_0110b3bc

    // in_EAX holds the source table pointer (passed via EAX register)
    void** sourceTable = (void**)thisPtr; // Actually EAX, but reused here

    if (!s_comboEnabled)
        return;

    s_comboStep++;
    if (s_comboStep >= 4)
        goto reset_combo;

    // Determine source and store parameters accordingly
    if (sourceTable == &s_table1) // +0x00 table (e.g., controller slot 0)
    {
        if (s_comboParam1 == 0)
        {
            s_comboParam1 = param_edx;
            return;
        }
    }
    else if (sourceTable == &s_table2) // +0x?? table (e.g., controller slot 1)
    {
        if (s_comboParam2 == 0)
        {
            s_comboParam2 = param_edx;
            return;
        }
        if (s_comboParam3 == 0)
        {
            s_comboParam3 = param_edx;
            return;
        }
    }
    else if ((sourceTable == &s_table3 || sourceTable == &s_table4) && // Additional controller types
             s_comboParam4 == 0 && s_comboParam3 == 0)
    {
        // Store multiple parameters for this combo step
        s_comboParam4 = param_stack1;
        s_comboParam3 = param_edx;
        s_comboParam5 = param_stack2;
        // Flag indicating which table triggered (0 for table3, non-zero for table4)
        s_comboFlag = (sourceTable == &s_table4);
        return;
    }

reset_combo:
    // Combo failed or complete – reset enable flag
    s_comboEnabled = false;
}