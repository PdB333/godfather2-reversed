// FUNC_NAME: PlayerActionableInfo::constructor
undefined4 * __fastcall PlayerActionableInfo::constructor(int this)
{
  undefined4 uVar1;
  undefined4 *pNewObj;
  undefined4 *pDst;
  undefined4 *pSrc;
  int i;
  undefined4 allocSize;
  undefined4 allocType;
  undefined4 allocAlign;
  
  pNewObj = (undefined4 *)FUN_009c8f80(); // likely memory manager singleton
  allocSize = 2;
  allocType = 0x10;
  allocAlign = 0;
  pDst = (undefined4 *)(**(code **)*pNewObj)(0xb0, &allocSize); // allocate 0xB0 bytes
  pNewObj = (undefined4 *)0x0;
  if (pDst != (undefined4 *)0x0) {
    FUN_00473950(this); // base class constructor
    *pDst = &PTR_FUN_00d5f1f0; // vtable pointer
    pDst[2] = &PTR_LAB_00d5f1e8; // another vtable or function pointer
    FUN_00473750(); // some initialization
    pDst[0x28] = 0; // member at +0xA0 (0x28*4)
    pNewObj = pDst;
  }
  uVar1 = _DAT_00d5f1e0; // global data
  pSrc = (undefined4 *)(this + 0x60); // source at this+0x60
  pDst = pNewObj + 0x18; // destination at newObj+0x60 (0x18*4)
  for (i = 0x10; i != 0; i = i + -1) {
    *pDst = *pSrc;
    pSrc = pSrc + 1;
    pDst = pDst + 1;
  }
  pSrc = (undefined4 *)(this + 0x60); // source again
  pDst = pNewObj + 8; // destination at newObj+0x20 (8*4)
  for (i = 0x10; i != 0; i = i + -1) {
    *pDst = *pSrc;
    pSrc = pSrc + 1;
    pDst = pDst + 1;
  }
  FUN_00473b10(uVar1); // finalize
  return pNewObj;
}