// FUNC_NAME: InputManager::countActiveButtons
void InputManager::countActiveButtons(int *pButtonA, int *pButtonB, int *pButtonX, int *pButtonY)
{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  uint uVar6;
  
  if ((**(int **)(DAT_012233a0 + 4) == 0) || (**(int **)(DAT_012233a0 + 4) == 0x1f30)) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_0043b870(DAT_01130fa0); // getControllerManager?
  }
  uVar6 = 0;
  if (*(int *)(iVar2 + 0x2c) != 0) { // +0x2c = numControllers?
    do {
      cVar1 = FUN_006b19e0(*(undefined4 *)(*(int *)(*(int *)(iVar2 + 0x28) + uVar6 * 4) + 0x28)); // isControllerConnected?
      if ((cVar1 != '\0') && (iVar3 = FUN_007351c0(), iVar3 != 0)) { // isActive?
        uVar4 = FUN_00791750(); // getActiveButton?
        switch(uVar4) {
        case 1:
        case 2:
          piVar5 = pButtonY; // button 1/2 -> Y
          break;
        case 3:
          piVar5 = pButtonX; // button 3 -> X
          break;
        case 4:
          piVar5 = pButtonB; // button 4 -> B
          break;
        case 5:
          piVar5 = pButtonA; // button 5 -> A
          break;
        default:
          goto switchD_009925ff_default;
        }
        *piVar5 = *piVar5 + 1;
      }
switchD_009925ff_default:
      uVar6 = uVar6 + 1;
    } while (uVar6 < *(uint *)(iVar2 + 0x2c));
  }
  return;
}