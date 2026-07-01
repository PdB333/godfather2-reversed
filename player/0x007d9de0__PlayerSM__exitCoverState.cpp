// FUNC_NAME: PlayerSM::exitCoverState
void __fastcall PlayerSM::exitCoverState(int this)
{
  int *pNode;
  undefined4 *pList;
  
  // Call the virtual function at vtable+0x304 (likely onEnter/onExit or similar state machine method)
  (**(code **)(**(int **)(this + 0x58) + 0x304))();
  
  // Clear bit 2 (0x4) of flags at +0xC4 (likely cover state flag)
  *(uint *)(this + 0xc4) = *(uint *)(this + 0xc4) & 0xfffffffb;
  
  // Get list of cover hint nodes (type 2)
  pList = (undefined4 *)FUN_0043c2c0(2);
  for (pNode = (int *)*pList; pNode != (int *)0x0; pNode = (int *)pNode[1]) {
    // Check if node has an occupant (+0x130)
    if (*(int *)(*pNode + 0x130) != 0) {
      // Clear occupant's cover state pointer (+0x30)
      *(undefined4 *)(*(int *)(*pNode + 0x130) + 0x30) = 0;
    }
  }
  return;
}