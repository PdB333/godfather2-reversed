// FUNC_NAME: StreamManager::processStreamCommands
void __thiscall StreamManager::processStreamCommands(int thisPtr, undefined4 param_2)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  FUN_0043b540(param_2);  // stream command init
  FUN_0043aff0(param_2,0xb5ece86c);  // set command type
  cVar1 = FUN_0043b120();  // check if stream is done
  do {
    if (cVar1 != '\0') {
      return;
    }
    FUN_0043b210();  // get next command
    iVar2 = FUN_0043ab70();  // get command ID
    if (iVar2 == 0) {
      FUN_0043b210();  // get command data
      uVar3 = FUN_0043ab90();  // get command parameter
      iVar2 = thisPtr + 0x58;  // +0x58: stream buffer pointer
LAB_0090618c:
      FUN_00408980(iVar2,uVar3);  // process stream command
    }
    else {
      if (iVar2 == 1) {
        FUN_0043b210();  // get command data
        uVar3 = FUN_0043ab90();  // get command parameter
        iVar2 = thisPtr + 0x60;  // +0x60: secondary stream buffer pointer
        goto LAB_0090618c;
      }
      if (iVar2 == 2) {
        iVar2 = FUN_0043b210();  // get command data
        *(undefined4 *)(thisPtr + 0x54) = *(undefined4 *)(iVar2 + 8);  // +0x54: stream state/flag
      }
    }
    FUN_0043b1a0();  // advance stream position
    cVar1 = FUN_0043b120();  // check if stream is done
  } while( true );
}