// FUNC_NAME: initializeGroupWitnessManager
void initializeGroupWitnessManager(void)
{
    // Initialize global pointer to GroupWitness manager/object
    // FUN_0043c1c0 likely creates or retrieves a singleton for "GroupWitness"
    g_pGroupWitnessManager = (GroupWitnessManager*)FUN_0043c1c0(PTR_s_GroupWitness_00e52464);
    return;
}