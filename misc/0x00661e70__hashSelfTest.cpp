// FUNC_NAME: hashSelfTest
int hashSelfTest(void)
{
    int ret;
    uint remainingBytes;
    int cmpResult;
    byte *pEntryData;
    byte *pExpectedInput;
    byte *pExpectedHash;
    byte hashOutput[16];
    byte buffer[4284];
    
    // Set magic marker at offset 0x10AC (verification signature)
    buffer[0x10AC] = 0x80;
    buffer[0x10AD] = 0x1E;
    buffer[0x10AE] = 0x66;
    buffer[0x10AF] = 0x00;
    
    byte *pCurrentEntry = &DAT_00e4386c; // start of test data table
    
    do {
        // Clear workspace area (0x10A0 bytes starting at offset 0x10)
        memset(buffer + 0x10, 0, 0x10A0);
        
        // Load test input into buffer+0x10; size is stored 4 bytes before current entry
        ret = FUN_00660a10(pCurrentEntry, *(int*)(pCurrentEntry - 4), 0, buffer + 0x10);
        if (ret != 0) {
            return ret;
        }
        
        // Pointers to expected input and stored hash within the entry structure
        pExpectedInput = pCurrentEntry + 0x20; // +0x20: 16 bytes of expected input
        pExpectedHash  = pCurrentEntry + 0x30; // +0x30: 16 bytes of expected hash
        
        // Compute hash: first stage (init/update)
        FUN_00661210(hashOutput, buffer + 0x10);
        // Second stage (finalize)
        FUN_00661810(hashOutput, buffer, buffer + 0x10);
        
        // Compare computed hash (16 bytes) with stored hash
        remainingBytes = 0x10;
        {
            byte *pComputed = hashOutput;
            byte *pStored = pExpectedHash;
            do {
                if (*(int*)pComputed != *(int*)pStored) goto hashMismatch;
                remainingBytes -= 4;
                pComputed += 4;
                pStored += 4;
            } while (remainingBytes > 3);
            if (remainingBytes == 0) goto hashesEqual;
        }
        
    hashMismatch:
        cmpResult = *pComputed - *pStored;
        if (cmpResult == 0) {
            if (remainingBytes == 1) goto hashesEqual;
            cmpResult = pComputed[1] - pStored[1];
            if (cmpResult == 0) {
                if (remainingBytes == 2) goto hashesEqual;
                cmpResult = pComputed[2] - pStored[2];
                if (cmpResult == 0) {
                    if (remainingBytes == 3) goto hashesEqual;
                    cmpResult = pComputed[3] - pStored[3];
                    if (cmpResult == 0) goto hashesEqual;
                }
            }
        }
        if (cmpResult < 0) cmpResult = -1;
        else cmpResult = 1;
        if (cmpResult != 0) {
            return 5; // Hash verification failed
        }
        
    hashesEqual:
        // Compare first 16 bytes of buffer (input data) with expected input
        remainingBytes = 0x10;
        {
            byte *pBuffer = buffer;
            byte *pExpected = pExpectedInput;
            do {
                if (*(int*)pBuffer != *(int*)pExpected) goto inputMismatch;
                remainingBytes -= 4;
                pBuffer += 4;
                pExpected += 4;
            } while (remainingBytes > 3);
            if (remainingBytes == 0) goto inputsEqual;
        }
        
    inputMismatch:
        cmpResult = *pBuffer - *pExpected;
        if (cmpResult == 0) {
            if (remainingBytes == 1) goto inputsEqual;
            cmpResult = pBuffer[1] - pExpected[1];
            if (cmpResult == 0) {
                if (remainingBytes == 2) goto inputsEqual;
                cmpResult = pBuffer[2] - pExpected[2];
                if (cmpResult == 0) {
                    if (remainingBytes == 3) goto inputsEqual;
                    cmpResult = pBuffer[3] - pExpected[3];
                    if (cmpResult == 0) goto inputsEqual;
                }
            }
        }
        if (cmpResult < 0) cmpResult = -1;
        else cmpResult = 1;
        if (cmpResult != 0) {
            return 5; // Input data verification failed
        }
        
    inputsEqual:
        // Clear hash output for stress test
        memset(hashOutput, 0, sizeof(hashOutput));
        
        // Stress test: run first hash stage 1000 times
        for (int i = 0; i < 1000; i++) {
            FUN_00661210(hashOutput, buffer + 0x10);
        }
        // Stress test: run second hash stage 1000 times
        for (int i = 0; i < 1000; i++) {
            FUN_00661810(hashOutput, hashOutput, buffer + 0x10);
        }
        
        // Verify hashOutput is still all-zero after stress test
        for (int i = 0; i < 0x10; i++) {
            if (hashOutput[i] != 0) {
                return 5; // Stress test failed: hash functions produced non-zero output
            }
        }
        
        // Advance to next entry (each entry is 0x44 bytes)
        pCurrentEntry += 0x44;
    } while (pCurrentEntry <= (byte*)0x00e43937);
    
    return 0; // All tests passed
}