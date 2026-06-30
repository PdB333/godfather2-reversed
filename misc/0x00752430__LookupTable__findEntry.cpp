// FUNC_NAME: LookupTable::findEntry
uint8 LookupTable::findEntry(LookupTable* thisTable, uint32 hashValue, uint32 firstKey, void* tableRoot, uint32 secondKey, void* comparisonValue)
{
    uint8 result = 0;
    
    if (firstKey == secondKey) {
        int32 nodePtr = FUN_005f5ec0(tableRoot, comparisonValue);
        if (nodePtr != 0) {
            result = FUN_005fd340(*(uint16*)(nodePtr + 8), hashValue, thisTable);
            return result;
        }
    }
    else {
        int localList = 0;      // temporary list head (pointer to a list node)
        int savedNext = 0;       // saved next pointer of the secondKey node
        
        if (secondKey != 0) {
            localList = secondKey;                     // treat secondKey as a node pointer
            savedNext = *(int*)(secondKey + 4);        // +0x4 = next pointer
            *(int**)(secondKey + 4) = &localList;      // temporarily rewire next to local stack
        }
        
        int dummyVal = (int)comparisonValue;  // unused except as second param? stored in local_4
        
        int32 nodePtr = FUN_005f5f20(tableRoot, &localList);
        result = 0;
        if (nodePtr != 0) {
            result = FUN_005fd340(*(uint16*)(nodePtr + 8), hashValue, thisTable);
        }
        
        if (localList != 0) {
            FUN_004daf90(&localList);  // cleanup the temporary list
        }
    }
    
    return result;
}