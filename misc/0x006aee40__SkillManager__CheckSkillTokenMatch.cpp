// FUNC_NAME: SkillManager::CheckSkillTokenMatch
char SkillManager::CheckSkillTokenMatch(const char* tokenListString, int skillId) {
    int iVar3 = g_pSkillManager; // global singleton
    int iteratorState = 0;
    char found = 0;
    int iteratorBuffer[18];
    
    tokenizeBegin(iteratorBuffer, tokenListString, 0); // initialize string token iterator
    
    do {
        int tokenHandle = tokenizeGetNext(iteratorBuffer); // get next token
        char firstChar = tokenizeGetFirstChar(tokenHandle); // check if token is non-empty
        
        // If no more tokens or already found, break condition
        bool hasNext = (firstChar != '\0') && (found == 0);
        if (!hasNext) {
            return found;
        }
        
        // Hash the token
        uint tokenHash = tokenizeGetHash(); // likely hashes the current token
        
        // Lookup tokenHash in hash table (g_pSkillManager->m_pBuckets)
        // m_pBuckets at +0x50, m_bucketCount at +0x54
        int bucketIndex = tokenHash % g_pSkillManager->bucketCount; // g_pSkillManager+0x54
        Node* node = g_pSkillManager->m_pBuckets[bucketIndex]; // g_pSkillManager+0x50
        
        // Traverse linked list
        while (node != nullptr) {
            if (node->hash == tokenHash) {
                if (node->pData != nullptr) {
                    // Check field at offset 0x2c from the data pointer
                    int dataField = *(int*)(node->pData + 0x2c);
                    if (dataField == skillId) {
                        found = 1;
                    }
                }
                break;
            }
            node = node->pNext; // node[2] is next pointer
        }
        
        // If not found, continue iteration
        if (found) {
            // already set, but loop continues? Actually condition will exit on next check
        }
        
        // Advance iterator (call virtual function at offset 4 of iterator vtable)
        (**(code**)(iteratorBuffer[0] + 4))(); // next step in iterator
    } while (true);
}