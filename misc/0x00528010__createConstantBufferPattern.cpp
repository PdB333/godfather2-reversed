// FUNC_NAME: createConstantBufferPattern

extern float g_constantA;  // DAT_00e2eff4
extern float g_constantB;  // DAT_00e2b1a4

// Custom memory allocator (pool ID 0xd, element size 4, alignment 0, flags 1, unknown)
void* allocateFromPool(int poolId, int elementSize, int alignment, int flags, int unknown);

// Registers the allocated buffer (e.g., submits to a constant manager)
void registerBuffer(void* buffer);

void createConstantBufferPattern(void)
{
    void* buffer = allocateFromPool(0xd, 4, 0, 1, 0);
    float constantA = g_constantA;
    float constantB = g_constantB;

    if (buffer != nullptr)
    {
        float* pBuffer = (float*)buffer;
        pBuffer[0] = constantA;  // index 0
        pBuffer[1] = constantA;  // index 1
        pBuffer[2] = constantB;  // index 2
        pBuffer[3] = constantA;  // index 3
        pBuffer[4] = constantB;  // index 4
        pBuffer[5] = constantB;  // index 5
        pBuffer[6] = constantA;  // index 6
        pBuffer[7] = constantB;  // index 7

        registerBuffer(buffer);
    }
}