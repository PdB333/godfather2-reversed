// FUNC_NAME: NetConnection::checkAndUpdateAckState
void __fastcall NetConnection::checkAndUpdateAckState(int thisPtr)
{
  int *piVar1;
  char cVar2;
  
  cVar2 = FUN_004b1730(*(undefined4 *)(thisPtr + 0x144));
  if (cVar2 == '\0') {
    piVar1 = (int *)(thisPtr + 0x134);
    FUN_004b18a0(*(undefined4 *)(thisPtr + 0x144),piVar1,1);
    FUN_004b1720((undefined4 *)(thisPtr + 0x144));
    if (((((*piVar1 != 0) || (*(int *)(thisPtr + 0x138) != 0)) || (*(int *)(thisPtr + 0x13c) != 0))
        || (*(int *)(thisPtr + 0x140) != 0)) &&
       (((*piVar1 != -0x45245246 || (*(int *)(thisPtr + 0x138) != -0x41104111)) ||
        ((*(int *)(thisPtr + 0x13c) != -0x153ea5ab || (*(int *)(thisPtr + 0x140) != -0x6eeff6ef)))))
       ) {
      *(uint *)(thisPtr + 0x118) = *(uint *)(thisPtr + 0x118) & 0xfffff8ff | 0x80;
    }
  }
  return;
}