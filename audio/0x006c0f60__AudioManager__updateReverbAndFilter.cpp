// FUNC_NAME: AudioManager::updateReverbAndFilter
void __thiscall AudioManager::updateReverbAndFilter(int this, float param_2, float param_3, float param_4)
{
  float fVar1;
  float fVar2;
  uint uVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  
  // Call to audio processing function with global constants
  fVar4 = (float10)FUN_006c91c0(param_2, _DAT_00e50e70, _DAT_00e50e74, _DAT_0112a780, _DAT_00e50f50);
  
  fVar2 = DAT_00d5eee4;  // Some audio constant
  fVar1 = _DAT_00d5780c; // 1.0f constant
  fVar6 = (DAT_00e50f4c * param_2 + _DAT_00e50f48) * param_2 * DAT_00e445a4; // Frequency-dependent scaling
  
  // Update reverb level at +0x50
  *(float *)(this + 0x50) =
       (float)((fVar4 * (float10)param_3 + (float10)_DAT_00d5780c) *
              (float10)*(float *)(this + 0x50));
  
  uVar3 = DAT_010c2678 & DAT_012054b4;  // Index into audio table
  fVar5 = (*(float *)(&DAT_010c2680 + (DAT_010c2678 & DAT_012054b4 + 1) * 4) * fVar2 - fVar1) *
          _DAT_00e50f40;  // Filter coefficient calculation
  
  DAT_012054b4 = DAT_012054b4 + 2;  // Advance table index
  
  // Update left filter coefficient at +0x40
  *(float *)(this + 0x40) =
       ((*(float *)(&DAT_010c2680 + uVar3 * 4) * fVar2 - fVar1) * _DAT_00e50f44 * fVar6 * param_4 +
       fVar1) * *(float *)(this + 0x40);
  
  // Update right filter coefficient at +0x44
  *(float *)(this + 0x44) = (fVar5 * fVar6 * param_4 + fVar1) * *(float *)(this + 0x44);
  
  return;
}