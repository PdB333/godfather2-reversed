// FUNC_NAME: Sentient::handleAction
uint __thiscall Sentient::handleAction(int param2, int param3, int actionId, int param5) {
  uint uVar1;
  uint result;

  if (actionId != 10) {
    if (actionId != 11) {
      // Delegate to generic handler for other actions
      return func_004ac640(param2, param3, actionId, param5);
    }
    // Action 11: possibly release/cancel
    return func_00481640();
  }

  // Action 10: specific interaction/use action
  result = 0;
  // Check two flags at +0x80 and +0x90 (bool, possibly m_canInteract and m_isInRange)
  if (m_flagA && m_flagB) {
    byte highPart = 0;
    // Check bit 0 of m_flags (+0x58) — maybe m_actionEnabled
    if (m_flags & 1) {
      uVar1 = func_0045f120();  // e.g., checkActionAvailability()
      // Condition: first function returns 0 and second function returns value equal to m_someId (+0x5c)
      if ((char)uVar1 == 0) {
        uVar1 = func_0045eea0();  // e.g., getCurrentActionId()
        if (m_someId == uVar1) {
          goto returnClearedLowByte;
        }
      }
      highPart = (byte)(uVar1 >> 8);
    }
    // Return (highPart << 8) | 1;  // sets low byte to 1
    return (uVar1 & 0xFFFFFF00) | 1;
  }
  return result;

returnClearedLowByte:
  // Return uVar1 with low byte cleared (preserves high 24 bits)
  return uVar1 & 0xFFFFFF00;
}