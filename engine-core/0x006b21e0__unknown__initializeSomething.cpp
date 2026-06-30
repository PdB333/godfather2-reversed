// FUNC_NAME: unknown::initializeSomething
void initializeSomething(void)
{
    // Stack variables for initialization
    void **local_14[2];          // Array of pointers
    int local_c;                 // Some integer value
    void *local_8;               // Pointer to local_14
    char local_4;                // Flag or counter
    
    local_8 = (void *)local_14;  // Point to the array
    local_14[0] = &PTR_LAB_00d5dbb0;  // Reference to some global data (+0x00d5dbb0)
    local_c = DAT_0112a5a4;      // Load global value from +0x0112a5a4
    local_4 = 0;                 // Initialize flag to 0
    
    // Call initialization function with reference to local_c and 0
    FUN_00408a00(&local_c, 0);
    
    return;
}