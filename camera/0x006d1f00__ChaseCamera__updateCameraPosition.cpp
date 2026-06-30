// FUNC_NAME: ChaseCamera::updateCameraPosition
void __fastcall ChaseCamera::updateCameraPosition(ChaseCamera *this)
{
  float fVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  pfVar2 = (float *)FUN_00471610(); // Get camera target position (likely player position)
  fVar6 = DAT_00e44564; // Some global constant
  fVar1 = _DAT_00d5780c; // Another global constant
  fVar3 = pfVar2[0xd]; // Target Y
  fVar4 = pfVar2[0xe]; // Target Z
  fVar5 = pfVar2[0xf]; // Target W (unused?)
  
  // Copy target position into camera struct
  *(float *)(this + 0x90) = pfVar2[0xc]; // +0x90: targetX
  *(float *)(this + 0x94) = fVar3;       // +0x94: targetY
  *(float *)(this + 0x98) = fVar4;       // +0x98: targetZ
  *(float *)(this + 0x9c) = fVar5;       // +0x9c: targetW
  
  fVar4 = *(float *)(this + 0x94) + DAT_0112a870; // Add offset to targetY
  *(float *)(this + 0x94) = fVar4; // Update targetY with offset
  
  fVar5 = fVar6 - *pfVar2;  // Delta X from camera to target
  fVar6 = fVar6 - pfVar2[2]; // Delta Z from camera to target
  
  fVar3 = fVar5 * fVar5 + fVar6 * fVar6; // Distance squared
  if (fVar3 <= DAT_00d5f2b4) { // If close enough, no movement
    fVar3 = 0.0;
  }
  else {
    fVar3 = fVar1 / SQRT(fVar3); // Normalize distance
  }
  
  fVar4 = fVar4 + DAT_00e51128; // Add another offset
  fVar6 = DAT_00e51124 * fVar3 * fVar6 + *(float *)(this + 0x98); // Apply damping
  
  // Update camera position
  *(float *)(this + 0xc0) = DAT_00e51124 * fVar3 * fVar5 + *(float *)(this + 0x90); // +0xc0: cameraX
  *(float *)(this + 200) = fVar6; // +0xc8: cameraZ (offset 200 = 0xC8)
  *(float *)(this + 0xc4) = fVar4; // +0xc4: cameraY
  *(float *)(this + 0xcc) = fVar1; // +0xcc: cameraFOV or zoom
  
  fVar3 = pfVar2[10] * DAT_00e51178; // Some scaling factor
  fVar4 = fVar4 + _DAT_00e5112c; // Additional Y offset
  
  // Update look-at target
  *(float *)(this + 0x70) = *(float *)(this + 0xc0) - pfVar2[8] * DAT_00e51178; // +0x70: lookAtX
  *(float *)(this + 0x74) = fVar4; // +0x74: lookAtY
  *(float *)(this + 0x78) = fVar6 - fVar3; // +0x78: lookAtZ
  *(float *)(this + 0x7c) = fVar1; // +0x7c: lookAtFOV
  
  return;
}