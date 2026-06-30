// FUNC_NAME: CryptoState::decryptAndGetBuffer
int __thiscall CryptoState::decryptAndGetBuffer(void* thisPtr, uint32_t key, uint32_t iv, float timeFactor)
{
    int validationResult;
    int local_10; // state first dword
    int local_c;  // state second dword
    int local_8;  // state third dword
    int local_4;  // state fourth dword
    
    // Initial validation of key/IV pair
    validationResult = FUN_006ff9a0(iv, key);
    if (validationResult == 0) {
        return 0;
    }
    
    // Initialize state with magic constants (AES key schedule seeds?)
    local_10 = 0xBBDBDBBA;  // -0x45245246
    local_c  = 0xBEEFBEEF;  // -0x41104111
    local_8  = 0xEAC15A55;  // -0x153ea5ab
    local_4  = 0x91100911;  // -0x6eeff6ef
    
    // Mix/transform the state
    FUN_006ff280(&local_10);
    
    // Check if state remained unchanged or all zero – both invalid
    if (local_10 == 0xBBDBDBBA) {
        if ((local_c  == 0xBEEFBEEF) &&
            (local_8  == 0xEAC15A55) &&
            (local_4  == 0x91100911)) {
            return 0;  // state untouched -> failure
        }
    }
    else if ((local_10 == 0) && (local_c == 0) && (local_8 == 0) && (local_4 == 0)) {
        return 0;  // zeroed state -> failure
    }
    
    // Get a time-based or random factor
    float factor = (float)FUN_006ff320();
    
    // Final decryption/validation step
    char success = FUN_006ffc40(&local_10, timeFactor, factor);
    if (success == '\0') {
        return 0;
    }
    
    // Return pointer to decrypted buffer at offset 0x24 in this object
    return (int)(thisPtr) + 0x24;
}