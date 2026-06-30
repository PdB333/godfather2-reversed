// FUNC_NAME: TransformNode::localizePoints
void __thiscall TransformNode::localizePoints(int this, float *points)
{
  float fVar1;
  float *nodeTransform;
  int numPoints;
  float *local_50;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  float diffX;
  float diffY;
  float diffZ;
  undefined4 uStack_14;
  
  if (((points != (float *)0x0) && (points[4] != 0.0)) && (this != 0)) {
    numPoints = 0;
    local_50 = nodeTransform;  // in_EAX - current transform node pointer
    local_34 = this;  // number of points
    do {
      fVar1 = points[4];  // some stride or count
      if (local_50[8] != 0.0) {  // some skip condition
        if (points[7] == 0.0) {  // if some flag is zero, do transform with inverse rotation
          diffX = *points - *local_50;
          diffY = points[1] - local_50[1];
          diffZ = points[2] - local_50[2];
          uStack_14 = DAT_00e2b1a4;  // global transform matrix
          FUN_0044c4c0(local_50[8], &diffX, &local_30);  // matrix multiply (inverse?)
          *(undefined4 *)(numPoints + 0xc + (int)fVar1) = local_30;
          *(undefined4 *)(numPoints + 0x10 + (int)fVar1) = local_2c;
          *(undefined4 *)(numPoints + 0x14 + (int)fVar1) = local_28;
        }
        else {  // if flag is non-zero, just copy world positions
          *(float *)(numPoints + 0xc + (int)fVar1) = *points;
          *(float *)(numPoints + 0x10 + (int)fVar1) = points[1];
          *(float *)(numPoints + 0x14 + (int)fVar1) = points[2];
        }
      }
      local_50 = local_50 + 0xc;  // advance to next transform node (12 floats stride)
      numPoints = numPoints + 0xc;
      local_34 = local_34 + -1;
    } while (local_34 != 0);
  }
  return;
}