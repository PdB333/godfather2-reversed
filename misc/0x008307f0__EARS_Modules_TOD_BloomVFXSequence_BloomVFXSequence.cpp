// Xbox PDB: EARS_Modules_TOD_BloomVFXSequence_BloomVFXSequence
// FUNC_NAME: BloomVFXSequence::BloomVFXSequence
undefined4 * __fastcall BloomVFXSequence::BloomVFXSequence(undefined4 *this)
{
  undefined4 uVar1;
  char *dataPtr;
  int cleanupHandle;
  code *cleanupFunc;

  // Base class constructor or initialization
  FUN_0082e5e0();

  // Set vtable pointer to BloomVFXSequence vtable
  *this = &BloomVFXSequence_vtable;

  // Log or register the class name "BloomVFXSequence"
  FUN_004d3bc0("BloomVFXSequence");

  // Push a cleanup scope: cleanupHandle is used for destruction order
  cleanupFunc = FUN_004d3e20(&cleanupHandle);

  // Retrieve data pointer from this+0x10 (field at offset +0x10)
  dataPtr = (char *)this[4];
  if (dataPtr == (char *)0x0) {
    dataPtr = &DAT_0120546e; // Default data if null
  }

  // Load or assign resource based on dataPtr, store result at this+0x0C (field at offset +0x0C)
  uVar1 = FUN_004dafd0(dataPtr);
  this[3] = uVar1;

  // Execute cleanup if handle is non-zero
  if (cleanupHandle != 0) {
    (*cleanupFunc)(cleanupHandle);
  }

  // Post-constructor initialization
  FUN_0082caa0();

  return this;
}