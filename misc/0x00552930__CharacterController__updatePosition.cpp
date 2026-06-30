// FUNC_NAME: CharacterController::updatePosition
// Address: 0x00552930
// Role: Main physics integration and collision resolution for a character controller.
// Uses TLS-based profiling markers for sub-steps.

void __thiscall CharacterController::updatePosition(void* this, int param1, int param2)
{
    // TLS profiling marker for function entry
    {
        void* tls = TlsGetValue(g_tlsProfileIndex);
        char** marker = *(char***)((char*)tls + 4);
        char** markerEnd = *(char***)((char*)tls + 12);
        if (marker < markerEnd)
        {
            *marker = "LtupdateCharacter";          // +0x00
            *(int*)(marker + 3) = (int)"StCast";    // +0x0C (actually marker[3] = string pointer)
            uint64_t cycles = rdtsc();
            *(int*)(marker + 1) = (int)cycles;      // +0x04
            *(char***)((char*)tls + 4) = marker + 4;
        }
    }

    // this is in_EAX (ECX). Cast to struct for clarity
    struct CharacterState* state = (CharacterState*)this;

    // Get pointer to collision shape (vtable offset 6? Actually in_EAX[0xc] is a pointer to shape at 0x30)
    void* shape = *(void**)((char*)state + 0x30);   // +0x30: pointer to collision shape (e.g., capsule)
    float shapeY = *(float*)((char*)shape + 0x30);  // shape position Y
    int shapeFlags1 = *(int*)((char*)shape + 0x34);
    float shapeZ = *(float*)((char*)shape + 0x38);
    int shapeFlags2 = *(int*)((char*)shape + 0x3C);

    // time step from param1+8 (probably a struct with time step at +0x08)
    float dt = *(float*)(param1 + 8);               // +0x08: delta time

    // some global constants
    float gDeltaTime = DAT_00e44598;                // 0.016666...? (1/60)
    float gFrictionCoeff = DAT_00e2b1a4;            // friction coefficient
    float gSlipThreshold = DAT_00e2e210;            // threshold for slipping

    // Check if dt exceeds maximum allowed step (likely substep loop)
    if (gDeltaTime < dt)
    {
        int substepCount = 0;
        do
        {
            if (substepCount > 9) break;

            // Profiling sub-step: "StUpdateManifold"
            {
                void* tls = TlsGetValue(g_tlsProfileIndex);
                char** marker = *(char***)((char*)tls + 4);
                char** markerEnd = *(char***)((char*)tls + 12);
                if (marker < markerEnd)
                {
                    *marker = "StUpdateManifold";
                    uint64_t cycles = rdtsc();
                    *(int*)(marker + 1) = (int)cycles;   // store low 32 bits? Actually undefined4
                    *(char***)((char*)tls + 4) = marker + 3;
                }
            }

            // Call updateManifold virtual function (vtable+0x0C)
            (*(void(__thiscall**)(void*))(*(void**)state + 0x0C))(param2);

            int numContacts = *(int*)((char*)state + 0x68);       // +0x68: number of contacts? (in_EAX[0x1a])
            int maxContacts = *(int*)((char*)state + 0x60);       // +0x60: maximum contact capacity? (in_EAX[0x18])
            int contactSize = 0x40;
            int contactDataBase = *(int*)((char*)state + 0x64);   // +0x64: pointer to contact arrays (in_EAX[0x19])

            // Allocate temporary contact buffer using TLS allocator
            int* tlsAllocator = (int*)TlsGetValue(DAT_01139810);
            int currentOffset = tlsAllocator[8];                  // current alloc offset
            int allocSize = (numContacts + maxContacts) * 0x40 + 0x10;
            int newOffset = currentOffset + allocSize;
            int tempBufferPtr;
            if ((uint)newOffset > (uint)tlsAllocator[11])        // compare to buffer size
            {
                // Need to allocate more memory (vtable+0x14)
                tempBufferPtr = (**(int(__thiscall**)(int))(*(void**)tlsAllocator + 0x14))(allocSize);
            }
            else
            {
                tlsAllocator[8] = newOffset;
                tempBufferPtr = currentOffset;
            }

            // Copy contact data to temporary buffer (vtable+0x14? Actually +0x14 is a function that copies)
            for (int i = 0; i < numContacts; i++)
            {
                (*(void(__thiscall**)(int, float))(*(void**)state + 0x14))(
                    contactDataBase + i * 0x30, (float)(tempBufferPtr + i * 0x40));
            }

            // Profiling sub-step: "StSlexMove"
            {
                void* tls = TlsGetValue(g_tlsProfileIndex);
                char** marker = *(char***)((char*)tls + 4);
                if (marker < *(char***)((char*)tls + 12))
                {
                    *marker = "StSlexMove";
                    uint64_t cycles = rdtsc();
                    *(int*)(marker + 1) = (int)cycles;
                    *(char***)((char*)tls + 4) = marker + 3;
                }
            }

            // --- Solver setup ---
            int numContactsAgain = *(int*)((char*)state + 0x68);  // re-read
            int maxContactsAgain = *(int*)((char*)state + 0x60);
            float friction = DAT_00e2b1a4;                        // global friction coefficient
            int contactFlags = 0;                                 // will be set to flags for each contact
            // Store initial velocity (from state offsets)
            float velX = *(float*)((char*)state + 0x10);          // +0x10: velocity X
            float velY = *(float*)((char*)state + 0x14);          // +0x14: velocity Y
            float velZ = *(float*)((char*)state + 0x18);          // +0x18: velocity Z
            float velW = *(float*)((char*)state + 0x1C);          // +0x1C: velocity W (maybe unused)

            // Allocate temporary contact index buffer
            int* tlsAlloc2 = (int*)TlsGetValue(DAT_01139810);
            float* tempIndexPtr = (float*)tlsAlloc2[8];           // reinterpret as float for some operations
            int allocSize2 = (numContactsAgain + maxContactsAgain + 1) * 0x10;
            int newOffset2 = (int)tempIndexPtr + allocSize2;
            if ((uint)newOffset2 > (uint)tlsAlloc2[11])
            {
                tempIndexPtr = (float*)(**(int(__thiscall**)(int))(*(void**)tlsAlloc2 + 0x14))(allocSize2);
            }
            else
            {
                tlsAlloc2[8] = newOffset2;
            }

            // Prepare solver data (set indices, velocities, etc.)
            int solverData[16]; // approximate stack structure
            // ... (many stack manipulations omitted for brevity)

            // For each contact, apply forces and solve constraints
            // The while loop iterates over contacts and applies friction/penetration correction

            // Call applySurface (vtable+0x10) to apply friction and move
            (*(void(__thiscall**)(void*, float, int))(*(void**)state + 0x10))(param1, (float)tempIndexPtr, numContactsAgain);

            // Profiling sub-step: "StApplySurf"
            {
                void* tls = TlsGetValue(g_tlsProfileIndex);
                char** marker = *(char***)((char*)tls + 4);
                if (marker < *(char***)((char*)tls + 12))
                {
                    *marker = "StApplySurf";
                    uint64_t cycles = rdtsc();
                    *(int*)(marker + 1) = (int)cycles;
                    *(char***)((char*)tls + 4) = marker + 3;
                }
            }

            // Apply surface forces and update state
            // (vtable+0x10 already called, now additional adjustments)

            // Profiling sub-step: "StCastMove"
            {
                void* tls = TlsGetValue(g_tlsProfileIndex);
                char** marker = *(char***)((char*)tls + 4);
                if (marker < *(char***)((char*)tls + 12))
                {
                    *marker = "StCastMove";
                    uint64_t cycles = rdtsc();
                    *(int*)(marker + 1) = (int)cycles;
                    *(char***)((char*)tls + 4) = marker + 3;
                }
            }

            // Check for ground collision and adjust velocity
            float posDeltaX = posDeltaXAccum; // from previous computation (unaff_ESI, etc.)
            float posDeltaY, posDeltaZ;
            // ... (lengthy position and velocity adjustment using friction and slipping)

            // If reached the end of sub-steps, update final position and velocity
            // else continue loop
        }
        while (gDeltaTime < dt);
    }

    // Finalize: store corrected velocity back to state
    *(int*)((char*)state + 0x10) = (int)finalVelX;     // store as int? Actually the decompiled shows in_EAX[4] = iStack_110 (int)
    *(int*)((char*)state + 0x14) = (int)finalVelY;
    *(int*)((char*)state + 0x18) = (int)finalVelZ;
    *(int*)((char*)state + 0x1C) = (int)finalVelW;

    // Clean up TLS allocators (reverse of allocation)
    // ... omitted

    // TLS profiling marker for exit
    {
        void* tls = TlsGetValue(g_tlsProfileIndex);
        char** marker = *(char***)((char*)tls + 4);
        if (marker < *(char***)((char*)tls + 12))
        {
            *marker = (char*)&DAT_00e391e4; // some end marker string
            uint64_t cycles = rdtsc();
            *(int*)(marker + 1) = (int)cycles;
            *(char***)((char*)tls + 4) = marker + 3;
        }
    }
    return;
}