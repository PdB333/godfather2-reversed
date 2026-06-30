// FUNC_NAME: Animation::advanceTime
int __thiscall Animation::advanceTime(int this, int param_2)
{
  uint uVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  uint3 uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar2 = DAT_00e2b1a4; // Some global constant (likely 0.0f or 1.0f)
  *(undefined4 *)(this + 0x48) = 0; // +0x48: some flag/state
  *(undefined4 *)(this + 0x44) = 0; // +0x44: 
  *(undefined4 *)(this + 0x40) = 0; // +0x40: 
  *(float *)(this + 0x4c) = fVar2;  // +0x4c: reset to constant
  *(undefined4 *)(this + 0x58) = 0; // +0x58: 
  *(undefined4 *)(this + 0x54) = 0; // +0x54: 
  *(undefined4 *)(this + 0x50) = 0; // +0x50: 
  *(float *)(this + 0x5c) = fVar2;  // +0x5c: reset to constant
  
  uVar1 = *(uint *)(this + 0x10); // +0x10: flags/state bitfield
  uVar3 = uVar1 >> 3 & 0xffffff01;
  *(uint *)(this + 0x10) = uVar1 & 0xf7fdfff4; // Clear some flags
  
  if ((char)uVar3 == '\0') { // Check if animation is not finished/stopped
    fVar8 = *(float *)(this + 0x24); // +0x24: end time or duration
    *(undefined4 *)(this + 0x20) = *(undefined4 *)(this + 0x1c); // +0x1c -> +0x20: copy current time
    *(float *)(this + 0x28) = fVar8; // +0x28: store end time
    
    if (*(int *)(this + 0x2c) != 2) { // +0x2c: playback mode (0=once, 1=loop, 2=pingpong?)
      fVar6 = *(float *)(this + 0x1c) + *(float *)(param_2 + 4); // Add delta time
      iVar4 = (uint)CONCAT21((short)(uVar3 >> 0x10),
                             (fVar8 == fVar2) << 6 | (NAN(fVar8) || NAN(fVar2)) << 2 | 2U |
                             fVar8 < fVar2) << 8;
      *(float *)(this + 0x1c) = fVar6; // Update current time
      
      if (fVar8 == fVar2) {
        // If end time equals constant, just take integer part
        iVar4 = (int)fVar6;
        fVar6 = fVar6 - (float)iVar4;
      }
      else {
        fVar7 = fVar8 - fVar2; // Duration
        if (fVar7 < fVar6) {
          // Handle wrapping/looping
          iVar4 = (int)(fVar6 / fVar7);
          fVar6 = fVar6 - (float)iVar4 * fVar7;
        }
      }
      
      *(float *)(this + 0x1c) = fVar6; // Store wrapped time
      fVar8 = fVar8 - fVar2; // Duration
      uVar5 = (uint3)((uint)iVar4 >> 8);
      
      if (*(float *)(param_2 + 4) < fVar8) {
        iVar4 = (uint)uVar5 << 8;
      }
      else {
        iVar4 = CONCAT31(uVar5,1);
      }
      
      if ((*(float *)(this + 0x20) <= fVar6) && ((char)iVar4 == '\0')) {
        return iVar4; // No wrap occurred
      }
      
      // Wrap occurred - set flag and update output
      *(uint *)(this + 0x10) = uVar1 & 0xf7fdfff4 | 1; // Set wrap flag
      *(undefined4 *)(param_2 + 8) = *(undefined4 *)(this + 0x1c); // Output current time
      *(float *)(param_2 + 0xc) = *(float *)(this + 0x20) - fVar8; // Output remaining time
      
      if (((*(char *)(this + 0x30) == '\0') || (*(int *)(this + 0x2c) == 0)) &&
         (*(float *)(this + 0x1c) = fVar8, fVar8 < *(float *)(this + 0x20))) {
        *(float *)(this + 0x20) = fVar8; // Clamp to end time
      }
      return CONCAT31((int3)((uint)iVar4 >> 8),1); // Return with wrap flag
    }
  }
  return (uVar1 >> 0xb) << 8; // Return previous state
}