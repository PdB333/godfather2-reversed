// FUNC_NAME: LuaBinding::readAndApplyLuaTable
void __thiscall LuaBinding::readAndApplyLuaTable(int this, undefined4 param_2)
{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  FUN_0046c710(param_2);
  FUN_0043aff0(param_2,0x5fef7f11);
  cVar1 = FUN_0043b120();
  do {
    if (cVar1 != '\0') {
      if (((((*(int *)(this + 0x68) == 0) && (*(int *)(this + 0x6c) == 0)) &&
           (*(int *)(this + 0x70) == 0)) && (*(int *)(this + 0x74) == 0)) ||
         (((*(int *)(this + 0x68) == -0x45245246 && (*(int *)(this + 0x6c) == -0x41104111)) &&
          ((*(int *)(this + 0x70) == -0x153ea5ab && (*(int *)(this + 0x74) == -0x6eeff6ef))))))
         ) {
        if (this != 0) {
          FUN_004088c0(this + 0x3c);
          return;
        }
        FUN_004088c0(0);
      }
      return;
    }
    FUN_0043b210();
    uVar2 = FUN_0043ab70();
    switch(uVar2) {
    case 0:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      FUN_004089b0(this + 0x50,uVar2);
      break;
    case 1:
      FUN_0043b210();
      puVar3 = (undefined4 *)FUN_0043abc0();
      *(undefined4 *)(this + 0x68) = *puVar3;
      *(undefined4 *)(this + 0x6c) = puVar3[1];
      *(undefined4 *)(this + 0x70) = puVar3[2];
      *(undefined4 *)(this + 0x74) = puVar3[3];
      break;
    case 2:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar4 = this + 0x58;
      goto LAB_00901be5;
    case 3:
      FUN_0043b210();
      uVar2 = FUN_0043ab90();
      iVar4 = this + 0x60;
LAB_00901be5:
      FUN_00408980(iVar4,uVar2);
    }
    FUN_0043b1a0();
    cVar1 = FUN_0043b120();
  } while( true );
}