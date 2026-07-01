// FUNC_NAME: NetSession::getSessionState
undefined4 * __thiscall NetSession::getSessionState(void *this, undefined4 *outState)
{
  undefined4 constantValue;
  int result;
  int state;
  undefined4 *source;
  undefined4 *dest;
  
  // Initialize first few fields to 0 and set field 0xF to global constant
  outState[3] = 0;
  outState[7] = 0;
  outState[0xb] = 0;
  outState[0xf] = _DAT_00d5780c;  // global constant (likely invalid/handshake value)
  
  result = FUN_006b07e0(*(undefined4 *)((int)this + 0x58)); // from connection pointer?
  if ((result == 0) || (*(int *)((int)this + 0x5c) == 5)) {
    // No valid match or state == 5 (e.g. disconnected)
    state = FUN_006b0ee0(*(undefined4 *)((int)this + 0x58)); // get default state
    constantValue = _DAT_00d5780c;
    outState[0xf] = _DAT_00d5780c;
    outState[10] = constantValue;
    outState[5] = constantValue;
    *outState = constantValue;
    outState[0xe] = 0;
    outState[0xd] = 0;
    outState[0xc] = 0;
    outState[3] = 0;
    outState[4] = 0;
    outState[2] = 0;
    outState[1] = 0;
    outState[7] = 0;
    outState[9] = 0;
    outState[8] = 0;
    outState[6] = 0;
    outState[0xb] = 0;
    // Copy three fields from the default state object
    outState[0xc] = *(undefined4 *)(state + 0x1c);
    outState[0xd] = *(undefined4 *)(state + 0x20);
    outState[0xe] = *(undefined4 *)(state + 0x24);
  }
  else {
    state = FUN_006aecd0(*(int *)((int)this + 0x5c)); // get state ID
    if (state != 0) {
      source = (undefined4 *)FUN_00471610(); // get a static template buffer
      dest = outState;
      for (int i = 0x10; i != 0; i--, dest++, source++) {
        *dest = *source; // copy 16 dwords from template
      }
      return outState;
    }
  }
  return outState;
}