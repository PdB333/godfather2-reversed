// FUNC_NAME: DebugState::printStateMessage
void __thiscall DebugState::printStateMessage(void* this, int messageId)
{
  char buffer1[284]; // local_120
  char buffer2[272]; // local_230
  char buffer3[272]; // local_340
  
  int state = *(int*)((char*)this + 0x24); // +0x24: current state ID
  if (state == 0) {
    char* formatted = formatString0(buffer1, messageId); // FUN_0082f000
    outputString(formatted); // FUN_0082b080
    return;
  }
  if (state != 1) {
    char* formatted = formatString1(buffer2, messageId, 0); // FUN_0082ede0
    outputString(formatted);
    return;
  }
  // state == 1
  char* formatted = formatString1(buffer3, messageId, 0);
  outputString(formatted);
  return;
}