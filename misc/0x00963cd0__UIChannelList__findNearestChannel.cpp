// FUNC_NAME: UIChannelList::findNearestChannel
uint __fastcall UIChannelList::findNearestChannel(int param_1)
{
  uint count;
  uint idx2;
  uint idx;
  
  // param_1+4 likely contains number of populated channels
  // param_1+8 likely channel count/capacity
  // param_1+0xc is the target frequency value to find
  count = *(int *)(param_1 + 4) + 2;
  idx = 0;
  if (*(uint *)(param_1 + 8) < count) {
    count = *(uint *)(param_1 + 8);
  }
  
  // These globals appear to be the channel frequency table and a bitmask
  // DAT_010c2680: float array of channel frequencies
  // DAT_010c2678: bitmask or index mask
  // DAT_012054b4: persistent search index (likely storing last searched channel index)
  idx2 = DAT_012054b4;
  if (3 < (int)count) {
    // Process in batches of 4 channels for performance
    do {
      if (*(float *)(param_1 + 0xc) < *(float *)(&DAT_010c2680 + (DAT_010c2678 & idx2) * 4) ||
          *(float *)(param_1 + 0xc) == *(float *)(&DAT_010c2680 + (DAT_010c2678 & idx2) * 4)) {
        DAT_012054b4 = idx2 + 1;
        return idx;
      }
      DAT_012054b4 = idx2 + 2;
      if (*(float *)(param_1 + 0xc) < *(float *)(&DAT_010c2680 + (DAT_010c2678 & idx2 + 1) * 4) ||
          *(float *)(param_1 + 0xc) == *(float *)(&DAT_010c2680 + (DAT_010c2678 & idx2 + 1) * 4)) {
        return idx + 1;
      }
      DAT_012054b4 = idx2 + 3;
      if (*(float *)(param_1 + 0xc) < *(float *)(&DAT_010c2680 + (DAT_010c2678 & idx2 + 2) * 4) ||
          *(float *)(param_1 + 0xc) == *(float *)(&DAT_010c2680 + (DAT_010c2678 & idx2 + 2) * 4)) {
        return idx + 2;
      }
      idx2 = idx2 + 4;
      if (*(float *)(param_1 + 0xc) < *(float *)(&DAT_010c2680 + (DAT_010c2678 & DAT_012054b4) * 4)
          || *(float *)(param_1 + 0xc) ==
             *(float *)(&DAT_010c2680 + (DAT_010c2678 & DAT_012054b4) * 4)) {
        DAT_012054b4 = idx2;
        return idx + 3;
      }
      idx = idx + 4;
      DAT_012054b4 = idx2;
    } while (idx < count - 3);
  }
  // Process remaining channels (1-3)
  if (idx < count) {
    while( true ) {
      idx2 = DAT_010c2678 & DAT_012054b4;
      DAT_012054b4 = DAT_012054b4 + 1;
      if (*(float *)(param_1 + 0xc) < *(float *)(&DAT_010c2680 + idx2 * 4) ||
          *(float *)(param_1 + 0xc) == *(float *)(&DAT_010c2680 + idx2 * 4)) break;
      idx = idx + 1;
      if (count <= idx) {
        return idx;
      }
    }
  }
  return idx;
}