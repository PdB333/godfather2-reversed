// FUNC_NAME: InputManager::initializeControllerSlots
void InputManager::initializeControllerSlots(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *unaff_ESI;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  FUN_00570a70();
  *unaff_ESI = &PTR_FUN_00e3ac08;
  unaff_ESI[0xb9] = param_1; // +0x2E4: numControllerSlots
  unaff_ESI[0xba] = 0; // +0x2E8: currentControllerIndex
  unaff_ESI[0xbc] = 0; // +0x2F0: someFlag
  unaff_ESI[0xb8] = 0xffffffff; // +0x2E0: activeControllerMask
  unaff_ESI[0xbe] = 0xffffffff; // +0x2F8: lastActiveControllerMask
  unaff_ESI[0xc2] = 0xffffffff; // +0x308: someMask
  unaff_ESI[0xc4] = 0xffffffff; // +0x310: anotherMask
  unaff_ESI[0xbf] = 0; // +0x2FC: flags
  unaff_ESI[0xc0] = 0; // +0x300: flags2
  unaff_ESI[0xc1] = 0; // +0x304: flags3
  unaff_ESI[0xc3] = 0; // +0x30C: flags4
  unaff_ESI[0xc5] = 0; // +0x314: flags5
  unaff_ESI[0xc6] = 0; // +0x318: flags6
  unaff_ESI[199] = 0; // +0x31C: flags7
  unaff_ESI[0xc9] = 0; // +0x324: flags8
  unaff_ESI[0xca] = 0; // +0x328: flags9
  unaff_ESI[0xcb] = 0; // +0x32C: flags10
  unaff_ESI[0xcc] = 0; // +0x330: flags11
  unaff_ESI[0xcd] = 0; // +0x334: flags12
  unaff_ESI[0xce] = 0; // +0x338: flags13
  unaff_ESI[0xcf] = 0; // +0x33C: flags14
  unaff_ESI[0xd0] = 0; // +0x340: flags15
  unaff_ESI[0xbd] = 4; // +0x2F4: controllerType (XInput)
  unaff_ESI[200] = 0x20; // +0x320: maxControllers (32)
  unaff_ESI[0xd2] = 0xffffffff; // +0x348: someId
  unaff_ESI[0xd6] = 0xffffffff; // +0x358: anotherId
  unaff_ESI[0xd8] = 0xffffffff; // +0x360: yetAnotherId
  unaff_ESI[0xdc] = 0x20; // +0x370: bufferSize (32)
  puVar1 = DAT_0120556c;
  unaff_ESI[0xd1] = 4; // +0x344: someSize
  unaff_ESI[0xd3] = 0; // +0x34C: flags16
  unaff_ESI[0xd4] = 0; // +0x350: flags17
  unaff_ESI[0xd5] = 0; // +0x354: flags18
  unaff_ESI[0xd7] = 0; // +0x35C: flags19
  unaff_ESI[0xd9] = 0; // +0x364: flags20
  unaff_ESI[0xda] = 0; // +0x368: flags21
  unaff_ESI[0xdb] = 0; // +0x36C: flags22
  unaff_ESI[0xdd] = 0; // +0x374: flags23
  unaff_ESI[0xde] = 0; // +0x378: flags24
  unaff_ESI[0xdf] = 0; // +0x37C: flags25
  unaff_ESI[0xe0] = 0; // +0x380: flags26
  unaff_ESI[0xe1] = 0; // +0x384: flags27
  unaff_ESI[0xe2] = 0; // +0x388: flags28
  unaff_ESI[0xe3] = 0; // +0x38C: flags29
  unaff_ESI[0xe4] = 0; // +0x390: flags30
  unaff_ESI[0xe9] = 0; // +0x3A4: flags31
  unaff_ESI[0xea] = 0; // +0x3A8: flags32
  local_c = 2; // alignment
  local_8 = 0x10; // size per slot (0xE0 bytes)
  local_4 = 0; // flags
  uVar2 = (**(code **)*puVar1)(unaff_ESI[0xb9] * 0xe0,&local_c); // allocate memory for controller slots
  iVar3 = 0;
  unaff_ESI[0xbb] = uVar2; // +0x2EC: controllerSlotArray
  if (0 < (int)unaff_ESI[0xb9]) {
    iVar4 = 0;
    do {
      if (unaff_ESI[0xbb] + iVar4 != 0) {
        FUN_00588f80(); // initialize each controller slot
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0xe0;
    } while (iVar3 < (int)unaff_ESI[0xb9]);
  }
  unaff_ESI[0xe5] = 0; // +0x394: someCounter
  uVar2 = DAT_00e39f98;
  unaff_ESI[0xe8] = 0; // +0x3A0: anotherCounter
  unaff_ESI[0xdd] = unaff_ESI + 0xe5; // +0x374: pointer to someCounter
  unaff_ESI[0xe6] = uVar2; // +0x398: someValue
  unaff_ESI[0xe7] = 1; // +0x39C: someFlag
  return;
}