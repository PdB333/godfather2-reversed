// FUNC_NAME: NetSession::advanceSequenceNumber
undefined4 __thiscall NetSession::advanceSequenceNumber(int *this, uint maxSequence, uint *sequence, uint increment, undefined4 *param5, undefined4 *param6)
{
  undefined4 result;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  if (1 < maxSequence) {
    if (*sequence == 0xffffffff) {
      *sequence = 0;
    }
    else {
      if ((int)increment < 0) {
        // Handle negative increment by wrapping around
        increment = maxSequence - ((increment ^ (int)increment >> 0x1f) - ((int)increment >> 0x1f)) % maxSequence;
      }
      *sequence = (increment + *sequence) % maxSequence;
    }
    local_c = *param5;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);  // Likely some logging or debug output
    result = (**(code **)(*this + 0x9c))();  // Virtual call at +0x9c
    FUN_0097b8e0(result);  // Another helper function
    return 1;
  }
  if (maxSequence == 0) {
    local_c = *param6;
    local_8 = 0;
    local_4 = 0;
    FUN_00408a00(&local_c,0);  // Logging for zero max sequence case
  }
  return 0;
}