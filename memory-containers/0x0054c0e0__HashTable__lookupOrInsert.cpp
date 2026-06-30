// FUNC_NAME: HashTable::lookupOrInsert
// Function at 0x0054c0e0: Initializes a hash value with a seed constant (0xfe16702f) and then potentially updates it based on key data.
// param_1: output pointer to store the hash value
// param_2: pointer to a string/object containing data at offset +0x10 (likely a pointer to the string content or a character)
// Returns: the same pointer as param_1

extern undefined4 * hashHelper(undefined4 **, int);

undefined4 * HashTable::lookupOrInsert(undefined4 *outHash, int keyObject)
{
  undefined4 *hashPtr;
  int derivedAddr;
  undefined4 *tempPtr;

  hashPtr = outHash;
  *outHash = 0xfe16702f; // Initial seed/hash value
  if ((keyObject != 0) && (derivedAddr = *(char *)(keyObject + 0x10) + keyObject, derivedAddr != 0)) {
    // keyObject appears to be a structure where offset +0x10 holds a relative offset or a byte used as an index
    tempPtr = (undefined4 *)hashHelper(&outHash, derivedAddr);
    *hashPtr = *tempPtr;
  }
  return hashPtr;
}