// FUNC_NAME: EARS::Framework::Object::constructor
void __thiscall EARSObject_constructor(void *this)
{
  undefined4 *vtablePtr; // in_EAX
  undefined4 uVar1;
  int iVar2;
  int esi; // unaff_ESI
  int *piVar3;
  
  piVar3 = (int *)*vtablePtr;
  iVar2 = vtablePtr[1];
  // Call base class constructor (vtable +8)
  (**(code **)(*piVar3 + 8))(piVar3);
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_004265d0(iVar2,piVar3);
  }
  // Initialize object with parent and data
  FUN_004ca9a0(esi,piVar3,uVar1);
  // Create a linked list node (likely for object tracking)
  iVar2 = FUN_004cac00();
  *(int *)(esi + 0x1c) = iVar2; // +0x1c: linked list node pointer
  *(undefined1 *)(iVar2 + 0x15) = 1; // +0x15: flag (1 = valid/active)
  // Initialize circular doubly-linked list (node points to itself)
  *(int *)(*(int *)(esi + 0x1c) + 4) = *(int *)(esi + 0x1c); // +0x04: prev = self
  *(undefined4 *)*(undefined4 *)(esi + 0x1c) = *(undefined4 *)(esi + 0x1c); // +0x00: next = self
  *(int *)(*(int *)(esi + 0x1c) + 8) = *(int *)(esi + 0x1c); // +0x08: some pointer = self
  *(undefined4 *)(esi + 0x20) = 0; // +0x20: some flag/pointer = null
  return;
}