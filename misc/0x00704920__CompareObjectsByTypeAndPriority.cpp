// FUNC_NAME: CompareObjectsByTypeAndPriority

// Compares two game objects for sorting purposes.
// Returns 1 if pObjB should come before pObjA (i.e., pObjB < pObjA), 0 otherwise.
// Primary sort key: object type ID (via getObjectTypeId)
// Secondary sort key: uint at offset 0x510 (e.g., priority, sequence number, or spawn order)
// If pObjA is null, returns 0.
// If pObjB is null, returns 0 (no comparison performed).

// Called from sort routine at 0x007051d0.

int CompareObjectsByTypeAndPriority(void* pObjA, void* pObjB)
{
    if (pObjA == 0) {
        return 0;
    }
    if (pObjB != 0) {
        int typeIdA = getObjectTypeId(pObjA);  // FUN_00704860
        int typeIdB = getObjectTypeId(pObjB);  // FUN_00704860
        if (typeIdA == typeIdB) {
            // Compare priority values at +0x510 (likely uint32)
            // pObjB's value must be less than pObjA's for true.
            unsigned int priorityA = *(unsigned int*)((char*)pObjA + 0x510);
            unsigned int priorityB = *(unsigned int*)((char*)pObjB + 0x510);
            if (priorityB < priorityA) {
                return 1;
            }
        }
    }
    return 0;
}