// FUNC_NAME: MoviePlayer::initialize
void __thiscall MoviePlayer::initialize(int this, undefined4 param_2, uint param_3, undefined4 param_4, undefined4 param_5)
{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  undefined4 *puVar5;
  undefined4 local_70 [2];
  undefined4 local_68 [2];
  undefined4 local_60;
  undefined4 local_58;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined1 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined1 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24;
  undefined4 *local_20;
  undefined4 local_1c;
  undefined1 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c;
  
  // Store parameters
  *(uint *)(this + 0x40) = param_3;  // +0x40: some ID/flag
  *(undefined4 *)(this + 4) = param_2;  // +0x04: first parameter
  *(undefined4 *)(this + 0x44) = param_4;  // +0x44: audio parameter
  *(undefined4 *)(this + 0x48) = param_5;  // +0x48: another parameter
  
  // Initialize audio system with shifted parameter
  FUN_00620040(param_3 >> 4, param_4);
  
  // Determine audio bus based on global flag
  if (*(char *)(DAT_01223454 + 0x15) == '\0') {
    pcVar4 = "MUSIC_UI";
  } else {
    pcVar4 = "MOVIE_PLAYER";
  }
  
  // Get audio bus handle
  uVar2 = FUN_004dafd0(pcVar4);
  *(undefined4 *)(this + 0x3c) = uVar2;  // +0x3c: audio bus handle
  
  // Begin audio setup
  FUN_00c9eac0();
  
  // Check if audio system is initialized
  if (*(int *)(*(int *)(this + 8) + 0x28) == 0) {
    FUN_00ca3ee0();  // Initialize audio system
  }
  
  // Create audio sources for movie playback
  uVar2 = FUN_00caa1c0();
  local_4c = FUN_00c9ceb0(uVar2);
  local_48 = (undefined1)param_4;
  local_50 = 0;
  
  // Create audio source objects with specific IDs
  local_40 = FUN_00c9cd50(0x52636830);  // "Rch0" - audio source
  local_44 = 0;
  local_3c = (undefined1)param_4;
  local_34 = FUN_00c9cd50(0x52737030);  // "Rsp0" - audio source
  local_38 = 0;
  local_30 = (undefined1)param_4;
  local_28 = FUN_00c9cd50(0x47614630);  // "Gaf0" - audio source
  local_24 = (undefined1)param_4;
  local_2c = 0;
  local_1c = FUN_00c9cd50(0x506e3231);  // "Pn21" - audio source
  
  // Set up audio source list
  puVar5 = local_68;
  uVar2 = FUN_00c9cd50(0x506e3231);
  FUN_00c9cba0(*(undefined4 *)(this + 8), uVar2, puVar5);
  
  local_58 = 0;
  local_20 = local_68;
  local_68[0] = DAT_0110ae38;
  local_60 = DAT_00e44720;
  local_18 = 6;
  local_10 = FUN_00c9cd50(0x53656e30);  // "Sen0" - audio source
  local_14 = 0;
  local_c = 6;
  
  // Create audio channel for movie
  iVar3 = FUN_00ca55a0(*(undefined4 *)(this + 8), 0, 6, &local_50, 0);
  *(int *)(this + 0x9c) = iVar3;  // +0x9c: audio channel handle
  *(char **)(iVar3 + 0x14) = "RWMovie Voice";
  
  // Set up audio output
  iVar3 = *(int *)(this + 0x9c);
  FUN_00c9cbe0(*(undefined4 *)(this + 8), local_10, 0, local_70);
  local_70[0] = FUN_00c9ebd0();
  FUN_00c9cd40(0, local_70);
  
  // Store audio channel properties
  *(undefined4 *)(this + 0xa8) = *(undefined4 *)(iVar3 + 0x58);  // +0xa8: audio channel property
  *(undefined4 *)(this + 0xa0) = *(undefined4 *)(iVar3 + 0x50);  // +0xa0: audio channel property
  *(undefined4 *)(this + 0xa4) = *(undefined4 *)(iVar3 + 0x5c);  // +0xa4: audio channel property
  iVar1 = *(int *)(iVar3 + 0x60);
  *(int *)(this + 0xac) = iVar1;  // +0xac: audio channel property
  *(undefined4 *)(this + 0xb0) = *(undefined4 *)(iVar3 + 100);  // +0xb0: audio channel property
  
  // Enable audio if channel exists
  if (iVar1 != 0) {
    FUN_00ca4e90(1, 0);
  }
  
  // Finalize audio setup
  FUN_00c9eae0();
  
  return;
}