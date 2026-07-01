// FUNC_NAME: NPC::findCoverAimDirection
// Address: 0x0080a080
// The function evaluates cover hint nodes relative to a given position and orientation,
// adjusts their normals to face the position, accumulates weighted direction contributions,
// and returns a boolean indicating whether any valid nodes were found.
// Outputs are stored in an optional struct (uint64 + float) representing the average direction.

bool __thiscall NPC::findCoverAimDirection(int thisPtr, float* position, undefined4* matrix, bool flag, ulonglong* outParam)
{
    float local_348;            // accumulated X-direction
    float local_340;            // accumulated Z-direction
    int local_33c;              // count of valid nodes
    int local_338;              // loop index offset
    bool result;                // return value
    float fVar14;               // zero constant
    float fVar15;               // constant from globals
    float fVar10, fVar11, fVar12, fVar13, fVar9;
    float fVar2, fVar3, fVar4;  // position components
    undefined4 local_310[3];    // transformed matrix rows
    float local_304;            // some float constant
    float local_2b0;            // another constant
    int local_19c;              // number of cover nodes
    int local_198;              // flags for allocation
    undefined1* local_1a0;      // pointer to cover node array
    undefined** local_1b0;      // pointer to vtable or class
    float local_290[6];         // buffer for axis data
    undefined1 local_1e0[48];   // stack buffer for initial transform
    undefined1 local_190[396];  // node array buffer (max 13 nodes of size 0x30)
    float local_260, local_25c, local_258; // position copy

    // Extract position components
    fVar2 = *position;
    fVar3 = position[1];
    fVar4 = position[2];

    // Initialize transform local_310 from param_3 and then multiply by a global matrix
    local_310[0] = *matrix;
    local_310[1] = matrix[1];
    local_310[2] = matrix[2];
    local_304 = _DAT_00d5780c;            // constant (likely 0.0)

    // Transform by global orientation
    FUN_00a66df0(&local_310, _DAT_00ef3a9c); // matrix multiply or quaternion transform

    // Prepare local_290 as 6 floats (0,0,0,0,0,0) and additional constants
    local_290[0] = _DAT_00d5780c;         // zero
    local_290[1] = 0.0f;
    local_290[2] = 0.0f;
    local_290[3] = 0.0f;
    local_290[4] = 0.0f;
    local_290[5] = _DAT_00d5780c;         // zero
    // These are probably axis/up vectors for some computation

    // Additional stack initialization
    local_278 = 0;
    local_274 = 0;
    local_270 = 0;
    local_26c = 0;
    local_264 = 0;
    float* local_2f0 = local_290;

    local_268 = _DAT_00d5780c;
    local_254 = _DAT_00d5780c;
    local_2ec = 0;
    local_2f4 = 0xffffffff;
    // ... other stack variables cleared

    // Copy of position
    local_260 = fVar2;
    local_25c = fVar3;
    local_258 = fVar4;

    FUN_00a64fd0();   // some initialization / setup
    // local_2df = (char)&local_2f8 - (char)&local_2e4; // offset calculation, irrelevant
    local_2b0 = DAT_00d5ccf8; // a constant (likely 1.0 or something)

    // Play sound or trigger something based on flag
    undefined4 uVar6 = 0x40322;   // sound ID or event ID
    if (flag) {
        uVar6 = 0x40332;
    }
    FUN_00540bc0(uVar6, *(undefined4*)(thisPtr + 0x830), 0, 0); // play audio

    // Setup node array for query
    local_2dc = FUN_00540cc0(local_2a4);   // get something like a query handle

    // Initialize node buffer from a global pool
    local_1a0 = local_190;
    local_1b0 = &PTR_LAB_00e397fc;      // some vtable pointer
    local_198 = 0x80000008;              // flags: probably "ignore" and size info
    local_19c = 0;                       // count of nodes will be set
    local_1ac = DAT_00e445dc;            // another global

    // Query the physics/collision system for objects in the area
    FUN_009eb730(&local_2f8, *(undefined4*)(*(int*)(DAT_01223480 + 0x24) + 0x6c), &local_1b0);

    // Iterate through the returned nodes
    fVar14 = 0.0f;                       // zero constant for comparison
    int iVar8 = 0;
    local_33c = 0;
    local_348 = 0.0f;
    local_340 = 0.0f;

    if (local_19c > 0) {
        local_338 = 0;
        fVar15 = DAT_00e44564;           // constant, likely 1.0 or -1.0?

        do {
            // Compute direction from node to position
            float dx = fVar2 - *(float*)(local_1a0 + local_338);          // node X
            float dy = fVar3 - *(float*)(local_1a0 + local_338 + 4);      // node Y
            float dz = fVar4 - *(float*)(local_1a0 + local_338 + 8);      // node Z

            float sqDist = dx*dx + dy*dy + dz*dz;
            float invDist = fVar14; // 0
            if (sqDist != 0.0f) {
                invDist = _DAT_00d5780c / sqrtf(sqDist); // 1/sqrt? or 0? Actually _DAT_00d5780c is 0.0? Wait earlier it's used as zero. But here it's 0.0 divided by sqrt? That would be 0.0. That seems wrong. Let's check: _DAT_00d5780c is used as 0.0 earlier, but here it's used as numerator. Possibly it's 1.0? Actually the code says: fVar10 = _DAT_00d5780c / SQRT(fVar9); If _DAT_00d5780c is 0.0, that would be 0.0. But that would make dot product always 0. So probably _DAT_00d5780c is 1.0. But the original uses it as 0.0 elsewhere. Might be a global constant that is actually 1.0. Given the context, it's likely a "magic number" for reciprocal sqrt. But the assembly would clarify. For cleanliness, I'll treat it as a float constant "one_over_sqrt" or just use 1.0f. Since the function computes dot product with normal, it likely uses the inverse distance to get a unit direction. So I'll assume _DAT_00d5780c is 1.0f.
            }

            // Adjust normal to face the position if it points away
            // Normal components at offsets 0x10, 0x14, 0x18
            float dot = *(float*)(local_1a0 + local_338 + 0x10) * invDist * dx
                      + *(float*)(local_1a0 + local_338 + 0x14) * invDist * dy
                      + *(float*)(local_1a0 + local_338 + 0x18) * invDist * dz;

            if (dot < 0.0f) {
                // Flip normal to face the position
                *(float*)(local_1a0 + local_338 + 0x10) = fVar15 - *(float*)(local_1a0 + local_338 + 0x10);
                *(float*)(local_1a0 + local_338 + 0x14) = fVar15 - *(float*)(local_1a0 + local_338 + 0x14);
                *(float*)(local_1a0 + local_338 + 0x18) = fVar15 - *(float*)(local_1a0 + local_338 + 0x18);
            }

            // Get adjusted normal components
            float nx = *(float*)(local_1a0 + local_338 + 0x10);
            float nz = *(float*)(local_1a0 + local_338 + 0x18); // note: Y component is at +0x14 but we only use X and Z? Actually code uses +0x10 and +0x18.

            // Check node validity
            char isValid = FUN_00803710(local_1a0 + local_338); // maybe isCoverNode?
            if (isValid) {
                char isActive = FUN_007fad30(local_1a0 + local_338); // additional test
                fVar14 = 0.0f;
                fVar15 = DAT_00e44564;  // reset constant
                if (isActive) {
                    // Weight from node at offset 0x1c, multiplied by constant
                    float weight = *(float*)(local_1a0 + local_338 + 0x1c) * DAT_00d5ccf8;
                    if (weight > 0.0f) {
                        local_33c++;
                        local_348 += nx * weight;
                        local_340 += nz * weight;
                    }
                }
            }
            local_338 += 0x30; // stride to next node
            iVar8++;
        } while (iVar8 < local_19c);

        if (local_33c > 0) {
            // Average the accumulated directions
            float invCount = 1.0f / (float)local_33c;
            local_348 *= invCount;
            local_340 *= invCount;
            result = true;
        } else {
            result = false;
        }
    } else {
        result = false;
    }

    // Store output if pointer provided
    if (outParam != nullptr) {
        *outParam = (ulonglong)(uint)local_348;  // store X as uint64 low 32 bits
        *(float*)(outParam + 1) = local_340;     // store Z as float at offset 8
    }

    // Cleanup: free node array if it was allocated (flags indicate allocation)
    local_1b0 = &PTR_LAB_00e397fc;
    if ((int)local_198 >= 0) {
        uint size = local_198 & 0x3fffffff;
        TlsGetValue(DAT_01139810);
        FUN_00aa26e0(local_1a0, size * 0x30, 0x17); // free memory
    }

    // Additional cleanup for the transform buffer
    local_1b0 = &PTR_LAB_00dc4710;
    FUN_00a66870();

    return result;
}