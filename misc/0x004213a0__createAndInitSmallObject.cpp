// FUNC_NAME: createAndInitSmallObject
// 0x004213a0 - Allocates a 0x14 (20) byte block and calls an initialization routine. Likely a factory for a small internal object.

// Forward declarations of helper functions
void* heapAllocate(int size);   // FUN_009c8e50
void initSmallObject(void);     // FUN_00420c20

void createAndInitSmallObject(void)
{
    void* mem = heapAllocate(0x14);  // Allocate 20 bytes (e.g., a struct or object)
    if (mem != nullptr)
    {
        initSmallObject();  // Construct or set up the newly allocated memory
    }
}