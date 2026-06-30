// FUNC_NAME: ConsoleCommandHandler::dispatchCommand
void ConsoleCommandHandler::dispatchCommand(undefined4 *param_1)

{
  code *pcVar1;
  char *in_EAX;
  int iVar2;
  undefined1 local_c [12];
  
  if (*in_EAX == '\n') {
    iVar2 = (int)*(short *)(in_EAX + 2);
    if (((-1 < iVar2) && (iVar2 < DAT_01205574)) &&
       (pcVar1 = *(code **)(DAT_01205570 + 4 + iVar2 * 0xc), pcVar1 != (code *)0x0)) {
      (*pcVar1)(*param_1,iVar2,local_c);
    }
    return;
  }
  return;
}