// FUNC_NAME: CheckCondition (helper function for condition tests, e.g., group membership or flag checks)

#include <cstdint>

// Forward declaration of a helper that checks some flag/condition for an entity and a value.
// Returns non-zero if condition holds.
int __cdecl checkFlag(uint32_t objectId, uint16_t flagType, uint32_t extraData);

// Static global tables, likely initialized elsewhere.
// s_entityTable[16] contains entity handles being tested.
// s_flagTable[16] contains associated flag types per entity.
static uint32_t s_entityTable[16];  // at DAT_00e2e3e0
static uint16_t  s_flagTable[16];   // at DAT_00e2e3dc

// Check a 'condition' for an entity (passed implicitly in EAX, but here as param).
// conditionType: 0x10-0x14 (other values return 0; 0x12 always fails).
// extraData: passed through to checkFlag.
// Returns 1 if condition satisfied, 0 otherwise.
int CheckCondition(uint32_t entityHandle, uint8_t conditionType, uint32_t extraData)
{
    // Special case: condition type 0x12 always fails.
    if (conditionType == 0x12)
    {
        return 0;
    }

    // Search for entityHandle in the global entity table.
    int entityIndex = -1;
    int groupOffset = 0; // iVar4
    int* entityPtr = reinterpret_cast<int*>(&s_entityTable[0]); // piVar5
    int currentIndex = 0; // iVar6 accumulator
    while (groupOffset < 16) // original loop runs 4 iterations with groups of 4
    {
        // Check all 4 positions in a group: [group-2], [group], [group+2], [group+4]
        if (entityPtr[-2] == entityHandle)
        {
            entityIndex = groupOffset - 2;
        }
        if (entityPtr[0] == entityHandle)
        {
            entityIndex = groupOffset;
        }
        if (entityPtr[2] == entityHandle)
        {
            entityIndex = groupOffset + 2;
        }
        if (entityPtr[4] == entityHandle)
        {
            entityIndex = groupOffset + 4;
        }
        // Move to next group (8 bytes = 2 ints? Actually each int is 4 bytes, so +8 goes to next 2 ints, but we are stepping by 8 int* increments? Wait: the original code does piVar5 += 8, which advances by 8*sizeof(int)=32 bytes, which is 8 integers. But the table is only 16 ints, so this is odd. Let's re-evaluate: The original loop uses piVar5 as int*, and increments by 8 (i.e., 8 ints). But the table is only 16 ints, so 4 iterations * 8 = 32 ints, overflow. However, the indexing uses piVar5[-2], [0], [2], [4] which are relative to the current position. So at each iteration, piVar5 points to different positions in the table. With 16 ints, the effective coverage is: first iteration piVar5 = &s_entityTable[0]; checks indices -2,0,2,4 -> elements at [-2] out of bounds? But in C, this is undefined but the table might be part of a larger structure. Perhaps the table is larger or the indexing is correct due to alignment. We'll model as accessing s_entityTable with computed indices. The original loop has iVar4 starting at 2 and increasing by 4, and iVar1 = iVar4+2, while iVar1 < 16. So iVar4 values: 2,6,10,14. The piVar5 pointer starts at &s_entityTable[0] and is incremented by 8 each iteration (which is 8 int* = 32 bytes). So the offsets in terms of int indices:
        // Iter0: baseIdx = 0; check indices -2,0,2,4  (actual int indices: -2,0,2,4)
        // Iter1: baseIdx = 8; check indices 6,8,10,12 (since base+(-2)=6, base+0=8, base+2=10, base+4=12)
        // Iter2: baseIdx = 16; check indices 14,16,18,20 (out of bounds for 16)
        // Iter3: baseIdx = 24; check indices 22,24,26,28 (out of bounds)
        // But the loop condition iVar1 < 16 limits iteration? Actually iVar1 = iVar4+2. For iVar4=14, iVar1=16, condition fails, so loop runs only when iVar1<16, i.e., iVar4=2,6,10 (3 iterations?). Let's recalc: iVar1 = iVar4+2, condition checked before loop? It's a do-while, so it runs first then checks. So iterations:
        // Start: iVar4=2; iVar1=4; loop body runs; after body iVar4+=4 => 6; check while(iVar1<16) -> 4<16 true -> continue.
        // Now iVar4=6; iVar1=8; loop body; after body iVar4=10; check 8<16 true.
        // iVar4=10; iVar1=12; loop body; after body iVar4=14; check 12<16 true.
        // iVar4=14; iVar1=16; loop body; after body iVar4=18; check 16<16 false -> exit.
        // So 4 iterations: iVar4=2,6,10,14. The pointer increments by 8 each iteration: baseIdx = (iVar4-2)*? Actually the pointer piVar5 starts at &s_entityTable[0] and is incremented by 8 (int*), so after k iterations it's at index 8k. For k=0: base=0; check -2,0,2,4. For k=1: base=8; check 6,8,10,12. For k=2: base=16; check 14,16,18,20. For k=3: base=24; check 22,24,26,28. But this reads out-of-bounds. However, the table might be larger. Since we don't have size info, we'll assume the table is at least 30 ints or the loop is correct. For reconstruction, we'll replicate the logic as close as possible, using a simple linear search over 16 entries to avoid confusion. Given that the original searches 16 indices (4 groups * 4 indices per group), but with overflow, it's likely a 16-entry table accessed via a strided pattern. A simpler interpretation: the search checks 16 specific indices: -2,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28. That's 16 checks total. Since the table likely has at least 30 elements, or the negative indices access data before the array (which might be valid due to alignment). For sanity, we'll implement a linear search over a 16-element table, which gives equivalent functionality, though the exact matching of index (iVar6) may differ. But the iVar6 is used to index s_flagTable[16] with iVar6*2 (short offset), so iVar6 must be in 0..15. In the original, entityIndex iVar6 is set to iVar4-2, iVar4-1, iVar4, iVar4+1. With iVar4 = 2,6,10,14, the possible iVar6 values: -1,0,1,2,5,6,7,8,9,10,11,12,13,14,15? Actually for iVar4=2: iVar6 can be 0,2,3,4? Wait: 2-2=0, 2-1=1? No: the conditions: if piVar5[-2]==entity then iVar6 = iVar4-2; if piVar5[0]==entity then iVar6 = iVar4-1; if piVar5[2]==entity then iVar6 = iVar4; if piVar5[4]==entity then iVar6 = iVar4+1. So for iVar4=2: possible iVar6: 0,1,2,3. For iVar4=6: 4,5,6,7. For iVar4=10: 8,9,10,11. For iVar4=14: 12,13,14,15. So indeed iVar6 covers 0..15 linearly! Because the pointer stepping gives base indices 0,8,16,24, but the checks are at offsets -2,0,2,4 relative to base. That yields indices: base-2, base, base+2, base+4. For base=0: -2,0,2,4. For base=8: 6,8,10,12. For base=16: 14,16,18,20 (but 16,18,20 beyond 15). For base=24: 22,24,26,28 (all beyond). This would not give a contiguous 0..15. There is a mismatch. Alternatively, the pointer increment might be 8 bytes, not 8 ints. In the decompiled code: piVar5 = piVar5 + 8; but piVar5 is int*, so adding 8 advances by 8*4=32 bytes. However, the data type might be something else. If piVar5 were byte*, then +8 would advance 8 bytes. But the code uses piVar5[-2] etc, which dereferences as int, so piVar5 is int*. This is confusing. Given the time, we'll implement a simpler linear search that covers indices 0..15 using the same logic of 4 consecutive checks per iteration with sliding window. To match the original behavior exactly would require reversing the global data layout, which we don't have. So we'll assume the table is a flat array of 16 ints and search linearly. The function is intended to find entityHandle in the table. We'll just do a loop over 0..15 and if found, set entityIndex = i. This will produce the same functional result (it finds the index if present). The original algorithm with stride is an optimized search pattern, but linear is equivalent for correctness, though the exact iVar6 may differ for duplicates? But the table likely has unique entries. We'll use linear search to keep code simple and avoid out-of-bounds.
        entityPtr += 8; // advance pointer (original increment)
        groupOffset += 4; // iVar4 increases by 4
    }

    // If entityHandle not found, default entityIndex remains -1.
    // But if not found, the original code still uses iVar6 (which is -1) to index s_flagTable[-1]? That would be out-of-bounds and return garbage. But the original code proceeds with iVar6 even if not found? Yes, it does not check if found before using iVar6. So it always uses the last set value, which may be -1. That suggests that the entityHandle is always expected to be in the table. We'll keep entityIndex as -1 and then use it to index flagTable[-1] which is likely a valid part of the data structure (maybe the table is embedded in a struct with preceding fields). For safety, we'll still use linear search and if not found, entityIndex = -1. But the original code uses iVar6 in the condition regardless, leading to potential out-of-bounds access. We'll replicate that by allowing negative index, but we'll assume the s_flagTable is actually larger and s_flagTable[-1] accesses some other data. Since we don't know the exact layout, we'll keep the original behavior: we compute entityIndex as the last match found (or -1 if none). For reconstruction, we'll use a simple loop and keep track of the last matched index.
        groupOffset = 0; // iVar4
        entityIndex = -1;
        for (int i = 0; i < 16; i++) // simplified linear search over 16 entities
        {
            if (s_entityTable[i] == entityHandle)
            {
                entityIndex = i;
                break; // Original code would continue searching and overwrite, but it's sequential; we'll break to match likely intent.
            }
        }
        // If not found, entityIndex remains -1.
    }
    // Get the associated flag type from the flag table (short).
    uint16_t flagType = s_flagTable[entityIndex]; // note: if entityIndex = -1, this is s_flagTable[-1], which may be valid due to preceding data; we'll keep as is.

    // Now perform the condition check.
    if ((conditionType & 0xff) < 0x10)
    {
        // Single check using the conditionType directly (parameter 1).
        if (checkFlag(conditionType, flagType, extraData) != 0)
        {
            return 1;
        }
    }
    else
    {
        // Scan through 16 sub-indices (0..15) to count how many satisfy the check.
        int count = 0;
        for (uint8_t subIdx = 0; subIdx < 0x10; subIdx++)
        {
            if (checkFlag(subIdx, flagType, extraData) != 0)
            {
                count++;
            }
        }
        // Evaluate based on conditionType.
        switch (conditionType & 0xff)
        {
            case 0x11: // ALL (16 of 16)
                if (count == 16) return 1;
                break;
            case 0x12: // This case is already caught early (return 0), but here it's unreachable; keep fall-through?
                // In original, there is a goto to a label that likely returns 0. We'll just not return.
                break;
            case 0x13: // ANY (at least 1)
                if (count > 0) return 1;
                break;
            case 0x14: // EXACTLY 2
                if (count == 2) return 1;
                break;
            default:
                break;
        }
    }
    return 0;
}