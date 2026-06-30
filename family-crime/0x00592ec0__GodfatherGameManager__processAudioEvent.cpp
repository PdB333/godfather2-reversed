// FUNC_NAME: GodfatherGameManager::processAudioEvent
int __thiscall GodfatherGameManager::processAudioEvent(int *this, int audioEvent, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
  float fVar1;
  uint in_EAX;
  undefined4 uVar2;
  int iVar3;
  float10 fVar4;
  uint local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined1 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined1 local_b4;
  undefined4 local_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  float fStack_a4;
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  float fStack_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  float local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  float local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  float local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  float local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  float fStack_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  float fStack_14;

  // Initialize audio transform matrices (likely 4x4 matrices with w=1.0)
  uStack_a8 = 0;
  uStack_ac = 0;
  local_b0 = 0;
  fStack_a4 = DAT_00e2b1a4; // 1.0f
  uStack_98 = 0;
  uStack_9c = 0;
  local_a0 = 0;
  fStack_94 = DAT_00e2b1a4; // 1.0f
  local_88 = 0;
  local_8c = 0;
  local_90 = 0;
  local_84 = DAT_00e2b1a4; // 1.0f
  local_78 = 0;
  local_7c = 0;
  local_80 = 0;
  local_74 = DAT_00e2b1a4; // 1.0f
  local_68 = 0;
  local_6c = 0;
  local_70 = 0;
  local_64 = DAT_00e2b1a4; // 1.0f
  local_58 = 0;
  local_5c = 0;
  local_60 = 0;
  local_54 = DAT_00e2b1a4; // 1.0f
  local_48 = 0;
  local_4c = 0;
  local_50 = 0;
  local_44 = DAT_00e2b1a4; // 1.0f
  local_38 = 0;
  local_3c = 0;
  local_40 = 0;
  local_34 = DAT_00e2b1a4; // 1.0f

  // Extract some flag from EAX
  local_dc = CONCAT31(local_dc._1_3_,(char)(in_EAX >> 5)) & 0xffffff01;

  // Zero out other local variables
  local_d4 = 0;
  local_d0 = 0;
  local_c8 = 0;
  local_c0 = 0;
  local_bc = 0;
  local_b4 = 0;
  local_d8 = 0;
  local_cc = 0;
  local_c4 = 0;
  local_b8 = 0;

  // Get random value and seed random generator
  fVar4 = (float10)FUN_00593910(param_5); // getRandomFloat
  FUN_00593910((float)fVar4); // seedRandom

  // Initialize matrix to identity
  FUN_00593210(&local_b0,0); // matrixIdentity

  // Check if audio event has a specific flag
  if ((in_EAX >> 5 & 1) != 0) {
    iVar3 = this[1]; // this->audioDataManager +0x4
    // Copy first matrix to second set
    local_30 = local_b0;
    uStack_2c = uStack_ac;
    uStack_28 = uStack_a8;
    fStack_24 = fStack_a4;
    local_20 = local_a0;
    uStack_1c = uStack_9c;
    uStack_18 = uStack_98;
    fStack_14 = fStack_94;

    // Get audio event data based on priority
    if ((*(uint *)(iVar3 + 4) & 0xff) < 10) {
      uVar2 = *(undefined4 *)(iVar3 + 0xc); // low priority audio data
    }
    else {
      uVar2 = *(undefined4 *)(iVar3 + 0x20); // high priority audio data
    }

    // Look up audio event in database
    iVar3 = FUN_00586df0(&local_50, uVar2); // findAudioEvent
    if (iVar3 == 0) {
      return 0; // event not found
    }
  }

  // Check if audio system is ready (two different states)
  iVar3 = FUN_005934f0(&local_70, &local_c4); // checkAudioSystemState
  if ((iVar3 != 0) && (iVar3 = FUN_005934f0(&local_90, &local_d8), iVar3 != 0)) {
    // Process the audio event with position data
    FUN_00586fa0(audioEvent, &local_50, local_dc); // playAudioEvent

    // Apply volume scaling if present
    if ((*this != 0) && (fVar1 = *(float *)(*this + 0x104), fVar1 != DAT_00e2b1a4)) {
      // Scale audio volume by master volume factor
      *(float *)(audioEvent + 0x10) = *(float *)(audioEvent + 0x10) * fVar1;
      *(float *)(audioEvent + 0x14) = *(float *)(audioEvent + 0x14) * fVar1;
      *(float *)(audioEvent + 0x18) = *(float *)(audioEvent + 0x18) * fVar1;
    }
    return audioEvent;
  }

  return 0; // audio system not ready
}