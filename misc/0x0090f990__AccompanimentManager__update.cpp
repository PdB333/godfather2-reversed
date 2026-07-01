// FUNC_NAME: AccompanimentManager::update
void __fastcall AccompanimentManager::update(int *this)
{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int local_84;
  undefined4 local_80;
  int local_7c;
  uint local_78;
  undefined4 *local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined1 local_60[16];
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  // Check global flag at +0x10 bit 2
  if ((*(uint *)(DAT_011298d4 + 0x10) >> 2 & 1) == 0) {
    *(uint *)(DAT_011298d4 + 0x10) = *(uint *)(DAT_011298d4 + 0x10) | 4;
    *(undefined1 *)(this + 0x23) = 1; // +0x8C flag set
  }
  else {
    *(undefined1 *)(this + 0x23) = 0; // +0x8C flag cleared
  }
  
  // State machine based on this[0x14] (+0x50)
  switch(this[0x14]) {
  case 1:
    FUN_0090f3c0(); // AccompanimentState::idle
    break;
  case 2:
    FUN_0090f520(); // AccompanimentState::following
    break;
  case 3:
    FUN_0090f690(); // AccompanimentState::waiting
    break;
  case 4:
    FUN_0090edb0(); // AccompanimentState::arrived
    break;
  case 5:
    FUN_0090f240(); // AccompanimentState::leaving
    break;
  case 6:
    FUN_0090f820(); // AccompanimentState::combat
  }
  
  // Get camera matrix from global camera manager
  local_7c = FUN_004262f0(0); // CameraManager::getCamera(0)
  local_50 = *(undefined4 *)(local_7c + 0x40);
  uStack_4c = *(undefined4 *)(local_7c + 0x44);
  uStack_48 = *(undefined4 *)(local_7c + 0x48);
  uStack_44 = *(undefined4 *)(local_7c + 0x4c);
  local_40 = *(undefined4 *)(local_7c + 0x50);
  uStack_3c = *(undefined4 *)(local_7c + 0x54);
  uStack_38 = *(undefined4 *)(local_7c + 0x58);
  uStack_34 = *(undefined4 *)(local_7c + 0x5c);
  local_30 = *(undefined4 *)(local_7c + 0x60);
  uStack_2c = *(undefined4 *)(local_7c + 100);
  uStack_28 = *(undefined4 *)(local_7c + 0x68);
  uStack_24 = *(undefined4 *)(local_7c + 0x6c);
  local_20 = *(undefined4 *)(local_7c + 0x70);
  uStack_1c = *(undefined4 *)(local_7c + 0x74);
  uStack_18 = *(undefined4 *)(local_7c + 0x78);
  uStack_14 = *(undefined4 *)(local_7c + 0x7c);
  
  local_70 = 0;
  local_6c = 0;
  local_68 = 0;
  local_74 = &local_70;
  local_64 = _DAT_00d5780c;
  local_78 = 0xffffffff;
  local_80 = 5;
  
  // Play accompaniment background sound
  FUN_004eacb0("accomp_bg"); // AudioManager::playSound
  
  // Create a new sound handle
  piVar3 = (int *)FUN_004df3c0(&local_84, local_60, &local_50, 0x1ff, 4, &local_80);
  
  // Manage linked list of sound handles at this[0x21] (+0x84)
  piVar1 = this + 0x21;
  if (this[0x21] != 0) {
    *(undefined4 *)(this[0x21] + 8) = 0;
    *piVar1 = 0;
  }
  iVar2 = *piVar3;
  *piVar1 = iVar2;
  if (iVar2 != 0) {
    *(int **)(iVar2 + 8) = piVar1;
    *piVar3 = 0;
  }
  if (local_84 != 0) {
    *(undefined4 *)(local_84 + 8) = 0;
  }
  
  // Call virtual function at vtable+0xC (likely update)
  (**(code **)(*this + 0xc))();
  
  // Set timer to 4000ms
  this[0x22] = 4000; // +0x88
  
  // Set up callback
  FUN_005c0d50(this + 5, &LAB_0090f3a0, 0); // TimerManager::setTimer
  
  local_80 = DAT_01130468;
  local_7c = 0;
  local_78 = local_78 & 0xffffff00;
  FUN_00408a00(&local_80, 0);
  
  return;
}