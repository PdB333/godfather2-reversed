// FUNC_NAME: createSomeObject
// Function address: 0x00662440
// Role: Allocates and initializes a 0x20-byte structure (likely a node or small object).
// If initialization fails, frees memory and returns NULL.

void* createSomeObject(void)
{
    void* memory = malloc(0x20);
    if (memory != nullptr) {
        int initResult = FUN_00667820(memory, (char*)memory + 0x10, 0);
        if (initResult == 0) {
            return memory;
        }
        free(memory);
    }
    return nullptr;
}