// FUNC_NAME: CameraManager::updateCameraShake
void __fastcall CameraManager::updateCameraShake(int this)
{
  float fVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  float local_24;
  float fStack_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  float local_4;
  
  // Get current camera position (world space)
  pfVar2 = (float *)FUN_00471610(); // likely getCameraPosition()
  // Calculate offset from reference point (DAT_00e44564 is probably 0.0f or some constant)
  local_c = DAT_00e44564 - *pfVar2;
  local_8 = DAT_00e44564 - pfVar2[1];
  local_4 = DAT_00e44564 - pfVar2[2];
  
  // Get another position (maybe target or look-at point)
  pfVar3 = (float *)FUN_00471610(); // likely getCameraTarget()
  local_18 = DAT_00e44564 - *pfVar3;
  local_14 = DAT_00e44564 - pfVar3[1];
  local_10 = DAT_00e44564 - pfVar3[2];
  
  // Get shake parameters
  iVar4 = FUN_00471610(); // likely getShakeParameters()
  fStack_20 = (float)((ulonglong)*(undefined8 *)(iVar4 + 0x30) >> 0x20); // shake frequency/amplitude high word
  fVar1 = (float)*(undefined8 *)(iVar4 + 0x30); // shake frequency/amplitude low word
  
  // Check camera mode (0x118 offset)
  if (*(int *)(this + 0x118) == 2) { // CAMERA_MODE_FIRST_PERSON or similar
    // First person shake calculation
    _local_24 = CONCAT44(local_14 * _DAT_00d5c458 + pfVar2[1] + fStack_20 + DAT_00d64730,
                         local_18 * _DAT_00d5c458 + *pfVar2 + fVar1);
    fVar1 = pfVar2[2];
  }
  else {
    // Third person shake calculation
    _local_24 = CONCAT44(local_14 * _DAT_00d5c458 + local_8 + fStack_20 + DAT_00d64730,
                         local_18 * _DAT_00d5c458 + fVar1 + local_c);
    fVar1 = local_4;
  }
  
  // Apply vertical shake component
  local_1c = local_10 * _DAT_00d5c458 + fVar1 + *(float *)(iVar4 + 0x38);
  
  // Apply the shake offset to camera
  FUN_007f6390(&local_24); // setCameraOffset or applyShake
  FUN_007f62e0(); // updateCameraTransform or similar
  FUN_007f62b0(); // finalizeCameraUpdate or similar
  
  return;
}