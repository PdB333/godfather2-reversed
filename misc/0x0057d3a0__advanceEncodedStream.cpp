// FUNC_NAME: advanceEncodedStream
void advanceEncodedStream(unsigned char **ppStream)
{
  unsigned char *pStream = *ppStream;
  unsigned char firstByte = *pStream;
  unsigned char highNibble = firstByte >> 4;           // initialNibble
  unsigned char code = firstByte & 0xF;                // code 0-15
  unsigned int combinedValue = (pStream[1] << 4) | highNibble; // combined from second byte + high nibble

  // If code != 5: simple skip using offset and base tables indexed by code
  if (code != 5)
  {
    // Tables at 0x00e2be68 (offsets) and 0x00e2be30 (bases) - each enty 4 bytes
    *ppStream = pStream + 
                ( *(int *)(DAT_00e2be68 + code * 4) * combinedValue ) +
                *(int *)(DAT_00e2be30 + code * 4);
    return;
  }

  // code == 5: tree node traversal
  int fullNodeCount = combinedValue >> 2;     // number of complete node groups
  unsigned int partialSteps = highNibble & 3; // remaining partial steps (0-3)

  pStream += 2;  // skip the first two bytes already read

  // Process full node groups (each group seems to decode 4 nodes)
  if (fullNodeCount > 0)
  {
    do
    {
      // --- Node 1 ---
      unsigned char nodeCode1 = *pStream & 0xF;
      int nodeOffset1 = ( (pStream[1] << 4) | (*pStream >> 4) ) *
                         *(int *)(DAT_00e2be68 + nodeCode1 * 4) +
                         *(int *)(DAT_00e2be30 + nodeCode1 * 4);

      // --- Node 2 (offset by nodeOffset1) ---
      unsigned char nodeCode2 = pStream[nodeOffset1] & 0xF;
      int nodeOffset2 = ( (pStream[nodeOffset1 + 1] << 4) | (pStream[nodeOffset1] >> 4) ) *
                         *(int *)(DAT_00e2be68 + nodeCode2 * 4) +
                         *(int *)(DAT_00e2be30 + nodeCode2 * 4);
      int nodeSum2 = nodeOffset2 + nodeOffset1;

      // --- Node 3 (offset by nodeSum2) ---
      unsigned char nodeCode3 = pStream[nodeSum2] & 0xF;
      int nodeOffset3 = ( (pStream[nodeSum2 + 1] << 4) | (pStream[nodeSum2] >> 4) ) *
                         *(int *)(DAT_00e2be68 + nodeCode3 * 4) +
                         *(int *)(DAT_00e2be30 + nodeCode3 * 4);
      int nodeSum3 = nodeOffset3 + nodeSum2;

      // --- Node 4 (offset by nodeSum3) ---
      unsigned char nodeCode4 = pStream[nodeSum3] & 0xF;
      // Final skip for this group: offset from node4 plus nodeSum3
      int finalSkip = nodeSum3 + 
                      ( (pStream[nodeSum3 + 1] << 4) | (pStream[nodeSum3] >> 4) ) *
                      *(int *)(DAT_00e2be68 + nodeCode4 * 4) +
                      *(int *)(DAT_00e2be30 + nodeCode4 * 4);

      pStream += finalSkip;
      fullNodeCount--;
    } while (fullNodeCount > 0);
  }

  // Process remaining partial steps (each step decodes one node)
  if (partialSteps != 0)
  {
    do
    {
      unsigned char nodeCode = *pStream & 0xF;
      int nodeSkip = ( (pStream[1] << 4) | (*pStream >> 4) ) *
                      *(int *)(DAT_00e2be68 + nodeCode * 4) +
                      *(int *)(DAT_00e2be30 + nodeCode * 4);
      pStream += nodeSkip;
      partialSteps--;
    } while (partialSteps > 0);
  }

  *ppStream = pStream;
}