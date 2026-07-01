// FUNC_NAME: SpatialQuery::performOverlapQuery

// This function performs or updates a spatial overlap query centered at (posX, posY, posZ)
// with a half-extent defined by the global constant at 0x00d5ef70.
// On first call, it allocates a query handle and builds the query structure.
// On subsequent calls, it updates the bounding box of the existing query.
// Returns true if the query result contains any objects (count > 0 at offset 0xC4 of result structure).

undefined4 __thiscall SpatialQuery::performOverlapQuery(
    int thisPtr,
    float centerX,
    float centerY,
    float centerZ
)
{
    float minX, maxX, minY, maxY, minZ, maxZ;
    float *pQueryResult;       // thisPtr + 0x24
    undefined8 *pAllocData;    // temporary for allocation
    int queryHandle;            // returned from initialization
    int resultCount;            // field at +0xC4 of query result

    minX = centerX - __globalHalfExtent;   // DAT_00d5ef70
    maxX = centerX + __globalHalfExtent;
    minY = centerY - __globalHalfExtent;
    maxY = centerY + __globalHalfExtent;
    minZ = centerZ - __globalHalfExtent;
    maxZ = centerZ + __globalHalfExtent;

    // Check if query structure already exists
    if (*(int *)(thisPtr + 0x24) == 0)
    {
        // Allocate 0x40130 bytes for the query's internal data (possibly a spatial hash/grid)
        pAllocData = (undefined8 *)FUN_00540bf0(2, 0, 0x40130, 0xffffffff, 0, 0);
        
        // Copy the first 20 bytes of the allocated block into this object (+0x28..+0x38)
        *(undefined8 *)(thisPtr + 0x28) = *pAllocData;                               // +0x28: 8 bytes
        *(undefined8 *)(thisPtr + 0x30) = pAllocData[1];                             // +0x30: 8 bytes
        *(undefined4 *)(thisPtr + 0x38) = *(undefined4 *)(pAllocData + 2);           // +0x38: 4 bytes

        TlsGetValue(DAT_01139810);
        // Allocate a new “query result” structure (size 0xD0, type 0x31)
        pQueryResult = (int *)FUN_00aa2680(0xd0, 0x31);
        *(undefined2 *)(pQueryResult + 4) = 0xd0;     // store size for validation?

        // Initialize the query handle from the 20-byte blob at +0x28
        queryHandle = FUN_00540cc0(thisPtr + 0x28);

        // Build the query region: pass the bounding box and handle
        pQueryResult = (int *)FUN_009f59e0(&minX, queryHandle);

        // Store the query result pointer
        *(int *)(thisPtr + 0x24) = (int)pQueryResult;

        // If allocation succeeded and the result has an empty (zero) ref count at +0x08, release it
        if ((pQueryResult != 0) && (*(int *)(pQueryResult + 8) == 0))
        {
            FUN_009e7450((int)pQueryResult);
        }
    }
    else
    {
        // Update the existing query with the new bounding box
        FUN_009f5240(&minX);
    }

    // Return whether the query result contains any objects (field at +0xC4)
    pQueryResult = *(int *)(thisPtr + 0x24);
    return CONCAT31((int3)((uint)pQueryResult >> 8), *(int *)(pQueryResult + 0xC4) > 0);
}