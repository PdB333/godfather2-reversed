// FUNC_NAME: NetSession::setSessionKey
void NetSession::setSessionKey(void)
{
  // +0x0: session key (16 bytes)
  // +0x10: session key continuation (16 bytes)
  // DAT_0121b910 and DAT_0121b920 are the session key storage (32 bytes total)
  // DAT_012058e8: current session pointer
  // DAT_0121b740: expected session pointer
  // DAT_0121b754: session state field
  // DAT_0121bbcc: some session data pointer
  // DAT_0121bb88: another session data pointer

  if (in_EAX == (undefined1 (*) [16])0x0) {
    // Clear session key if null passed
    _DAT_0121b910 = (undefined1  [16])0x0;
    _DAT_0121b920 = (undefined1  [16])0x0;
  }
  else {
    // Copy 32-byte session key from input
    _DAT_0121b910 = *in_EAX;
    _DAT_0121b920 = in_EAX[1];
  }

  // If current session matches expected session and state is valid, 
  // send session key to network layer
  if ((DAT_012058e8 == &DAT_0121b740) && (DAT_0121b754 == DAT_0121bbcc)) {
    FUN_0060ab00(DAT_0121bbcc, DAT_0121bb88, &DAT_0121b910, 8);
  }
}