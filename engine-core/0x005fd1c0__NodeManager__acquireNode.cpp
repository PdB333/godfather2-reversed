// FUNC_NAME: NodeManager::acquireNode
void __thiscall NodeManager::acquireNode(NodeManager* this, NodeLink* outLink, NodeQuery* query)
{
  ushort uVar1;
  int nodePtr;
  char success;
  int temp;
  float dist;
  int local_44;
  int local_40;
  undefined **local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined8 local_2c;
  undefined8 local_24;
  undefined8 local_1c;
  undefined8 local_14;
  undefined4 local_c;
  
  if ((int)(uint)*(ushort *)(query + 3) <
      (int)((uint)*(ushort *)(this + 0x3c) - (uint)*(ushort *)(this + 0x90))) {
    nodePtr = FUN_005fcd80((uint)*(ushort *)(query + 3));
  }
  else {
    if (((*(ushort *)((int)query + 10) & 0x4000) != 0) || (nodePtr = FUN_005fcde0(), nodePtr == 0))
    goto LAB_005fd324;
    if ((*(ushort *)((int)query + 10) & 0x2000) != 0) {
      // Copy data from node array at offset 0x20 into local buffer (transform?)
      local_2c = *(undefined8 *)
                  (*(int *)(this + 0x20) + (uint)*(ushort *)((int)query + 6) * 0x24);
      int iVar2 = *(int *)(this + 0x20) + (uint)*(ushort *)((int)query + 6) * 0x24;
      local_24 = *(undefined8 *)(iVar2 + 8);
      local_1c = *(undefined8 *)(iVar2 + 0x10);
      local_14 = *(undefined8 *)(iVar2 + 0x18);
      local_c = *(undefined4 *)(iVar2 + 0x20);
      local_38 = 0;
      local_34 = 0;
      local_30 = 0;
      local_3c = &PTR_LAB_00e4081c;
      local_44 = nodePtr;
      FUN_00602490(&local_2c, &local_3c, DAT_00e2eb58);
      success = FUN_005f5cb0(&local_44, &local_40);
      nodePtr = local_44;
      if (success == '\0') {
        *(ushort *)((int)query + 10) = *(ushort *)((int)query + 10) | 0x4000;
      }
      else {
        dist = (float10)FUN_0045c4b0(&local_2c, local_40);
        *query = (float)dist;
        local_40 = local_40 - *(int *)(nodePtr + 0x20);
        *(short *)(query + 1) =
             ((short)(local_40 / 0x24) + (short)(local_40 >> 0x1f)) -
             (short)((longlong)local_40 * 0x38e38e39 >> 0x3f);
      }
      *(ushort *)((int)query + 10) = *(ushort *)((int)query + 10) & 0xdfff;
      FUN_005fc970();
    }
  }
  if (nodePtr != 0) {
    uVar1 = *(ushort *)(query + 1);
    int offset = *(int *)(nodePtr + 0x20);
    outLink[1] = 0;
    *outLink = nodePtr;
    outLink[1] = *(int *)(nodePtr + 4);
    *(int **)(nodePtr + 4) = outLink;
    outLink[2] = offset + (uint)uVar1 * 0x24;
    return;
  }
LAB_005fd324:
  *outLink = 0;
  outLink[1] = 0;
  outLink[2] = 0;
  return;
}