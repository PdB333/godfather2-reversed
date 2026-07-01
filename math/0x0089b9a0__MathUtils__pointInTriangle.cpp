// FUNC_NAME: MathUtils::pointInTriangle
bool MathUtils::pointInTriangle(undefined4 *trianglePoints, undefined4 point)
{
  int iVar1;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  FUN_004262f0(0);
  local_20 = *trianglePoints;
  local_1c = trianglePoints[1];
  local_18 = trianglePoints[2];
  local_14 = point;
  iVar1 = FUN_004bdae0(&local_20);
  return iVar1 == 2;
}