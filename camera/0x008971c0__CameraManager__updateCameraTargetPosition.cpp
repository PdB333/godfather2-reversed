// FUNC_NAME: CameraManager::updateCameraTargetPosition
void __fastcall CameraManager::updateCameraTargetPosition(undefined4 *this)
{
  float local_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  // Call member function at offset +0x1c (getCameraTarget?) - returns position via pointer
  (*(code *)this[7])(*this, &local_3c);
  
  // Build two position vectors: one for interpolation, one for direct
  // +0x40 = offset position X, +0x44 = Y, +0x48 = Z
  // +0x4c = offset for W component stored in global _DAT_00d5780c
  fStack_20 = (float)this[0x10] + local_3c;
  fStack_1c = (float)this[0x11] + fStack_38;
  fStack_18 = (float)this[0x12] + fStack_34;
  fStack_14 = (float)this[0x13] + _DAT_00d5780c;
  
  // +0x30 = another position offset X, +0x34 = Y, +0x38 = Z
  // +0x3c = offset for W component
  fStack_30 = (float)this[0xc] + local_3c;
  fStack_2c = (float)this[0xd] + fStack_38;
  fStack_28 = (float)this[0xe] + fStack_34;
  fStack_24 = (float)this[0xf] + _DAT_00d5780c;
  
  // +0x20 = flag indicating if we need to create a new interpolator
  if (this[8] == 0) {
    // No interpolator exists - create one using TLS and memory allocation
    TlsGetValue(DAT_01139810);
    int iVar2 = FUN_00aa2680(0xd0, 0x31);  // Allocate 208 bytes, align 0x31
    *(undefined2 *)(iVar2 + 4) = 0xd0;  // Set size field
    undefined4 uVar3 = FUN_009f59e0(&fStack_30, this[6]);  // Create interpolator from position
    undefined4 uVar1 = *this;
    this[8] = uVar3;  // Store interpolator
    FUN_0043b490();  // Notify system of allocation
    FUN_009f01f0(0x2001, uVar1, 0);  // Register memory usage
    FUN_009e7450(this[8]);  // Initialize interpolator
    this[0x14] = DAT_01205224;  // +0x50 = set some flag/timestamp
    return;
  }
  
  // Interpolator exists - just update target position
  FUN_009f5240(&fStack_30);  // Update interpolator with new position
  this[0x14] = DAT_01205224;  // +0x50 = update timestamp/flag
  return;
}