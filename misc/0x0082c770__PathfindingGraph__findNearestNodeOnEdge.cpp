// FUNC_NAME: PathfindingGraph::findNearestNodeOnEdge
uint __thiscall PathfindingGraph::findNearestNodeOnEdge(int this, undefined4 param_2)
{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  iVar2 = *(int *)(this + 0xc); // +0x0C: nodeCount
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  if (iVar2 == 1) {
    return 0;
  }
  uVar3 = *(uint *)(this + 4); // +0x04: lastFoundNodeIndex
  if (uVar3 < iVar2 - 1U) {
    iVar2 = uVar3 + 1;
  }
  else {
    iVar2 = 0;
  }
  cVar1 = FUN_00821840(param_2,*(int *)(*(int *)(this + 8) + uVar3 * 4) + 4, // +0x08: nodeArray
                       *(int *)(*(int *)(this + 8) + iVar2 * 4) + 4);
  if (cVar1 != '\0') {
    return *(uint *)(this + 4);
  }
  uVar3 = *(uint *)(this + 0xc);
  uVar4 = 0;
  if (uVar3 != 0) {
    do {
      if (uVar4 < uVar3 - 1) {
        iVar2 = uVar4 + 1;
      }
      else {
        iVar2 = 0;
      }
      cVar1 = FUN_00821840(param_2,*(int *)(*(int *)(this + 8) + uVar4 * 4) + 4,
                           *(int *)(*(int *)(this + 8) + iVar2 * 4) + 4);
      if (cVar1 != '\0') {
        return uVar4;
      }
      uVar3 = *(uint *)(this + 0xc);
      uVar4 = uVar4 + 1;
    } while (uVar4 < uVar3);
  }
  return 0xffffffff;
}