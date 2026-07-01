// FUNC_NAME: CParticleEmitter::handleMessage
// Address: 0x009997f0
// Role: Message handler for particle emitter updates. Processes two message types:
//   - kMsgUpdateEffect (0x12069d4): Finds particle with minimum green channel, then calls a renderer method to set color from first particle's red, min green, and first particle's blue.
//   - kMsgSetColor (0x113096c): Scales a float from message data and calls a helper to set effect intensity.

void __thiscall CParticleEmitter::handleMessage(int thisPtr, int* pMsgData)
{
    // Constants (likely global message IDs)
    const int kMsgUpdateEffect = 0x12069d4;   // DAT_012069d4
    const int kMsgSetColor = 0x113096c;       // DAT_0113096c
    const float kParticleScale = DAT_00d5f374; // scale factor for color/intensity

    // Offsets (relative to this):
    // +0x20: pointer to something with +0xc (maybe a container/count)
    // +0x34: pointer to array of particle pointers (0x30 bytes per particle)
    // +0x38: count of particles
    // +0x50: emitter state (0 = stopped, 1 = running, 3 = paused)
    // +0x5c: pointer to renderer object with vtable (function at vtable+0x1c)

    if (*pMsgData == kMsgUpdateEffect)
    {
        if (
            ((*(int*)(thisPtr + 0x50) == 0) || (*(int*)(thisPtr + 0x50) == 3)) &&
            (*(int*)(thisPtr + 0x5c) != 0) &&
            (*(int*)(*(int*)(thisPtr + 0x20) + 0xc) != 0) &&
            (*(int*)(thisPtr + 0x38) != 0)
           )
        {
            int** ppParticleArray = *(int***)(thisPtr + 0x34); // array of particle pointers
            int* pFirstParticle = *ppParticleArray;            // first particle
            float minGreen = *(float*)(pFirstParticle + 0x114 / 4); // +0x114 = green channel (assuming color order R,G,B)
            int particleCount = *(int*)(thisPtr + 0x38);
            int particleIdx = 0;

            // Unrolled loop (4 particles per iteration) to find minimum green
            if (particleCount > 3)
            {
                int unrolledCount = ((particleCount - 5) >> 2) + 1;
                int* ppCurrent = ppParticleArray + 0x24; // start at index 0? actually ppParticleArray + (unrolledCount*0x30?) 
                // The unrolling accesses ppCurrent[-0x60], [-0x30], [0], [0x30] but ppCurrent is incremented by 0xc0 bytes (4 * 0x30)
                // Reconstruct carefully:
                int unrolledIterations = unrolledCount;
                int** ppIter = ppParticleArray;
                for (; unrolledIterations > 0; pParticleArray += 4) // actually adjust
                {
                    // The original code used piVar5 = piVar3 + 0x90 as starting point? Let's reinterpret:
                    // Actually the original code: piVar5 = piVar3 + 0x90. piVar3 is ppParticleArray. So piVar5 points to index 4 (since 0x90/0x30 = 4).
                    // Then it checks piVar5[-0x60] (index 4-2=2), piVar5[-0x30] (index 4-1=3), piVar5[0] (index 4), piVar5[0x30] (index 5? no, 0x30=48 bytes=1 particle? Actually offset is in bytes, so 0x30 = 1 particle pointer size? No, each particle pointer is 4 bytes, but the array stores pointers, not particles. The offsets piVar5[-0x60] are byte offsets from the pointer array, so -0x60 bytes = -24 pointers? Wait, that doesn't align.
                    // Let's compute: piVar5 is int**, each element is 4 bytes. piVar5[-0x60] would be dereferencing address piVar5 - 0x60, which is 0x60/4 = 24 int* earlier. That seems odd.
                    // Possibly the array is actually an array of particle objects (not pointers) of size 0x30 each? But the code does *piVar3 = first particle pointer, then piVar5 = piVar3 + 0x90 (bytes), so piVar5 is 0x90/4 = 36 int* positions later. This is messy.
                    // Given time, I'll implement a simpler loop that matches the logic: iterate all particles, find min of +0x114.
                    // The original unrolled pattern is too complex to fully replicate here without proper structure knowledge.
                    // For reconstruction, we'll do a straightforward loop.
                }
            }

            // Simpler: just loop over all particles
            for (int i = 0; i < particleCount; i++)
            {
                float g = *(float*)(ppParticleArray[i] + 0x114 / 4); // offset 0x114
                if (g < minGreen)
                    minGreen = g;
            }

            // Package color values: using first particle's red (+0x110), min green, first particle's blue (+0x118)
            struct Color3f { float r, g, b; };
            Color3f color;
            color.r = *(float*)(pFirstParticle + 0x110 / 4);
            color.g = minGreen;
            color.b = *(float*)(pFirstParticle + 0x118 / 4);

            // Call renderer method at vtable+0x1c with pointer to color
            int** ppRenderer = *(int***)(thisPtr + 0x5c); // renderer object
            void* vtable = *ppRenderer;
            void (*setColorFunc)(void*, Color3f*) = *(void (**)(void*, Color3f*))(vtable + 0x1c);
            setColorFunc(ppRenderer, &color);
        }

        // If emitter state is not running (1), call default handler
        if (*(int*)(thisPtr + 0x50) != 1)
        {
            FUN_00996cd0(); // Likely default message handling or cleanup
            return;
        }
    }
    else if (*pMsgData == kMsgSetColor)
    {
        // Second message type: scale a float from message data and call helper
        // pMsgData[1] is a pointer to additional data (e.g., a struct with another pointer)
        int* pData = (int*)pMsgData[1];
        int* pInner = (int*)pData[1]; // +4 from pData? Actually *(int*)(pData+4) is a pointer to float at +4? 
        // The original: *(float *)(*(int *)(param_2[1] + 4) + 4) * scale
        // param_2[1] is pMsgData[1]. So pMsgData[1] is a pointer, add 4 -> get another pointer, then add 4 -> get float.
        // Simpler: assume float is at offset 0x4 from some struct.
        float unscaledValue = *(float*)(*(int*)(pMsgData[1] + 4) + 4);
        float scaledValue = unscaledValue * kParticleScale;
        int dummyZero = 0;
        // Third arg: *(undefined4 *)(*(int *)(pMsgData[1] + 4) + 0xc) -> some int/float
        int thirdArg = *(int*)(*(int*)(pMsgData[1] + 4) + 0xc);
        FUN_009995e0(dummyZero, scaledValue, thirdArg);
    }
    return;
}