// FUNC_NAME: HashGenerator::computeHash
// Address: 0x00655000
// This function computes a cryptographic hash over three data segments:
//   - param_2 (20 bytes)
//   - param_3 (8 bytes)
//   - this->field_0x70 (12 bytes, likely object unique ID or key)
// It returns the first 32-bit word of the hash.
uint32_t HashGenerator::computeHash(void* data1, void* data2) {
    // Hash context buffer (208 bytes, e.g., SHA-1 or custom EARS hash)
    char hashContext[208];
    
    // Initialize hashing context
    hashInit(hashContext);
    
    // Feed first data block (20 bytes)
    hashUpdate(hashContext, data1, 0x14);
    
    // Feed second data block (8 bytes)
    hashUpdate(hashContext, data2, 8);
    
    // Feed internal data from this object at offset 0x70 (12 bytes)
    hashUpdate(hashContext, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + 0x70), 0xC);
    
    // Finalize hash and store result in array of 8 uint32_t (32 bytes)
    uint32_t hashResult[8];
    hashFinal(hashContext, hashResult);
    
    // Return the first 32-bit word as the hash identifier
    return hashResult[0];
}