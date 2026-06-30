// FUNC_NAME: RefCountedPtr::assign
// Address: 0x005e1150
// Role: Assignment operator for a reference-counted smart pointer.
//   Manages a reference to a shared object (param_1) with a resource ID (param_2).
//   Uses vtable functions at offsets 0x04 (Release?), 0x08 (AddRef?), 0x0C (SomeFinalize?).
//   Increments reference count when param_2 != 0, otherwise sets to null.

void __thiscall RefCountedPtr::assign(int *this, int *pObject, int resourceId)
{
  int *pObj; // originally piVar2
  int refHandle; // originally uVar1

  pObj = pObject;

  // Call vtable[2] (offset 0x08) on the object – likely AddRef or Release?
  // At start, this might be cleaning up the current stored object.
  ((void (*)(int *))((int *)pObject[0])[2])(pObject);

  // Determine reference handle based on resourceId
  if (resourceId == 0) {
    refHandle = 0;
  } else {
    refHandle = FUN_004265d0(resourceId, pObj);
  }

  // Store the reference handle inside the smart pointer
  FUN_005e1480(pObj, refHandle);

  // Save the raw object pointer in this+0x0C
  *(int **)((int)this + 0x0C) = pObject;

  // Call vtable[2] again – possibly AddRef/Release on the newly stored object?
  // Note: argument missing in decompiled output, likely still pObject
  ((void (*)(void))((int *)pObject[0])[2])();

  if (resourceId != 0) {
    // Acquire a second handle using the stored object pointer
    refHandle = FUN_004265d0(resourceId, *(int **)((int)this + 0x0C));
    *(int *)((int)this + 0x10) = refHandle;

    // Call vtable[1] (offset 0x04) with resourceId and 0 – perhaps Release old resource?
    ((void (*)(int, int))((int *)pObject[0])[1])(resourceId, 0);

    // Call vtable[3] (offset 0x0C) – finalize or update reference count?
    ((void (*)(void))((int *)pObject[0])[3])();
    return;
  }

  // No resourceId: set handle to 0
  *(int *)((int)this + 0x10) = 0;

  // Call vtable[3] to finalize
  ((void (*)(void))((int *)pObject[0])[3])();
  return;
}