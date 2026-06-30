// FUNC_NAME: PathBuilder::generatePoints
undefined4 __thiscall PathBuilder::generatePoints(int thisPtr, int pathData, int numPoints, float* radii)
{
  float scale;
  float fVar1;
  int iVar2;
  char* pointBytePtr;
  float fVar4;
  double dVar5;
  float fVar6;
  float currentAngle;
  ushort* pIdArray;
  
  // thisPtr+0x30 = total angle (e.g., 2*PI), thisPtr+0x34 = scale factor
  // DAT_00e2a848 is likely a conversion factor (e.g., deg to rad or PI)
  fVar4 = *(float *)(thisPtr + 0x30) * *(float *)0x00e2a848; // total angle after scaling
  fVar6 = 0.0f;                                              // initial angle
  iVar2 = 0;
  
  // pathData header: count at +0x0e, count-1 at +0x1c
  *(char *)(pathData + 0x0e) = (char)numPoints;
  currentAngle = 0.0f;
  *(ushort *)(pathData + 0x1c) = (ushort)(byte)((char)numPoints - 1);
  
  if (0 < numPoints) {
    pointBytePtr = (char *)(pathData + 0x0f); // start of point byte fields
    pIdArray = (ushort *)(pathData + 0x3c);   // array of IDs (step size 0x10)
    do {
      // Zero bytes at offsets (relative to point base) 0x0c and 0x0d
      *(pointBytePtr - 3) = '\0';
      *(pointBytePtr - 2) = '\0';
      
      // For iVar2 != 0, set next ID in the ID array
      if (iVar2 != 0) {
        *pIdArray = (ushort)iVar2 & 0xff;
        pIdArray = pIdArray + 0x10; // advance by 16 bytes (sizeof(ushort) * 8?)
      }
      
      // Set flag byte at offset 0x0f: 1 for first point, 2 otherwise
      *pointBytePtr = (iVar2 != 0) + '\x01';
      
      scale = *(float *)(thisPtr + 0x34);
      dVar5 = (double)fVar6;
      FUN_00b99fcb(); // likely sin(double)
      
      // Compute x coordinate: sin(angle) * radiusX * scale
      *(float *)(pointBytePtr - 0x0f) = (float)dVar5 * *radii * scale;
      
      // Zero bytes at offsets 0x04-0x07
      *(pointBytePtr - 0x0b) = '\0';
      *(pointBytePtr - 0x0a) = '\0';
      *(pointBytePtr - 0x09) = '\0';
      *(pointBytePtr - 0x08) = '\0';
      
      dVar5 = (double)currentAngle;
      FUN_00b99e20(); // likely cos(double)
      
      // Update angle step for next iteration
      currentAngle = fVar4 / (float)(numPoints - 1) + currentAngle;
      
      // Compute y coordinate: cos(previousAngle) * radiusY * scale
      *(float *)(pointBytePtr - 7) = (float)dVar5 * radii[2] * scale;
      
      fVar6 = currentAngle;
      FUN_00414aa0(); // possibly some post-processing (e.g., random noise?)
      iVar2 = iVar2 + 1;
      pointBytePtr = pointBytePtr + 0x20; // advance to next point (0x20 bytes each)
    } while (iVar2 < numPoints);
  }
  return 1;
}