// FUNC_NAME: EARS::Framework::ListHead::operator=
undefined4 * __thiscall EARS::Framework::ListHead::operator=(EARS::Framework::ListHead &this, const EARS::Framework::ListHead &other)
{
  int *oldPointerField;
  int newPointerValue;
  
  // Copy first field (offset 0x00)
  this.field0 = other.field0;
  
  // Handle pointer field at offset +0x04 (linked list head pointer)
  oldPointerField = &this.pointerField; // parm_1+1
  if (oldPointerField != &other.pointerField) {
    newPointerValue = other.pointerField;
    if (*oldPointerField != newPointerValue) {
      // Release old pointer if non-null (deallocate or remove from list)
      if (*oldPointerField != 0) {
        this.releasePointerField(oldPointerField); // FUN_004daf90
      }
      *oldPointerField = newPointerValue;
      if (newPointerValue != 0) {
        // Update intrusive list: save the old next pointer from the node, then point the node back to this head
        this.nextPointer = *(int *)(newPointerValue + 4); // +0x04 from node data
        *(int **)(newPointerValue + 4) = oldPointerField; // node->prevHead = &this.pointerField
      }
    }
  }
  
  // Copy remaining fields (offsets 0x0C, 0x14, 0x1C, 0x20, 0x24)
  // Note: field layout: 
  // +0x0C: fieldC (8 bytes, likely two ints or a float2)
  // +0x14: field14 (8 bytes)
  // +0x1C: field1C (4 bytes)
  // +0x20: field20 (4 bytes)
  // +0x24: field24 (4 bytes)
  *(undefined8 *)(&this.fieldC) = *(undefined8 *)(&other.fieldC);
  *(undefined8 *)(&this.field14) = *(undefined8 *)(&other.field14);
  this.field1C = other.field1C;
  this.field20 = other.field20;
  this.field24 = other.field24;
  
  return &this;
}