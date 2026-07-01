// FUNC_NAME: SomeGameObject::~SomeGameObject

void __thiscall SomeGameObject::~SomeGameObject(SomeGameObject *this)
{
  uint *pPtr;
  void *pTls;

  // Set vtable pointers to cleanup vtables (possible base class destructors)
  this->vtable = &PTR_FUN_00d6a2a8;                // +0x00
  *(uint *)((int)this + 0x3C) = &PTR_LAB_00d6a298; // +0x3C
  *(uint *)((int)this + 0x48) = &PTR_LAB_00d6a294; // +0x48
  *(uint *)((int)this + 0x50) = &PTR_LAB_00d6a290; // +0x50
  *(uint *)((int)this + 0x54) = &PTR_LAB_00d6a230; // +0x54
  *(uint *)((int)this + 0x58) = &PTR_LAB_00d6a1c8; // +0x58

  // Initialize / destroy sub-objects (likely lists or strings)
  subobjectInit(&DAT_0120e93c);
  subobjectInit(&DAT_0112a618);
  subobjectInit(&DAT_0112a5cc);
  subobjectInit(&DAT_0112a600);
  subobjectInit(&DAT_0112a628);
  subobjectInit(&DAT_0112a5f0);
  subobjectInit(&DAT_0112a5e8);
  subobjectInit(&DAT_0112a5d8);
  subobjectInit(&DAT_0112a620);

  subobjectInit(this + 0x274);  // +0x274
  subobjectRelease(this + 0x274);
  subobjectInit(this + 0x27C);  // +0x27C
  subobjectRelease(this + 0x27C);
  subobjectInit(this + 0x284);  // +0x284
  subobjectRelease(this + 0x284);
  subobjectInit(this + 0x28C);  // +0x28C
  subobjectRelease(this + 0x28C);
  subobjectInit(this + 0x294);  // +0x294
  subobjectRelease(this + 0x294);
  subobjectRelease(this + 0x29C);  // +0x29C

  // Release optional container (byte flag at +0x428)
  if (*(char *)(this + 0x428) != '\0') {
    releaseContainer(0x10, this + 0x3C);   // +0x3C (list head?)
    *(char *)(this + 0x428) = 0;
  }
  releaseContainer(2, this + 0x3C);   // general release

  // Deallocate pointer at +0x32C using TLS free list
  pPtr = *(uint **)(this + 0x32C);  // +0x32C
  if (pPtr != (uint *)0x0) {
    pTls = TlsGetValue(DAT_01139810);
    if (*(int *)((int)pTls + 0x6C) < *(int *)((int)pTls + 0x34)) {
      *(int *)((int)pTls + 0x6C) = *(int *)((int)pTls + 0x6C) + 1;
      *pPtr = *(uint *)((int)pTls + 0x68);
      *(uint **)((int)pTls + 0x68) = pPtr;
    }
    else {
      customDeallocate(6, pPtr, 0x27);  // size hint 0x27
    }
  }

  // Call destructor via vtable on object at +0x394
  if (*(uint *)(this + 0x394) != 0) {
    (*(code (__thiscall **)(int))(* (uint *)(this + 0x394) ))(1);
  }

  // Deallocate pointer at +0x390 using TLS free list (different pool)
  pPtr = *(uint **)(this + 0x390);  // +0x390
  if (pPtr != (uint *)0x0) {
    pTls = TlsGetValue(DAT_01139810);
    if (*(int *)((int)pTls + 0x84) < *(int *)((int)pTls + 0x34)) {
      *(int *)((int)pTls + 0x84) = *(int *)((int)pTls + 0x84) + 1;
      *pPtr = *(uint *)((int)pTls + 0x80);
      *(uint **)((int)pTls + 0x80) = pPtr;
    }
    else {
      customDeallocate(9, pPtr, 9);  // size hint 9
    }
  }

  // Additional destruction steps
  destroyGlobalList_0();       // FUN_00794600(0)
  freeMemory(0x18, this);      // FUN_008f67c0(0x18, this) – possibly deallocate this?

  // Destroy any string resources at +0x41C and +0x348
  if ((int)this[0x107] != 0) {
    destroyString(this + 0x41C);   // +0x41C (string object)
  }
  destroyGlobalList_1();       // FUN_009a3550()

  if ((int)this[0xD2] != 0) {
    destroyString(this + 0x348);   // +0x348 (string object)
  }
  destroyFinal();              // FUN_005419a0()
}