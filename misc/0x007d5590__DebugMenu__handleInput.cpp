// FUNC_NAME: DebugMenu::handleInput
undefined1 __thiscall DebugMenu::handleInput(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5, undefined4 param_6)
{
  undefined1 uVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  float10 extraout_ST0;
  
  piVar3 = *(int **)(this + 0x58); // +0x58: pointer to some debug state/context
  uVar1 = 1;
  switch(param_5) {
  case 0x31: // '1' key
    // Handle sub-menu 1
    FUN_007d3f50(param_3);
    FUN_007d4070();
    FUN_007d4110(param_3);
    return 1;
  case 0x32: // '2' key
    // Handle sub-menu 2
    FUN_007d4dd0();
    FUN_007d38f0();
    return 1;
  case 0x33: // '3' key
    // Handle sub-menu 3
    FUN_007d4fb0();
    FUN_007d3a70();
    return 1;
  case 0x34: // '4' key
    // Handle sub-menu 4
    FUN_007d5140();
    return 1;
  case 0x35: // '5' key
    // Toggle some debug flag
    *(uint *)(DAT_01129c4c + 0x5c) = *(uint *)(DAT_01129c4c + 0x5c) & 0xffffdfff;
    return 1;
  case 0x36: // '6' key
    // Handle sub-menu 6
    FUN_00798480();
    return 1;
  case 0x37: // '7' key
    // Handle sub-menu 7 - conditional based on some global
    iVar2 = FUN_007ff880();
    if (iVar2 != 0) {
      piVar3 = (int *)FUN_007ff880();
      (**(code **)(*piVar3 + 0x1a8))(); // Call virtual function at vtable+0x1a8
      if ((float10)DAT_00d5779c < extraout_ST0) {
        FUN_007d52b0();
        return 1;
      }
    }
    break;
  case 0x38: // '8' key
    // Handle sub-menu 8 - calls a virtual function with parameter
    iVar2 = *piVar3;
    uVar4 = FUN_007ff880(0);
    (**(code **)(iVar2 + 0x288))(3, uVar4); // Call virtual function at vtable+0x288
    FUN_007a6700();
    return 1;
  case 0x39: // '9' key
    // Handle sub-menu 9 - stores result in this+0xc4
    uVar1 = FUN_007d3ea0();
    *(undefined1 *)(this + 0xc4) = uVar1;
    return 1;
  case 0x3a: // ':' key
    // Handle sub-menu 10 - conditional based on this+0x9c
    if (*(int *)(this + 0x9c) == 0) {
      FUN_007d4820(piVar3, 0);
      return 1;
    }
    FUN_007d4820(piVar3, *(int *)(this + 0x9c) + -0x48);
    return 1;
  default:
    // Default handler for other keys
    uVar1 = FUN_007abec0(param_2, param_3, param_4, param_5, param_6);
  }
  return uVar1;
}