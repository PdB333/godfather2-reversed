// FUNC_NAME: Navigation::findClosestEdgeToPoint
uint __thiscall Navigation::findClosestEdgeToPoint(int this, undefined4 point)
{
  char cVar1;
  int edgeCount;
  uint currentEdgeIdx;
  uint nextEdgeIdx;
  
  edgeCount = *(int *)(this + 0xc); // +0xC: number of edges in navigation graph
  if (edgeCount == 0) {
    return 0xffffffff;
  }
  if (edgeCount == 1) {
    return 0;
  }
  
  currentEdgeIdx = *(uint *)(this + 4); // +0x4: current edge index (starting point for search)
  if (currentEdgeIdx < edgeCount - 1U) {
    nextEdgeIdx = currentEdgeIdx + 1;
  }
  else {
    nextEdgeIdx = 0;
  }
  
  // Check if point is between current edge and next edge
  cVar1 = FUN_00821840(point, *(int *)(*(int *)(this + 8) + currentEdgeIdx * 4) + 4,
                       *(int *)(*(int *)(this + 8) + nextEdgeIdx * 4) + 4);
  if (cVar1 != '\0') {
    return *(uint *)(this + 4); // Return current edge index
  }
  
  // Search all edges for the closest one to the point
  currentEdgeIdx = *(uint *)(this + 0xc);
  nextEdgeIdx = 0;
  if (currentEdgeIdx != 0) {
    do {
      if (nextEdgeIdx < currentEdgeIdx - 1) {
        edgeCount = nextEdgeIdx + 1;
      }
      else {
        edgeCount = 0;
      }
      cVar1 = FUN_00821840(point, *(int *)(*(int *)(this + 8) + nextEdgeIdx * 4) + 4,
                           *(int *)(*(int *)(this + 8) + edgeCount * 4) + 4);
      if (cVar1 != '\0') {
        return nextEdgeIdx;
      }
      currentEdgeIdx = *(uint *)(this + 0xc);
      nextEdgeIdx = nextEdgeIdx + 1;
    } while (nextEdgeIdx < currentEdgeIdx);
  }
  return 0xffffffff;
}