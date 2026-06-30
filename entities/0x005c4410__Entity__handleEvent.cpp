// FUNC_NAME: Entity::handleEvent
void Entity::handleEvent(int param_1, undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar2 = 0;
  iVar1 = DAT_0122206c;
  if (0 < DAT_01222068) {
    do {
      if (param_1 <= *(int *)(iVar1 + 0x10)) {
        iVar1 = FUN_005d48f0();
        if (iVar1 != 0) {
          return;
        }
        break;
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 0x20;
    } while (iVar2 < DAT_01222068);
  }
  local_8 = param_2;
  local_c = 2;
  local_4 = 0;
  (**(code **)**(undefined4 **)(DAT_012234ec + 4))(param_1,&local_c);
  return;
}