// FUNC_NAME: createAndInitObject
void* createAndInitObject(void)
{
    void* memory = malloc(0x20); // Allocate 32 bytes for object
    if (memory != nullptr) {
        // Initialize sub-object at offset 0x10, with flag 0
        int result = initSubObject(memory, (int)memory + 0x10, 0);
        if (result == 0) {
            return memory; // Success
        }
        free(memory); // Initialization failed, free memory
    }
    return nullptr;
}