// FUNC_NAME: EARSObject::resumeProcessing
void __fastcall EARSObject::resumeProcessing(EARSObject *this)
{
  // +0x31: byte flags? Bit 1 (0x02) likely "suspended" flag
  if ((this->field_0x31 & 2) == 0) {
    // If not suspended, call some initialization/reset function
    FUN_004df650();
  }

  // +0x80: pointer to a sub-object (e.g., timer, state machine)
  int *pSubObj = this->field_0x80;
  if (pSubObj != 0) {
    // Clear bits 0 and 31 of sub-object's flags at +0x0C
    pSubObj[3] &= 0x7FFFFFFE;  // +0x0C: flags (bit 0 = paused? bit 31 = ?)

    // Check bit 17 (0x20000) - if not active, set it and trigger update
    if ((pSubObj[3] & 0x20000) == 0) {
      pSubObj[3] |= 0x20000;   // Set active bit
      FUN_0051b120();          // Likely triggers update/resume processing
    }

    // Clear bit 18 (0x40000) - might be a "stop" flag
    pSubObj[3] &= 0xFFFBFFFF;

    // +0x08: pointer to a callback or linked list node
    int *pCallback = pSubObj[2];
    if (pCallback != 0) {
      *pCallback = 0;  // Clear callback reference
      pSubObj[2] = 0;  // Nullify pointer
    }
  }
}