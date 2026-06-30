// FUNC_NAME: AudioManager::initAudioState
void __thiscall AudioManager::initAudioState(int this, char *param_2, int param_3, undefined4 *param_4)
{
  uint uVar1;
  uint *puVar2;
  int *piVar3;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar4;
  undefined4 *puVar5;
  bool bVar6;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 local_50 [76];
  
  // Initialize audio state
  FUN_005c5320(this);
  FUN_005c4850();
  FUN_00417560();
  
  iVar4 = *(int *)(param_3 + 4);
  *(undefined4 *)(param_3 + 0xc) = 0;
  
  if (param_4 == (undefined4 *)0x0) {
    // No custom audio parameters - use defaults
    FUN_005c48f0(*(undefined4 *)(iVar4 + 8),*(undefined4 *)(iVar4 + 0xc),
                 *(undefined4 *)(iVar4 + 0x10));
    iVar4 = extraout_ECX_00;
  }
  else {
    // Custom audio parameters provided
    local_60 = *param_4;
    uStack_5c = param_4[1];
    uStack_58 = param_4[2];
    uStack_54 = param_4[3];
    FUN_005c48a0();
    iVar4 = extraout_ECX;
  }
  
  // Store audio state globals
  DAT_0119d990 = *(float *)(iVar4 + 0x58);  // +0x58: masterVolume
  _DAT_0119da20 = *(float *)(iVar4 + 0x40);  // +0x40: sfxVolume
  DAT_0119d994 = *(undefined4 *)(iVar4 + 0x44);  // +0x44: musicVolume
  DAT_0119d9ac = *(undefined4 *)(iVar4 + 0x5c);  // +0x5c: voiceVolume
  
  // Calculate interpolated volume based on param_2 indices
  DAT_0119d9c0 = (*(float *)(PTR_DAT_00f17644 + param_2[1] * 4) * DAT_00e44988 +
                 *(float *)(PTR_DAT_00f17644 + *param_2 * 4) * DAT_00e44984) *
                 (_DAT_0119da20 - DAT_0119d990) + DAT_0119d990;
  
  DAT_0119d9a4 = 0;
  DAT_0119d9bc = 0;
  
  DAT_0119d9f0 = (*(float *)(PTR_DAT_00f17644 + param_2[4] * 4) * DAT_00e44988 +
                 *(float *)(PTR_DAT_00f17644 + param_2[3] * 4) * DAT_00e44984) *
                 (DAT_0119d990 - _DAT_0119da20) + _DAT_0119da20;
  
  // Copy audio parameters to multiple state slots
  DAT_0119d998 = local_60;
  DAT_0119d99c = uStack_5c;
  DAT_0119d9a0 = uStack_58;
  DAT_0119d9b0 = local_60;
  DAT_0119d9b4 = uStack_5c;
  DAT_0119d9b8 = uStack_58;
  DAT_0119d9c8 = local_60;
  DAT_0119d9cc = uStack_5c;
  DAT_0119d9d0 = uStack_58;
  DAT_0119d9d4 = uStack_54;
  DAT_0119d9e0 = local_60;
  DAT_0119d9e4 = uStack_5c;
  DAT_0119d9e8 = uStack_58;
  DAT_0119d9ec = uStack_54;
  DAT_0119d9f8 = local_60;
  DAT_0119d9fc = uStack_5c;
  DAT_0119da00 = uStack_58;
  DAT_0119da04 = uStack_54;
  _DAT_0119da10 = local_60;
  _DAT_0119da14 = uStack_5c;
  _DAT_0119da18 = uStack_58;
  _DAT_0119da1c = uStack_54;
  _DAT_0119da28 = local_60;
  _DAT_0119da2c = uStack_5c;
  _DAT_0119da30 = uStack_58;
  _DAT_0119da34 = 0;
  _DAT_0119da40 = local_60;
  _DAT_0119da44 = uStack_5c;
  _DAT_0119da48 = uStack_58;
  _DAT_0119da4c = 0;
  
  puVar2 = (uint *)(DAT_01206880 + 0x14);
  
  // Set initial state values
  DAT_0119d9a8 = DAT_0119d990;
  DAT_0119d9c4 = DAT_0119d994;
  DAT_0119d9d8 = DAT_0119d9c0;
  DAT_0119d9dc = DAT_0119d9ac;
  DAT_0119d9f4 = DAT_0119d994;
  _DAT_0119da08 = DAT_0119d9f0;
  _DAT_0119da0c = DAT_0119d9ac;
  _DAT_0119da24 = DAT_0119d994;
  _DAT_0119da38 = _DAT_0119da20;
  _DAT_0119da3c = DAT_0119d9ac;
  
  // Write audio state command buffer
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126b40;
  *puVar2 = *puVar2 + 4;
  *(undefined1 *)*puVar2 = 1;
  bVar6 = DAT_012056a8 == 1;
  *puVar2 = *puVar2 + 4 & 0xfffffffc;
  
  uVar1 = DAT_01205684;
  
  if (bVar6) {
    if (1 < DAT_01205684) {
      puVar2 = (uint *)(DAT_01206880 + 0x14);
      **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126c08;
      *puVar2 = *puVar2 + 4;
      *(undefined1 *)*puVar2 = 0;
      *puVar2 = *puVar2 + 4 & 0xfffffffc;
    }
    
    iVar4 = DAT_01206880;
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126bb8;
    *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 4;
    **(undefined4 **)(iVar4 + 0x14) = 8;
    *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 4;
    
    piVar3 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126b18;
    *piVar3 = *piVar3 + 4;
    
    puVar5 = (undefined4 *)(*piVar3 + 3U & 0xfffffffc);
    *piVar3 = (int)puVar5;
    *puVar5 = 1;
    
    puVar5 = (undefined4 *)(*piVar3 + 7U & 0xfffffffc);
    *piVar3 = (int)puVar5;
    *puVar5 = 1;
    
    puVar5 = (undefined4 *)(*piVar3 + 7U & 0xfffffffc);
    *piVar3 = (int)puVar5;
    *puVar5 = 5;
    *piVar3 = *piVar3 + 4;
    
    FUN_005c8640(local_50);
    
    if (1 < uVar1) {
      puVar2 = (uint *)(DAT_01206880 + 0x14);
      **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126c08;
      *puVar2 = *puVar2 + 4;
      *(undefined1 *)*puVar2 = 1;
      *puVar2 = *puVar2 + 4 & 0xfffffffc;
    }
    
    iVar4 = DAT_01206880;
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126bb8;
    *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 4;
    **(undefined4 **)(iVar4 + 0x14) = 7;
    *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 4;
    
    piVar3 = (int *)(DAT_01206880 + 0x14);
    **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126b18;
    *piVar3 = *piVar3 + 4;
    
    puVar5 = (undefined4 *)(*piVar3 + 3U & 0xfffffffc);
    *piVar3 = (int)puVar5;
    *puVar5 = 1;
    
    puVar5 = (undefined4 *)(*piVar3 + 7U & 0xfffffffc);
    *piVar3 = (int)puVar5;
    *puVar5 = 7;
    
    puVar5 = (undefined4 *)(*piVar3 + 7U & 0xfffffffc);
    *piVar3 = (int)puVar5;
    *puVar5 = 8;
    *piVar3 = *piVar3 + 4;
  }
  
  FUN_005c8640(local_50);
  
  puVar2 = (uint *)(DAT_01206880 + 0x14);
  **(undefined4 **)(DAT_01206880 + 0x14) = &PTR_LAB_01126b40;
  *puVar2 = *puVar2 + 4;
  *(undefined1 *)*puVar2 = 0;
  *puVar2 = *puVar2 + 4 & 0xfffffffc;
  
  return;
}