// FUNC_NAME: EARS::Framework::ObjectLink::constructor
undefined4 * __thiscall EARS::Framework::ObjectLink::constructor(undefined4 *this, int parentObject, undefined8 *data, int *extraData)
{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  *this = &PTR_FUN_00d74308; // vtable pointer
  piVar1 = this + 4; // +0x10: previous link pointer
  piVar2 = this + 6; // +0x18: next link pointer
  *piVar1 = 0;
  this[5] = 0; // +0x14: next link pointer (alternate)
  *piVar2 = 0;
  this[7] = 0; // +0x1C: previous link pointer (alternate)
  this[8] = 0; // +0x20: extra data pointer
  
  if (parentObject == 0) {
    parentObject = 0;
  }
  else {
    parentObject = parentObject + 0x48; // offset to link list head
  }
  
  if (*piVar1 != parentObject) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1); // likely unlink or release
    }
    *piVar1 = parentObject;
    if (parentObject != 0) {
      this[5] = *(undefined4 *)(parentObject + 4); // store next pointer
      *(int **)(parentObject + 4) = piVar1; // update list head
    }
  }
  
  *(undefined8 *)(this + 1) = *data; // +0x04: store data (8 bytes)
  this[3] = *(undefined4 *)(data + 1); // +0x0C: store additional data
  
  if (extraData != (int *)0x0) {
    if (piVar2 != extraData) {
      iVar3 = *extraData;
      if (*piVar2 != iVar3) {
        if (*piVar2 != 0) {
          FUN_004daf90(piVar2);
        }
        *piVar2 = iVar3;
        if (iVar3 != 0) {
          this[7] = *(undefined4 *)(iVar3 + 4);
          *(int **)(iVar3 + 4) = piVar2;
        }
      }
    }
    this[8] = extraData[2]; // +0x20: store extra data value
  }
  return this;
}