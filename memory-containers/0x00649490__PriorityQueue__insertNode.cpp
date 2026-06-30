// FUNC_NAME: PriorityQueue::insertNode
void __fastcall PriorityQueue::insertNode(int this, int node)
{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  
  // Get the priority value from the node (offset +0x4, lower 31 bits)
  uVar6 = *(uint *)(this + 4) & 0xfffffffe;
  
  // Convert to float (handle negative values with magic constant)
  fVar1 = (float)(int)uVar6;
  if ((int)uVar6 < 0) {
    fVar1 = fVar1 + DAT_00e44578; // 0x4f800000 (magic float constant for int-to-float conversion)
  }
  
  // Calculate bucket index based on exponent of float representation
  uVar5 = ((uint)fVar1 >> 0x17) - 0x7f; // Extract exponent, subtract bias
  if (uVar5 < 6) {
    uVar5 = 6; // Minimum bucket index
  }
  uVar5 = uVar5 - 6; // Normalize to 0-based
  if (7 < uVar5) {
    uVar5 = 7; // Maximum bucket index (8 buckets total)
  }
  
  // Calculate bucket start address (each bucket is 0x20 bytes)
  node = node + uVar5 * 0x20;
  
  // Get the head of the bucket's linked list (offset +0x78 from bucket start)
  iVar7 = node + 0x78;
  iVar4 = *(int *)(node + 0x90); // First node in bucket's list
  
  // Find insertion point in sorted order (ascending priority)
  iVar3 = iVar7;
  while ((iVar2 = iVar4, iVar2 != iVar7 && ((*(uint *)(iVar2 + 4) & 0xfffffffe) < uVar6))) {
    iVar3 = iVar2;
    iVar4 = *(int *)(iVar2 + 0x18); // Next node pointer (offset +0x18)
  }
  
  // Insert node into doubly-linked list
  *(int *)(this + 0x14) = iVar3; // Previous pointer (offset +0x14)
  *(undefined4 *)(this + 0x18) = *(undefined4 *)(iVar3 + 0x18); // Next pointer (offset +0x18)
  *(int *)(iVar3 + 0x18) = this; // Update previous node's next
  *(int *)(*(int *)(this + 0x18) + 0x14) = this; // Update next node's previous
  return;
}