// FUNC_NAME: EntityManager::findNextAvailableId
int __thiscall EntityManager::findNextAvailableId(int skipIndex) {
    uint startIdx;
    int result = 0;
    
    // Convert skipIndex to an index, add 1 to start after it
    if (skipIndex != 0) {
        int idx = convertIdToIndex(skipIndex);  // FUN_00849a70
        startIdx = idx + 1;
    } else {
        startIdx = 0;
    }
    
    // Check bounds and search array
    if ((int)startIdx < 0) return 0;
    
    if (startIdx >= m_objectCount) return 0;  // m_objectCount at +0x14
    
    int* objPtr = m_objectArray + startIdx;  // m_objectArray at +0x10
    
    do {
        int id = *(int*)(*objPtr + 0x50);          // m_id
        byte flags = *(byte*)(*objPtr + 0x58);      // m_flags
        
        // Skip if bit0 of flags is set (active/in use) OR id matches exclude value
        if ((flags & 1) != 0 || id == m_excludeValue) {  // m_excludeValue at +0x8
            startIdx++;
            objPtr++;
        } else {
            result = id;
            break;
        }
    } while (startIdx < m_objectCount);
    
    return result;
}