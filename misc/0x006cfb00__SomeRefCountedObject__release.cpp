// FUNC_NAME: SomeRefCountedObject::release
// Function address: 0x006cfb00
// This appears to be a destructor / release method for a reference-counted object.
// It sets vtable pointers, decrements reference count, then cleans up sub-objects and resources.

void __thiscall SomeRefCountedObject::release(SomeRefCountedObject *this)
{
  int *refCountBlock; // piVar2 - pointer to reference count structure at this+0xD8
  int *piVar1;
  int iVar3;

  refCountBlock = (int *)this[0x36]; // offset +0xD8: pointer to ref count block
  this->vtable = &PTR_FUN_00d5f228; // restore vtable to base class
  this[0x0f] = &PTR_LAB_00d5f214;   // offset +0x3C: set another vtable/function pointer
  this[0x12] = &PTR_LAB_00d5f210;   // offset +0x48
  this[0x14] = &PTR_LAB_00d5f20c;   // offset +0x50

  // Decrement reference count
  piVar1 = refCountBlock + 1; // +4 bytes from refCountBlock -> actual ref count
  *piVar1 = *piVar1 - 1;
  if (*piVar1 == 0) {
    // If ref count hit zero, call the delete function stored in the ref count block
    (*(code **)(*refCountBlock + 4))(refCountBlock); // call delete via function pointer
  }

  // Destroy sub-object at this+0xB4 (offset 0x2d)
  FUN_004086d0(this + 0x2d); // likely destructor or cleanup
  FUN_00408310(this + 0x2d);
  // Destroy sub-object at this+0xBC (offset 0x2f)
  FUN_004086d0(this + 0x2f);
  FUN_00408310(this + 0x2f);

  // Call base class destructor or common cleanup
  FUN_0089ffc0(this);

  // Check two resource pointers at offsets 0xC8 and 0xD0 (0x32 and 0x34)
  if (this[0x32] == 0) {
    FUN_004df600(); // global shutdown if already null? maybe error handling
  }
  if (this[0x34] == 0) {
    FUN_004df600();
  }

  // Clean up resource pointer at +0xD0
  iVar3 = this[0x34];
  if (iVar3 != 0) {
    *(undefined4 *)(iVar3 + 8) = 0; // maybe set a flag or clear pointer
    this[0x34] = 0;
  }
  // Clean up resource pointer at +0xC8
  iVar3 = this[0x32];
  if (iVar3 != 0) {
    *(undefined4 *)(iVar3 + 8) = 0;
    this[0x32] = 0;
  }

  FUN_00473880(); // final global cleanup
  return;
}