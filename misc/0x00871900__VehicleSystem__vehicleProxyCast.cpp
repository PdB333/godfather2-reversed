// FUNC_NAME: VehicleSystem::vehicleProxyCast

// Address: 0x00871900
// Role: Performs a proxy cast (likely raycast/shape cast) for vehicle physics.
// Parameters:
//   fromPos - start position (3 floats)
//   toPos - end position (3 floats)
//   hitData - pointer to hit result data (can be null)
//   hitDataCount - number of hit data entries (size of hitData array)
// Returns: true if the cast hit something (cStack_108 == 0)

bool __cdecl VehicleSystem::vehicleProxyCast(float* fromPos, float* toPos, void* hitData, int hitDataCount)
{
    // --- Profiling / TLS tracing ---
    // The function uses TLS for performance profiling (similar to other functions in this binary)
    LPVOID tlsBase = TlsGetValue(DAT_01139830);
    undefined4** tlsStack = *(undefined4***)((int)tlsBase + 4);
    if (tlsStack < *(undefined4***)((int)tlsBase + 0xC))
    {
        *tlsStack = "TtVehicle Proxy Cast";
        uint64 tsc = rdtsc();
                tlsStack[1] = tsc;
        *(undefined4***)((int)tlsBase + 4) = tlsStack + 3;
    }

    // --- Initialize stack based shape / query data ---
    // Call to clear/zero out some global state
    FUN_00a64b00(_DAT_00d7613c);

    // Structure representing a shape/box (probably for the query)
    // Offsets: +0x00 -> min X, +0x04 -> min Y, +0x08 -> min Z, etc.
    // In this case we use default zero vector from global
    float shapeMin[3] = { *DAT_00d5780c, *DAT_00d5780c, *DAT_00d5780c };  // +0x00, +0x04, +0x08
    float shapeMax[3] = { *DAT_00d5780c, *DAT_00d5780c, *DAT_00d5780c };  // +0x0c, +0x10, +0x14
    float shapePos[3] = { *DAT_00d5780c, *DAT_00d5780c, *DAT_00d5780c };  // +0x18, +0x1c, +0x20

    // Set the starting position for the cast
    shapePos[0] = fromPos[0];
    shapePos[1] = fromPos[1] + _DAT_00d76124;   // +0x1c : add a time offset (global time step)
    shapePos[2] = fromPos[2];

    // Pointer to the shape structure
    float* shapePtr = shapeMin;   // puStack_170 points to uStack_c0, which is shapeMin

    // Second structure (auStack_e0) seems to be another array or shape data
    float extraData[8] = {}; // zeroed, puStack_178 points to this

    // Clear more fields (uStack_bc to uStack_84)
    // These correspond to unknown fields in the shape/query structure
    // For now, just zero them
    float zero = 0.0f;
    shapeMin[1] = 0.0f;   // uStack_bc
    shapeMin[2] = 0.0f;   // uStack_b8
    // etc. (skipping for brevity)

    // Set some extra values to zero
    extraData[0] = 0.0f; // uStack_16c
    // ... more initializations

    // Initialize a second structure for the "end" position (uStack_1a0)
    float endPos[3];
    endPos[0] = toPos[0];
    endPos[1] = toPos[1] + _DAT_00d76124; // add time step
    endPos[2] = toPos[2];
    // +0x0c, +0x10, +0x14 (offset in that struct) well skip

    // ... rest of initializations (uStack_194, ppuStack_110, etc.)

    // Call to clear out some context
    FUN_00a64fd0();

    // Compute an offset between two pointers, used later as a size
    int fieldSize = (char*)extraData - (char*)&someField;  // cStack_15f = (char)&puStack_178 - (char)&uStack_164

    // Prepare for memory allocation if hitDataCount > 0
    bool hasHitData = (hitDataCount != 0);
    undefined4* allocBuffer = nullptr;
    undefined4 stackBuffer;  // uStack_1b0
    if (hasHitData)
    {
        allocBuffer = &stackBuffer;
        stackBuffer = FUN_0043b490();  // Some query/creation function (maybe returns a reference)
        // Copy hitData into temporary buffer on stack (auStack_1ac)
        _memcpy(auStack_1ac, hitData, hitDataCount * 4);
        hitDataCount++; // increase count for allocation?
    }

    // Allocate memory (FUN_00540bc0 : likely memory allocator)
    // First arg is flags derived from hasHitData
    int allocFlags = ((-(int)hasHitData) & 0x20) + 2;  // if true -> 0x22, else 0x2
    FUN_00540bc0(allocFlags, 0xC0000, allocBuffer, hitDataCount);

    // Get an index/offset from the allocated memory (FUN_00540cc0)
    int shapeIndex = FUN_00540cc0(auStack_124);  // auStack_124 is some array on stack

    // Setup end position struct (uStack_190, uStack_18c = global default)
    // ... (similar to start)

    // Global pointer for type identification
    undefined** typeVtable = &PTR_LAB_00dcfea0;  // vtable or type info

    // Perform the actual proxy cast query
    // FUN_009e7fd0 takes pointers to the shape data, end position, type info, and a flag (0)
    FUN_009e7fd0(&extraData, &endPos, &typeVtable, 0);

    // Check the result flag (cStack_108)
    bool hitDetected = (cStack_108 == '\0');

    // --- Profiling / TLS end ---
    LPVOID tlsBaseEnd = TlsGetValue(DAT_01139830);
    undefined4** tlsStackEnd = *(undefined4***)((int)tlsBaseEnd + 4);
    if (tlsStackEnd < *(undefined4***)((int)tlsBaseEnd + 0xC))
    {
        *tlsStackEnd = &DAT_00e39c6c;  // Some marker string
        uint64 tscEnd = rdtsc();
        tlsStackEnd[1] = tscEnd;
        *(undefined4***)((int)tlsBaseEnd + 4) = tlsStackEnd + 3;
    }

    return hitDetected;
}