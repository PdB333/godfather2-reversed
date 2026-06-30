// FUNC_NAME: ensureCachedBuffer
// Address: 0x006F0640
// Role: Caches a single buffer of specified capacity (in units of 4 bytes). Reallocates if needed.

static int* g_cachedBuffer = nullptr;       // +0x112a9d8
static uint g_cachedBufferCapacity = 0;    // +0x112a9dc

// Allocation and deallocation functions (addresses 0x009c8e80, 0x009c8f10)
extern int* allocateMemory(uint size);
extern void freeMemory(int* ptr);

int ensureCachedBuffer(uint desiredCapacity)
{
    if (desiredCapacity < g_cachedBufferCapacity)
        return (int)g_cachedBuffer;

    int* newBuffer = allocateMemory(desiredCapacity * 4); // Each element is 4 bytes
    if (newBuffer != 0)
    {
        if (g_cachedBuffer != 0)
            freeMemory(g_cachedBuffer);
        g_cachedBufferCapacity = desiredCapacity;
        g_cachedBuffer = newBuffer;
    }
    return (int)newBuffer;
}