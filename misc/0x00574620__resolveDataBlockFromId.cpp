// FUNC_NAME: resolveDataBlockFromId
// Address: 0x00574620
// Role: Retrieves a data block (64 or 16 bytes) based on an ID, with fallback and remap via manager.
// Global pointer g_fallbackData (DAT_0120557c) serves as a default buffer for ID 0 or fallback.
// The manager object (param_2) contains a remap table at +0xB4 (byte array) and a data table at +0xB8 (stride 0x40 = 64 bytes).
// If remap fails (byte == 0xFF), uses g_fallbackData + id * 16.

unsigned int* __fastcall resolveDataBlock(unsigned int* sourceData, void* manager, int* idPtr)
{
  int id = *idPtr;                                      // The ID to resolve
  unsigned int* destBlock;                               // Pointer to a global fallback buffer
  unsigned int* result;

  destBlock = (unsigned int*)DAT_0120557c;               // Global fallback data pointer

  if (id == 0)
  {
    // Copy a 64-byte block from sourceData to the global fallback buffer
    // This sets the default template for ID 0
    destBlock[0]  = sourceData[0];
    destBlock[1]  = sourceData[1];
    destBlock[2]  = sourceData[2];
    destBlock[3]  = sourceData[3];
    destBlock[4]  = sourceData[4];
    destBlock[5]  = sourceData[5];
    destBlock[6]  = sourceData[6];
    destBlock[7]  = sourceData[7];
    destBlock[8]  = sourceData[8];
    destBlock[9]  = sourceData[9];
    destBlock[10] = sourceData[10];
    destBlock[11] = sourceData[11];
    destBlock[12] = sourceData[12];
    destBlock[13] = sourceData[13];
    destBlock[14] = sourceData[14];
    destBlock[15] = sourceData[15];
    return destBlock;
  }

  // If manager has a remap table and the remap byte is not 0xFF, use the remapped index
  if (*(int*)((char*)manager + 0xB4) != 0)              // +0xB4: pointer to remap table
  {
    unsigned int remapIndex = *(unsigned char*)(*(int*)((char*)manager + 0xB4) + id);
    if (remapIndex != 0xFF)
    {
      // Use the remap index to fetch a 64-byte block from the data table at +0xB8
      return (unsigned int*)(remapIndex * 0x40 + *(int*)((char*)manager + 0xB8));
    }
  }

  // Fallback: use 16-byte entries in the global buffer, indexed by id
  return destBlock + id * 4;  // each 16 bytes = 4 dwords
}