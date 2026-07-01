// FUNC_NAME: EARS::StreamManager::waitForStreamLoad
void __thiscall StreamManager::waitForStreamLoad(int this, undefined4 streamId)
{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  FUN_0046c710(streamId);
  FUN_0043aff0(streamId,0x647df06b);
  cVar1 = FUN_0043b120();
  while (cVar1 == '\0') {
    FUN_0043b210();
    iVar2 = FUN_0043ab70();
    if ((iVar2 == 0) && (iVar2 = FUN_0043b210(), *(char *)(iVar2 + 8) != '\0')) {
      *(uint *)(this + 0x60) = *(uint *)(this + 0x60) | 0x80000000;
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  }
  FUN_0043aff0(streamId,0xdc51ebb1);
  cVar1 = FUN_0043b120();
  do {
    if (cVar1 != '\0') {
LAB_008cfd96:
      uVar3 = FUN_00445f00(this);
      if (this == 0) {
        this = 0;
      }
      else {
        this = this + 0x3c;
      }
      FUN_004035c0(uVar3,2,this);
      return;
    }
    FUN_0043b210();
    iVar2 = FUN_0043ab70();
    if (iVar2 == 5) {
      FUN_0043b210();
      uVar3 = FUN_0043ab90();
      FUN_00408980(this + 0x50,uVar3);
      goto LAB_008cfd96;
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  } while( true );
}