// FUNC_NAME: ObjectManager::removeObjectByType
void __thiscall ObjectManager::removeObjectByType(int this, int typeId)
{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 local_14;
  undefined4 *local_10;
  undefined1 local_c;
  
  puVar1 = *(undefined4 **)(typeId + 8);  // Get type info from typeId
  local_14 = DAT_01222220;
  local_c = 0;
  local_10 = puVar1;
  FUN_00408a00(&local_14,0);  // Likely a lock/mutex acquire
  
  piVar3 = (int *)**(undefined4 **)(this + 0x28);  // Get first object in list
  do {
    if (piVar3 == *(int **)(this + 0x28)) {  // Reached end of list
LAB_005fb275:
      puVar2 = *(undefined4 **)(this + 0x48);  // Get second list
      puVar6 = (undefined4 *)*puVar2;
      do {
        if (puVar6 == puVar2) {  // Reached end of second list
          (**(code **)*puVar1)(0);  // Release lock
          return;
        }
        if (puVar6 == *(undefined4 **)(this + 0x48)) {
          FUN_00b97aea();  // Error handler
        }
        piVar3 = (int *)(**(code **)(*(int *)puVar6[2] + 8))();  // Get object type
        if (piVar3[1] != 0) {
          iVar5 = *piVar3;
          iVar4 = piVar3[1] * 0x10 + iVar5;
          for (; iVar5 != iVar4; iVar5 = iVar5 + 0x10) {
            if (*(undefined4 **)(iVar5 + 4) == puVar1) {  // Check if type matches
              FUN_005fc5f0(0);  // Remove object
              break;
            }
          }
        }
        if (puVar6 == *(undefined4 **)(this + 0x48)) {
          FUN_00b97aea();  // Error handler
        }
        puVar6 = (undefined4 *)*puVar6;  // Next object
      } while( true );
    }
    if (piVar3 == *(int **)(this + 0x28)) {
      FUN_00b97aea();  // Error handler
    }
    if ((undefined4 *)piVar3[2] == puVar1) {  // Check if object type matches
      if ((piVar3 != *(int **)(this + 0x28)) ||
         (FUN_00b97aea(), piVar3 != *(int **)(this + 0x28))) {
        *(int *)piVar3[1] = *piVar3;  // Remove from linked list
        *(int *)(*piVar3 + 4) = piVar3[1];
        (**(code **)(**(int **)(this + 0x10) + 4))(piVar3,0xc);  // Free memory
        *(int *)(this + 0x2c) = *(int *)(this + 0x2c) + -1;  // Decrement count
      }
      goto LAB_005fb275;
    }
    if (piVar3 == *(int **)(this + 0x28)) {
      FUN_00b97aea();  // Error handler
    }
    piVar3 = (int *)*piVar3;  // Next object
  } while( true );
}