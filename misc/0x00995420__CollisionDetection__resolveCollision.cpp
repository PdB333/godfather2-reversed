// FUNC_NAME: CollisionDetection::resolveCollision
void __thiscall CollisionDetection::resolveCollision(int *this)
{
  int *node;
  int *lastNode;
  int *currentNode;
  int *prevNode;
  int entity;
  float dx1, dy1, dz1;
  float dx2, dy2, dz2;
  float crossX, crossY, crossZ;
  float normalX, normalY, normalZ;
  int unused;
  
  // Traverse linked list to find last node (tail)
  currentNode = (int *)*this;  // head of list
  lastNode = currentNode;
  for (node = (int *)currentNode[3]; node != (int *)0x0; node = (int *)node[3]) {
    lastNode = node;
  }
  
  // If the last node matches the current context node (this[3] + 0x10)
  if ((int *)(this[3] + 0x10) == lastNode) {
    currentNode = (int *)this[1];  // alternate head
  }
  
  entity = *currentNode;
  prevNode = (int *)currentNode[3];
  
  // Traverse again to find the last node from prevNode
  while (node = prevNode, node != (int *)0x0) {
    currentNode = node;
    prevNode = (int *)node[3];
  }
  
  // Check entity type at offset +0x0C
  if (*(int *)(entity + 0xc) == 4) {
    // Calculate cross product of two edge vectors
    // Entity has vertices at offsets +0x20, +0x28, +0x30, +0x38, +0x40, +0x48
    dx1 = *(float *)(entity + 0x38) - *(float *)(entity + 0x28);  // edge1.x
    dx2 = *(float *)(entity + 0x48) - *(float *)(entity + 0x28);  // edge2.x
    dy1 = *(float *)(entity + 0x30) - *(float *)(entity + 0x20);  // edge1.y
    dy2 = *(float *)(entity + 0x40) - *(float *)(entity + 0x20);  // edge2.y
    dz1 = *(float *)(entity + 0x44) - *(float *)(entity + 0x24);  // edge1.z
    dz2 = *(float *)(entity + 0x34) - *(float *)(entity + 0x24);  // edge2.z
    
    // Cross product: normal = edge1 x edge2
    crossX = dx1 * dy2 - dx2 * dy1;
    crossY = dx2 * dz1 - dx1 * dz2;
    crossZ = dz1 * dy1 - dy2 * dz1;  // Note: this is actually dz1*dy1 - dy2*dz1, likely a bug or specific convention
    
    // Normalize the cross product
    unused = 0;
    FUN_00aa2cd0(currentNode[2], &crossX);  // Normalize function
    
    // Check dot product with another vector (this[4] + 0x10, 0x14, 0x18)
    entity = this[4];
    if (*(float *)(entity + 0x18) * crossZ + *(float *)(entity + 0x14) * crossX +
        crossY * *(float *)(entity + 0x10) < 0.0f) {
      this[8] = 1;  // Set collision flag
      return;
    }
  }
  else {
    // For other entity types, check a property via function call
    entity = FUN_00541470(prevNode[7]);  // Get some type/state
    if (entity == 5) {
      // Check if Y component is negative (pointing downward)
      if (*(float *)(this[4] + 0x14) <= 0.0f && *(float *)(this[4] + 0x14) != 0.0f) {
        this[8] = 1;  // Set collision flag
      }
    }
    else if (entity != 8) {
      return;  // No collision for other types
    }
    
    // Check if both nodes have a specific flag at offset +0x80
    entity = (int)(char)prevNode[4] + (int)prevNode;
    if ((*(char *)(this[3] + 0x80) == '\x01') && (*(char *)(entity + 0x80) == '\x01')) {
      // Trigger some visual/audio effect
      FUN_009f66e0(this[9], this[3], entity, *(undefined4 *)(this[0xb] + 4), 0x3f800000, 0);
    }
  }
  return;
}