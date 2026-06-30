// FUNC_NAME: initializeGlobalInstance
// Function at 0x0044be20: Initialization wrapper that prepares a global pointer and flag, then delegates to a generic initialization routine.

// Forward declaration of the external initialization function (address 0x004a4bd0)
void genericInit(void* initBlock);

// The global pointer variable that this function targets (originally PTR_LAB_00e31594)
extern void* g_globalInstancePtr;

// Structure describing the initialization block passed to genericInit
struct GlobalInitBlock {
    void** ppTarget;  // pointer to the global pointer that should be set/initialized
    uint8_t flag;     // flag value (1 = enable/initialize)
};

void initializeGlobalInstance(void)
{
    GlobalInitBlock initBlock;

    initBlock.ppTarget = &g_globalInstancePtr; // assign the address of the global pointer
    initBlock.flag = 1;                         // set the initialization flag

    // Call the generic initialization routine with a pointer to the block
    genericInit(&initBlock);

    return;
}