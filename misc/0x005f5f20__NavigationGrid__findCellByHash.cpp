// FUNC_NAME: NavigationGrid::findCellByHash
int __thiscall NavigationGrid::findCellByHash(NavigationGrid* thisGrid, HashKey* key, CellSearchResult* cell)
{
    // cell->targetCellID is the desired cell ID
    int targetCellID = cell->targetCellID;
    if (targetCellID == 0) {
        return 0;
    }

    // cell->hashIndex is additional search parameter (related to position/ID)
    int hashIndex = cell->hashIndex;

    // +0x20 in the target cell: presumably a base value used to compute a short offset
    int baseValue = *(int*)(targetCellID + 0x20);

    // Count of hash iterations from key structure (e.g., number of bytes in a hash)
    int iterationCount = key->iterationCount; // +0x15
    short keyBase = key->keyBase; // +0x16: base short value

    // Iterate through hash buckets
    for (int i = 0; i < iterationCount; i++) {
        // Compute bucket index: (keyBase + i) * 16 + grid->bucketArrayBase (at +0x30)
        int bucketIndex = (keyBase + i) * 16 + *(int*)(thisGrid + 0x30);
        // bucketIndex points to a bucket structure (16 bytes? but only 0xc,0x4, etc used)

        // Read a ushort from offset 0xc of bucket, then use it to index into an ID table at +0x34
        ushort typeID = *(ushort*)(*(int*)(thisGrid + 0x34) + (uint)*(ushort*)(bucketIndex + 0xc) * 2);

        // If typeID is not 0xFFFF (invalid)
        if (typeID != 0xFFFF) {
            // Offset into node array (each node is 8 bytes? Actually offset = typeID * 8)
            int nodeOffset = (uint)*(ushort*)(bucketIndex + 0xc) * 8;
            // Get pointer to node from node array (+0x38)
            int* nodePtr = *(int**)((int*)(*(int*)(thisGrid + 0x38) + nodeOffset));

            // If node doesn't exist, attempt to create it
            if (nodePtr == 0) {
                // node address = typeID * 16 + nodeAllocBase (+0x28)
                int nodeAddr = typeID * 16 + *(int*)(thisGrid + 0x28);
                nodePtr = (int*)FUN_005faf10(nodeAddr);
                if (nodePtr != 0) {
                    // Insert node into bucket's linked list
                    int* bucketEntry = (int*)(*(int*)(thisGrid + 0x38) + nodeOffset);
                    if (*bucketEntry != (int)nodePtr) {
                        if (*bucketEntry != 0) {
                            // Release old node (likely smart pointer)
                            FUN_004daf90(bucketEntry);
                        }
                        *bucketEntry = (int)nodePtr;
                        // Link node into chain: node's next points to bucket entry?
                        bucketEntry[1] = *(int*)(nodePtr + 4);
                        *(int**)(nodePtr + 4) = bucketEntry;
                    }
                }
            }

            // Check if this node matches the search criteria
            if ((int)nodePtr == targetCellID && 
                *(short*)(bucketIndex + 4) == (short)((hashIndex - baseValue) / 0x24)) {
                // Found: return the bucket address (which contains the cell info)
                return bucketIndex;
            }
        }
    }
    return 0;
}