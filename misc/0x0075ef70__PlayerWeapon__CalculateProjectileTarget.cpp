// FUNC_NAME: PlayerWeapon::CalculateProjectileTarget
void __thiscall PlayerWeapon::CalculateProjectileTarget(Vec3* outWorldPos, bool bUseMuzzleOffset)
{
  float fVar1;
  int cameraPtr;
  int* basePtr;
  float10 invLength;
  float scaledFactor;
  float dirX, dirY, dirZ;
  float local_1c, local_28, fStack_18;
  float fStack_20, fStack_2c, fStack_38;
  
  // Check if aim-lock or some flag at +0xA8 bit 17
  if ((*(uint*)(this + 0xA8) >> 0x11 & 1) == 0) {
    cameraPtr = getCamera();  // FUN_00471610()
    
    // Read weapon position (x,y packed as double at +0x60, z at +0x68)
    dirX = (float)*(undefined8*)(this + 0x60);               // low 32 bits
    dirY = (float)((ulonglong)*(undefined8*)(this + 0x60) >> 0x20); // high 32 bits
    dirZ = *(float*)(this + 0x68);
    
    if (bUseMuzzleOffset) {
      // Apply muzzle offset stored at +0xFC/+0x100/+0x104
      dirX += *(float*)(this + 0xFC);
      dirY += *(float*)(this + 0x100);
      dirZ += *(float*)(this + 0x104);
    }
    
    // Compute direction from weapon to camera target
    dirX -= *(float*)(cameraPtr + 0x30);
    dirY -= *(float*)(cameraPtr + 0x34);
    dirZ -= *(float*)(cameraPtr + 0x38);
    
    // Get the weapon's attachment base (from +0x48, adjust to container)
    if (*(int*)(this + 0x48) == 0) {
      basePtr = 0;
    } else {
      basePtr = (int*)(*(int*)(this + 0x48) - 0x48);
    }
    
    // Call virtual function to get weapon offset vector (likely barrel tip position)
    (**(code**)(*basePtr + 0x4C))(&local_1c);
    float offsetLen = SQRT(local_1c * local_1c + fStack_20 * fStack_20 + fStack_18 * fStack_18);
    
    // Clamp offset length to minimum constant
    if (offsetLen < cMinOffsetLen) {  // DAT_00e51b00
      offsetLen = cMinOffsetLen;
    }
    float scale = cScaleFactor * offsetLen;  // DAT_00e51afc
    if (fStack_38 < scale) {
      scale = fStack_38;
    }
    
    // Normalize direction and scale, then add camera position
    invLength = inverseVec3Length(&dirX, &dirY, &dirZ);  // FUN_0056afa0
    outWorldPos->x = (float)invLength * scale + *(float*)(cameraPtr + 0x30);
    outWorldPos->y = dirY * (float)invLength * scale + *(float*)(cameraPtr + 0x34);
    outWorldPos->z = dirZ * (float)invLength * scale + *(float*)(cameraPtr + 0x38);
    return;
  }
  
  // Fast path: copy weapon position directly if aim-lock is active
  outWorldPos->packedXY = *(undefined8*)(this + 0x60);  // x,y as double
  outWorldPos->z = *(float*)(this + 0x68);
}