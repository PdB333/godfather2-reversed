// FUNC_NAME: EARS::StreamManager::readStreamData
void __thiscall StreamManager::readStreamData(int this, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 local_c0 [12];
  undefined4 local_b4;
  undefined4 local_a4;
  undefined4 local_94;
  undefined8 local_90;
  undefined4 local_88;
  undefined4 local_84;
  
  // Begin reading stream data
  FUN_0043aff0(param_2,0xb390b11a);
  FUN_0043af00(1);
  cVar1 = FUN_0043b120();
  if (cVar1 == '\0') {
    puVar4 = local_c0;
    local_b4 = 0;
    local_a4 = 0;
    local_94 = 0;
    local_84 = _DAT_00d5780c;
    FUN_0043b210(puVar4);
    FUN_0043ac60(puVar4);
    *(undefined8 *)(this + 0xb4) = local_90;
    *(undefined4 *)(this + 0xbc) = local_88;
  }
  FUN_0043aff0(param_2,0x5e254a6d);
  cVar1 = FUN_0043b120();
  do {
    if (cVar1 != '\0') {
      return;
    }
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      iVar3 = this + 0x54;
      goto LAB_00908dc8;
    case 1:
      iVar3 = this + 100;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 2:
      iVar3 = this + 0x74;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 3:
      iVar3 = this + 0x84;
LAB_00908dc8:
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 4:
      iVar3 = this + 0x94;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 5:
      iVar3 = this + 0xa4;
      FUN_0043b210(iVar3);
      FUN_0043ad10(iVar3);
      break;
    case 6:
      iVar3 = FUN_0043b210();
      *(undefined4 *)(this + 0xc0) = *(undefined4 *)(iVar3 + 8);
      break;
    case 7:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_00408980(this + 0xc4,uVar2);
      break;
    case 8:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0xcc,uVar2);
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  } while( true );
}