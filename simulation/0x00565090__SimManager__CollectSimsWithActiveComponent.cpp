// FUNC_NAME: SimManager::CollectSimsWithActiveComponent
// Address: 0x00565090
// Collects IDs from managed entities that have at least one sub-object with a non-null flag at offset 0x129.
// Offsets:
// +0x124: count of managed entities (int)
// +0x24: pointer array of managed entities (int*)
// +0x10 (per entity): count of sub-object pointers (int)
// +0x3c (per entity): ID field to output (uint)
// +0x129 (per sub-object): flag byte – if non-zero, parent entity is collected

void __thiscall SimManager::CollectSimsWithActiveComponent(uint *outBuffer)
{
  int entityCount = *(int *)(this + 0x124);
  uint collectedCount = 0;
  int collectedEntities[64];  // Temporary buffer for entity pointers (max 64)
  
  if (entityCount != 0) {
    int *entityPtr = (int *)(this + 0x24);
    for (int i = 0; i < entityCount; i++) {
      int entity = *entityPtr;
      uint subObjCount = *(uint *)(entity + 0x10);
      
      if (subObjCount != 0) {
        for (uint j = 0; j < subObjCount; j++) {
          int subObj = *(int *)(entity + j * 4);  // Get sub-object pointer
          // Check flag at offset 0x129
          if (*(char *)(subObj + 0x129) != '\0') {
            if (collectedCount < 0x40) {  // buffer limit
              collectedEntities[collectedCount] = entity;
              collectedCount++;
            }
            break;  // Only need one active sub-object per entity
          }
        }
      }
      entityPtr++;
    }
  }
  
  // Output: first element is count, followed by IDs
  *outBuffer = collectedCount;
  outBuffer++;  // Now points to the start of the ID array
  
  if (collectedCount != 0) {
    // Copy IDs from collected entities to output buffer
    int baseDiff = (int)collectedEntities - (int)outBuffer;  // for pointer arithmetic
    for (uint k = 0; k < collectedCount; k++) {
      *outBuffer = *(uint *)(*(int *)(baseDiff + (int)outBuffer) + 0x3c);
      outBuffer++;
    }
  }
  return;
}