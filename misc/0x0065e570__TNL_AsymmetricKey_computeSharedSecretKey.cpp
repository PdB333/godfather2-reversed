// Xbox PDB: TNL::AsymmetricKey::computeSharedSecretKey
// FUNC_NAME: CryptoManager::generateSecretSubKey
void CryptoManager::generateSecretSubKey(int this, undefined4 *outKey, int inputData)
{
  undefined4 *keyBuffer;
  void *allocatedBuffer;
  undefined4 *keyPtr;
  longlong timerStart;
  longlong timerEnd;
  undefined4 hashSize [3];
  undefined1 hashBuffer [32];
  undefined1 keyData [208];
  
  if ((*(int *)(inputData + 0x10) == *(int *)(this + 0x10)) && (*(char *)(this + 0x14) != '\0'))
  {
    hashSize[0] = 0x800; // SHA-512 hash size in bits
    timerStart = getTimer(); // FUN_0065c340
    computeHash(*(undefined4 *)(this + 0xc), // +0x0c: secret key
                *(undefined4 *)(inputData + 0xc), // +0x0c: input data
                &DAT_01204978, // global hash context
                hashSize);
    timerEnd = getTimer(); // FUN_0065c340
    recordTiming(timerEnd - timerStart); // FUN_0065c4a0
    logMessage("Timer: %s Elapsed: %g ms","secretSubKeyGen",in_XMM0_Qa); // FUN_0065bc40
    
    // Initialize key derivation buffer
    initKeyDerivation(keyData); // FUN_006595c0
    updateKeyDerivation(keyData, &DAT_01204978); // FUN_00659640
    finalizeKeyDerivation(keyData); // FUN_00659730
    
    // Allocate and populate output key buffer
    keyBuffer = (undefined4 *)allocateMemory(0x18); // FUN_009c8e50
    keyPtr = (undefined4 *)0x0;
    if (keyBuffer != (undefined4 *)0x0) {
      keyBuffer[1] = 0; // reference count
      keyBuffer[2] = 0; // size
      *keyBuffer = &PTR_LAB_00e42d64; // vtable pointer
      keyBuffer[4] = 0x20; // 32 bytes key length
      keyBuffer[3] = hashBuffer; // pointer to hash data
      *(undefined1 *)(keyBuffer + 5) = 0; // owns buffer flag = false
      keyPtr = keyBuffer;
    }
    // If buffer doesn't own the data, allocate and copy
    if (*(char *)(keyPtr + 5) == '\0') {
      allocatedBuffer = (void *)(*(code *)PTR__malloc_00f0cd88)(); // malloc
      _memcpy(allocatedBuffer,(void *)keyPtr[3],keyPtr[4]);
      keyPtr[3] = allocatedBuffer;
      *(undefined1 *)(keyPtr + 5) = 1; // owns buffer flag = true
    }
    keyPtr[2] = keyPtr[2] + 1; // increment reference count
    *outKey = keyPtr;
    return;
  }
  *outKey = 0;
  return;
}