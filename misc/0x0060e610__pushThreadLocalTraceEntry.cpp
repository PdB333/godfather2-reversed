// FUNC_NAME: pushThreadLocalTraceEntry

// Global variables (based on addresses)
static uint32_t* g_stackBase0 = (uint32_t*)0x01206880;   // base for thread0 stack
static uint32_t* g_stackBase1 = (uint32_t*)0x012068e8;   // base for thread1 stack
static uint32_t g_traceBuffer[2] = {0};                  // at 0x00f15a4c, indexed by (tlsValue == 0)

void pushThreadLocalTraceEntry(uint32_t value)
{
    // Retrieve thread-local storage value (TLS slot at FS:[0x2C] + 0x34)
    int tlsValue = *(int*)(**(int**)(__readfsdword(0x2C) + 0x34));

    // Store value in a small buffer; index is 0 if tlsValue == 0, else 1
    g_traceBuffer[tlsValue == 0] = value;

    // Select appropriate stack base depending on tlsValue
    uint32_t* basePtr = g_stackBase0;
    if (tlsValue != 0) {
        basePtr = g_stackBase1;
    }

    // Get the stack pointer (offset +0x14 in the base structure)
    uint32_t** stackPtr = (uint32_t**)(basePtr + 0x14);

    // Push the label pointer (PTR_LAB_01127524) onto the stack
    *(*stackPtr)++ = (uint32_t)&PTR_LAB_01127524;

    // Push the value onto the stack
    *(*stackPtr)++ = value;
}