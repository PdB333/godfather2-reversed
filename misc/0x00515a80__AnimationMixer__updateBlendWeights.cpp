// FUNC_NAME: AnimationMixer::updateBlendWeights
void AnimationMixer::updateBlendWeights(void)

{
  char cVar1;
  float fVar2;
  
  // Check if target weight (DAT_01219240) differs from current weight (DAT_00e2b05c)
  // and if the time threshold (DAT_00e2af44) is less than various blend track timers
  if ((DAT_01219240 != DAT_00e2b05c) &&
     (((DAT_00e2af44 <= DAT_01219220 &&
       (((DAT_00e2af44 <= DAT_01219200 || (DAT_00e2af44 <= DAT_01219204)) ||
        (DAT_00e2af44 <= DAT_01219208)))) ||
      ((DAT_00e2af44 <= DAT_0121922c &&
       (((DAT_00e2af44 <= DAT_01219210 || (DAT_00e2af44 <= DAT_01219214)) ||
        (DAT_00e2af44 <= DAT_01219218)))))))) {
    // Calculate blend factor (current time / target weight)
    fVar2 = DAT_00e2b1a4 / DAT_01219240;  // +0x1a4: time delta, +0x240: blend duration
    
    // Scale all 8 blend weights by the blend factor (8 tracks, 4x4 float matrix layout)
    _DAT_012191e0 = fVar2 * _DAT_012191e0;  // +0x1e0: blend weight 0
    _DAT_012191e4 = fVar2 * _DAT_012191e4;  // +0x1e4: blend weight 1
    _DAT_012191e8 = fVar2 * _DAT_012191e8;  // +0x1e8: blend weight 2
    _DAT_012191ec = fVar2 * _DAT_012191ec;  // +0x1ec: blend weight 3
    _DAT_012191f0 = fVar2 * _DAT_012191f0;  // +0x1f0: blend weight 4
    _DAT_012191f4 = fVar2 * _DAT_012191f4;  // +0x1f4: blend weight 5
    _DAT_012191f8 = fVar2 * _DAT_012191f8;  // +0x1f8: blend weight 6
    _DAT_012191fc = fVar2 * _DAT_012191fc;  // +0x1fc: blend weight 7
    
    // Call normalization function with blend weights array, sample count (DAT_01219230), and param_2
    cVar1 = FUN_00514c40(&DAT_012191e0,DAT_01219230,param_2);  // normalize weights
    if (cVar1 == '\0') {
      // Normalization failed - reset all weights to zero and re-initialize
      DAT_01219200 = DAT_00e2b1a4;  // +0x200: reset blend start time
      DAT_01219204 = DAT_00e2b1a4;  // +0x204: reset blend end time
      DAT_01219208 = DAT_00e2b1a4;  // +0x208: reset blend curve time
      _DAT_012191ec = 0.0;  // Clear all blend weights
      _DAT_012191e8 = 0.0;
      _DAT_012191e4 = 0.0;
      _DAT_012191e0 = 0.0;
      _DAT_012191fc = 0.0;
      _DAT_012191f8 = 0.0;
      _DAT_012191f4 = 0.0;
      _DAT_012191f0 = 0.0;
      _DAT_0121920c = 0;  // +0x20c: reset blend state flags
      _DAT_0121921c = 0;  // +0x21c: reset blend mode
      DAT_01219218 = 0.0;  // +0x218: reset blend position
      DAT_01219214 = 0.0;  // +0x214: reset blend ratio
      DAT_01219210 = 0.0;  // +0x210: reset blend target
      DAT_01219220 = 0.0;  // +0x220: reset blend timer
      DAT_0121922c = 0.0;  // +0x22c: reset blend parameter
      DAT_01219224 = DAT_00e2eb58;  // +0x224: reset to default interpolation value
      DAT_01219228 = DAT_00e2eb58;  // +0x228: reset second interpolation value
      DAT_01219230 = 0;  // +0x230: reset sample count
      DAT_01219240 = 0.0;  // +0x240: reset target weight
    }
  }
  return;
}