// FUNC_NAME: SomeClass::updateClosestPoint
void __thiscall updateClosestPoint(int this, undefined4 pointA, undefined4 pointB, undefined4 pointC)
{
  float10 distanceSq;
  undefined8 closestPoint;
  undefined4 extraParam;
  
  distanceSq = (float10)FUN_0084cb90(pointA, pointB, pointC, &closestPoint, 1);
  if ((*(float *)(this + 0x14) == DAT_00d5ccf8) || ((float)distanceSq < *(float *)(this + 0x14))) {
    *(undefined8 *)(this + 8) = closestPoint;   // +0x08: closest point position
    *(undefined4 *)(this + 0x10) = extraParam;   // +0x10: extra parameter for closest point
    *(float *)(this + 0x14) = (float)distanceSq; // +0x14: closest distance squared
  }
  return;
}