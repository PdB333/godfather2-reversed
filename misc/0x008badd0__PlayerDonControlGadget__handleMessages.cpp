// FUNC_NAME: PlayerDonControlGadget::handleMessages
void __thiscall PlayerDonControlGadget::handleMessages(int thisPtr, int *msgBuffer)
{
  int *piVar1;
  uint uVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  float fVar6;
  
  if (*msgBuffer == DAT_012067dc) {
    piVar1 = *(int **)(thisPtr + 0xf4);
    if ((*(uint *)(thisPtr + 0x150) >> 8 & 1) == 0) {
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 0x48))(0x2c2eae66,0);
      }
    }
    else if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x2c))