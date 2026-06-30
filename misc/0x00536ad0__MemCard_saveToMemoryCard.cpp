// FUNC_NAME: MemCard_saveToMemoryCard
void MemCard_saveToMemoryCard(void)

{
  undefined8 *in_EAX;
  
  _DAT_0121a2d0 = *in_EAX;
  _DAT_0121a2d8 = in_EAX[1];
  _DAT_0121a2e0 = in_EAX[2];
  _DAT_0121a2e8 = in_EAX[3];
  if (DAT_012058e8 == &DAT_0121a1f0) {
    if (DAT_0121a200 == DAT_0121a350) {
      FUN_0060ab00(DAT_0121a200,DAT_0121a320,&DAT_0121a2d0,8);
      return;
    }
    if (DAT_0121a200 == DAT_0121a364) {
      FUN_0060ab00(DAT_0121a200,DAT_0121a324,&DAT_0121a2d0,8);
    }
  }
  return;
}