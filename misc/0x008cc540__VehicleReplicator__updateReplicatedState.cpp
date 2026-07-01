// FUNC_NAME: VehicleReplicator::updateReplicatedState
void __thiscall VehicleReplicator::updateReplicatedState(int thisPtr, int* replicationData)
{
  int currentNode;
  int lastNode;
  int headNode;
  
  // Check if processing is not suppressed (bit 4 of flags)
  if ((*(uint *)(thisPtr + 4) >> 4 & 1) == 0) {
    // Find the last node in the first linked list starting from replicationData[0]
    headNode = *replicationData;
    lastNode = headNode;
    for (currentNode = *(int *)(headNode + 0xc); currentNode != 0; currentNode = *(int *)(currentNode + 0xc)) {
      lastNode = currentNode;
    }
    
    // Check if there's a matching composite key (base + offset)
    if (*(char *)(lastNode + 0x10) + lastNode == replicationData[3]) {
      // Follow second list from replicationData[1]
      headNode = replicationData[1];
      for (currentNode = *(int *)(replicationData[1] + 0xc); currentNode != 0; currentNode = *(int *)(currentNode + 0xc)) {
        headNode = currentNode;
      }
      lastNode = headNode;
    }
    else {
      // Keep the original lastNode from first list
      for (currentNode = *(int *)(headNode + 0xc); currentNode != 0; currentNode = *(int *)(currentNode + 0xc)) {
        lastNode = currentNode;
      }
    }
    
    // Check node type via function call
    int nodeType = FUN_00541470(*(undefined4 *)(lastNode + 0x1c));
    if (nodeType != 0x10) {
      int nodeDataPtr = *(char *)(lastNode + 0x10) + lastNode;
      if ((nodeType == 5) && (*(char *)(*(int *)(thisPtr + 0xc) + 0xd8) == '\a')) {
        // Case 1: Node type 5 and some condition on this object
        replicationData[8] = 1;
        // Compare squared magnitude of velocity
        if (*(float *)(thisPtr + 0x14) * *(float *)(thisPtr + 0x14) +
            *(float *)(thisPtr + 0x18) * *(float *)(thisPtr + 0x18) +
            *(float *)(thisPtr + 0x1c) * *(float *)(thisPtr + 0x1c) <
            // vs some threshold from node data
            *(float *)(nodeDataPtr + 0x1a0) * *(float *)(nodeDataPtr + 0x1a0) +
            *(float *)(nodeDataPtr + 0x1a4) * *(float *)(nodeDataPtr + 0x1a4) +
            *(float *)(nodeDataPtr + 0x1a8) * *(float *)(nodeDataPtr + 0x1a8)) {
          // Copy position/velocity from node data
          *(undefined4 *)(thisPtr + 0x14) = *(undefined4 *)(nodeDataPtr + 0x1a0);
          *(undefined4 *)(thisPtr + 0x18) = *(undefined4 *)(nodeDataPtr + 0x1a4);
          *(undefined4 *)(thisPtr + 0x1c) = *(undefined4 *)(nodeDataPtr + 0x1a8);
          *(undefined4 *)(thisPtr + 0x20) = *(undefined4 *)(nodeDataPtr + 0x1ac);
        }
      }
      else {
        // Case 2: Default handling - call external function
        FUN_009f66e0(replicationData[9], *(undefined4 *)(thisPtr + 0xc), lastNode,
                     *(undefined4 *)(replicationData[0xb] + 4), _DAT_00e5451c, _DAT_0112f984);
      }
      // Set flags: bit 0 (dirty?) and bit 2 (updated?)
      *(uint *)(thisPtr + 4) = *(uint *)(thisPtr + 4) | 5;
      
      // If bit 3 not set, set it and possibly broadcast
      if (((*(uint *)(thisPtr + 4) >> 3 & 1) == 0) &&
         (*(uint *)(thisPtr + 4) = *(uint *)(thisPtr + 4) | 8, DAT_012069f4 != 0)) {
        FUN_00408900(thisPtr + -0x20, &DAT_012069f4, 0x8000);
      }
    }
  }
  return;
}