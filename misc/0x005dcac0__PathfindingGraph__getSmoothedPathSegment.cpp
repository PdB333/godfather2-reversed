// FUNC_NAME: PathfindingGraph::getSmoothedPathSegment
bool PathfindingGraph::getSmoothedPathSegment(float param_1, float *param_2, float *param_3, float param_4)
{
  int iVar1;
  float fVar2;
  float local_c;
  float local_8;
  float local_4;
  
  iVar1 = FUN_005dc670(this);
  if (iVar1 != 0) {
    FUN_005dd8a0(0, &param_1);            // get segment start point
    FUN_005dd8a0(DAT_012056c0, &local_c); // get segment control point
    fVar2 = DAT_00e2b1a4 - param_4;       // DAT_00e2b1a4 is probably 1.0f (complement of t)
    *param_2 = fVar2 * param_1 + local_c * param_4; // quadratic bezier X interpolation
    *param_3 = fVar2 * local_8 + local_4 * param_4; // quadratic bezier Y interpolation
  }
  return iVar1 != 0;
}