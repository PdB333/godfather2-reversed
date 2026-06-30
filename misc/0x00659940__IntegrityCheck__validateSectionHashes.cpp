// FUNC_NAME: IntegrityCheck::validateSectionHashes
void IntegrityCheck::validateSectionHashes() { // 0x00659940
    // This function computes SHA256 hashes for a list of strings (likely section names)
    // and compares them against hardcoded expected hashes.
    // Returns 0 on success, 5 on integrity failure.
    
    // Buffer layout:
    //   localBuffer[0..31] - output hash
    //   localBuffer[32..243] - hash context (212 bytes)
    uint8_t localBuffer[244];
    
    // Table of entries: each is 36 bytes (4 bytes string pointer + 32 bytes hash)
    // The table is terminated by address > 0x00e4335f
    const struct HashEntry {
        const char* name;
        uint8_t expectedHash[32];
    }* entry = reinterpret_cast<HashEntry*>(PTR_DAT_00e43318);
    
    do {
        // Initialize hash context (context starts at localBuffer+32)
        hashInit(localBuffer + 32);
        
        // Get the current string pointer
        const char* sectionName = entry->name;
        
        // Compute string length
        int len = strlen(sectionName);
        
        // Feed string into hash (excluding null terminator)
        hashUpdate(localBuffer + 32, sectionName, len);
        
        // Finalize hash into localBuffer[0..31]
        hashFinal(localBuffer + 32, localBuffer);
        
        // Compare computed hash with expected hash (32 bytes)
        bool match = (memcmp(localBuffer, entry->expectedHash, 32) == 0);
        
        if (!match) {
            return 5; // Integrity violation
        }
        
        // Advance to next entry (each entry is 9 dwords = 36 bytes)
        entry = (HashEntry*)((uint8_t*)entry + 36);
        
    } while ((uint32_t)entry <= 0x00e4335f); // Until end of table (approx)
    
    return 0; // All hashes match
}