// FUNC_NAME: SpatialQuery::sweepTestOverlap
uint __thiscall SpatialQuery::sweepTestOverlap(void *context, float *box, uint userData, uint *objectList)
{
    uint resultMask = 0;
    // Validate input
    if (objectList == nullptr) {
        return 0xFFFFFFFF;
    }

    // Local stack variables: initialised with some global transform data
    // DAT_00e2b1a4 likely identity (0.0f or 1.0f)  _DAT_00ef3a9c some global matrix
    local_50 = userData;                // +0x50: user parameter stored but not directly used
    local_4c = 0xFFFFFFFF;              // sentinel
    local_40 = 0xFFFFFFFF;
    local_20 = 0;

    // Setup local transform from global data
    FUN_00a66df0(&local_a0, _DAT_00ef3a9c);

    do {
        // Extract bounding box / transformation for the current object
        // local_90[0] becomes an object pointer (vtable at +0x20 contains test function)
        FUN_00558db0(local_90, objectList, context);

        // Apply offset (likely the object's position) to the query box
        // box[0..3] = min X,Y,Z, ?  box[4] = ?  box[5..7] = max X,Y,Z?
        box[0] -= local_c0;
        box[1] -= local_bc;
        box[2] -= local_b8;
        box[3] -= local_b4;
        box[5] -= local_bc;
        box[6] -= local_b8;
        box[7] -= local_b4;
        box[4] -= local_c0;

        // Call virtual test method (vtable slot +0x20)
        // Returns result in local_c5 and potentially modifies local_60 (some hit info)
        char testResult;
        (*(void (**)(char *, float *, undefined1 *))(*(int *)local_90[0] + 0x20))(&testResult, box, local_60);

        if (testResult == 0) {
            // Test failed; perform half-space check using absolute values
            // fStack_b0 etc are absolute values of box components via FUN_0040f220 (likely fabsf)
            // Compare against thresholds stored in fStack_70, fStack_6c, fStack_68 (set by the virtual test)
            // If all three comparisons indicate border/outside, fall through to mark hit
            if (fStack_70 < (float)FUN_0040f220(box[0])
             && fStack_6c < (float)FUN_0040f220(box[1])
             && fStack_68 < (float)FUN_0040f220(box[2])) {
                // Actually the logic in the original code: if testResult == 0, it computes fabs of box components and then if the condition (bVar3|bVar5|bVar4) == 0xe it jumps to LAB_005591b1 (the hit handling).
                // 0xe = 14 = 1110 binary, so all three bits set? Actually bVar4 is 0 or 8, bVar5 0 or 4, bVar3 0 or 2. So 0xe = 14 = 8+4+2 => all three are non-zero (i.e., fStack_b0 > fStack_70 etc). So it hits if all three are greater than thresholds.
                // We'll simplify as "hit if outside all thresholds".
                hitMask |= *objectList;
            }
        } else {
            // Test immediately indicated overlap
            hitMask |= *objectList;
        }

        // Restore the box to original state
        box[0] += local_c0;
        box[1] += local_bc;
        box[2] += local_b8;
        box[3] += local_b4;
        box[5] += local_bc;
        box[6] += local_b8;
        box[7] += local_b4;
        box[4] += local_c0;

        // Move to next object in list (each object is 16 bytes)
        objectList += 4;  // sizeof(uint) * 4 = 16 bytes

        // Check termination flag at offset 0x0B of the *just processed* object
        if (*(char *)((int)(objectList - 4) + 0x0B) != 0) {
            // End of list
            break;
        }
    } while (1);

    // Cleanup
    FUN_00a66870();
    return resultMask;
}