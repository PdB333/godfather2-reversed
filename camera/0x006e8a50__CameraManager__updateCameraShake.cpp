// FUNC_NAME: CameraManager::updateCameraShake
undefined4 * __thiscall CameraManager::updateCameraShake(undefined4 *this, int param_2, undefined4 param_3)

{
  float *pfVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  float fVar5;
  float fVar6;
  float local_9c;
  float local_98;
  float local_94;
  undefined1 local_90 [64];
  undefined1 auStack_50 [76];
  
  uVar4 = 0;
  this[1] = param_2;
  this[2] = param_3;
  *this = &PTR_FUN_00d5fb78;
  this[3] = 0;
  iVar2 = FUN_009c8e50(0x8c); // Allocate memory for shake data (0x8c bytes)
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = FUN_006e8950(); // Initialize shake data
  }
  local_98 = DAT_00e44730; // Default Y shake magnitude
  local_94 = DAT_00d5eee4; // Default X shake magnitude
  this[3] = uVar3;
  local_9c = DAT_00d5f540; // Default Z shake magnitude
  if (*(short *)(param_2 + 0x20) != 0) { // Check if there are shake parameters
    do {
      pfVar1 = *(float **)(*(int *)(param_2 + 0x1c) + uVar4 * 4); // Get parameter entry
      fVar5 = pfVar1[4]; // Parameter type identifier
      if ((uint)fVar5 < 0xb02940b3) {
        if (fVar5 == -6.157378e-10) { // Type: X magnitude
          local_94 = *pfVar1;
        }
        else if (fVar5 == 9.000423e-10) { // Type: X frequency
          FUN_006e5d30(*pfVar1);
        }
        else if (fVar5 == 1.804863e+22) { // Type: Y magnitude
          local_98 = *pfVar1;
        }
        else if (fVar5 == 4.7095128e+26) { // Type: Y frequency
          FUN_006e5d60(*pfVar1);
        }
      }
      else if (fVar5 == -1.48274e-06) { // Type: shake flags
        *(char *)(this[3] + 0x88) = '\\x01' << (SUB41(*pfVar1,0) & 0x1f);
      }
      else if (fVar5 == -1.4321715e+13) { // Type: shake event
        FUN_004a36a0(local_90); // Get current time
        (**(code **)(**(int **)(this[2] + 8) + 4))(); // Callback
        FUN_006e86c0(auStack_50); // Process shake event
        FUN_006e5b40(auStack_50); // Apply shake
      }
      else if (fVar5 == -3.5940283e+17) { // Type: Z magnitude
        local_9c = *pfVar1;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < *(ushort *)(param_2 + 0x20));
  }
  FUN_006e5d90(local_94,local_98); // Apply base shake magnitudes
  iVar2 = this[3];
  if ((*(byte *)(iVar2 + 0x88) & 1) == 0) { // Check if shake is not disabled
    fVar5 = *(float *)(iVar2 + 0x20) * local_9c; // Scale X by Z magnitude
    fVar6 = *(float *)(iVar2 + 0x24) * local_9c; // Scale Y by Z magnitude
    local_9c = *(float *)(iVar2 + 0x28) * local_9c; // Scale Z by Z magnitude
    if (*(byte *)(iVar2 + 0x88) == 4) { // Shake type: subtractive
      *(float *)(iVar2 + 0x68) = *(float *)(iVar2 + 0x44) - fVar5; // +0x68: offset X
      *(float *)(iVar2 + 0x6c) = *(float *)(iVar2 + 0x48) - fVar6; // +0x6c: offset Y
      *(float *)(iVar2 + 0x70) = *(float *)(iVar2 + 0x4c) - local_9c; // +0x70: offset Z
    }
    else {
      *(float *)(iVar2 + 0x68) = *(float *)(iVar2 + 0x44) + fVar5; // +0x68: offset X
      *(float *)(iVar2 + 0x6c) = *(float *)(iVar2 + 0x48) + fVar6; // +0x6c: offset Y
      *(float *)(iVar2 + 0x70) = *(float *)(iVar2 + 0x4c) + local_9c; // +0x70: offset Z
      if (*(char *)(iVar2 + 0x88) == '\\b') { // Shake type: additive with secondary
        *(float *)(iVar2 + 0x74) = *(float *)(iVar2 + 0x44) + fVar5; // +0x74: secondary offset X
        *(float *)(iVar2 + 0x78) = *(float *)(iVar2 + 0x48) + fVar6; // +0x78: secondary offset Y
        *(float *)(iVar2 + 0x7c) = *(float *)(iVar2 + 0x4c) + local_9c; // +0x7c: secondary offset Z
      }
    }
    *(float *)(iVar2 + 0x6c) = *(float *)(iVar2 + 0x6c) + DAT_00d5ca18; // Add gravity offset to Y
    *(byte *)(this[3] + 0x8a) = *(byte *)(this[3] + 0x8a) | 8; // Set dirty flag
    return this;
  }
  // Shake disabled: copy base position to offsets
  *(undefined8 *)(iVar2 + 0x68) = *(undefined8 *)(iVar2 + 0x44); // Copy X,Y base to offset
  *(undefined4 *)(iVar2 + 0x70) = *(undefined4 *)(iVar2 + 0x4c); // Copy Z base to offset
  *(float *)(iVar2 + 0x6c) = *(float *)(iVar2 + 0x6c) + DAT_00d5fb68; // Add gravity offset to Y
  *(undefined8 *)(iVar2 + 0x74) = *(undefined8 *)(iVar2 + 0x44); // Copy X,Y base to secondary offset
  *(undefined4 *)(iVar2 + 0x7c) = *(undefined4 *)(iVar2 + 0x4c); // Copy Z base to secondary offset
  *(byte *)(this[3] + 0x8a) = *(byte *)(this[3] + 0x8a) | 8; // Set dirty flag
  return this;
}