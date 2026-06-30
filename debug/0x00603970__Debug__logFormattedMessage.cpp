// FUNC_NAME: Debug::logFormattedMessage
void Debug::logFormattedMessage(int param_1, int param_2)
{
  char buffer[4108]; // 0x1010 bytes
  int formatIndex; // +0x0
  
  formatIndex = 0;
  _memset(buffer, 0, 0x1010);
  FUN_00603610(&formatIndex, param_1, param_2, 0);
  return;
}