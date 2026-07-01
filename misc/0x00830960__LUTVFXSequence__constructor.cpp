// FUNC_NAME: LUTVFXSequence::constructor
undefined4 * __fastcall LUTVFXSequence::constructor(undefined4 *this)
{
  undefined4 uVar1;
  undefined1 *puVar2;
  int local_10 [3];
  code *local_4;
  
  // Call base class constructor
  FUN_0082e7e0();
  
  // Set vtable pointer
  *this = &PTR_FUN_00d73934;
  
  // Register class name with memory manager
  FUN_004d3bc0("LUTVFXSequence");
  
  // Initialize local scope (likely RAII scope guard)
  FUN_004d3e20(local_10);
  
  // Get string from offset +0x10 (param_1[4])
  puVar2 = (undefined1 *)this[4];
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e; // Default string
  }
  
  // Load resource by name
  uVar1 = FUN_004dafd0(puVar2);
  this[3] = uVar1; // Store resource handle at +0x0C
  
  // Cleanup local scope if needed
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]);
  }
  
  return this;
}