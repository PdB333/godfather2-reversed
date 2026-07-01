// Xbox PDB: EARS_Modules_TOD_ToneMappingTODSequence_ToneMappingTODSequence
// FUNC_NAME: ToneMappingTODSequence::constructor
undefined4 * __fastcall ToneMappingTODSequence::constructor(undefined4 *this)
{
  undefined4 uVar1;
  undefined1 *puVar2;
  int local_10 [3];
  code *local_4;
  
  // Call base class constructor
  FUN_0082fbe0();
  
  // Set vtable pointer
  *this = &PTR_FUN_00d73a00;
  
  // Initialize some member to 1 (likely enabled flag)
  this[9] = 1;
  
  // Register with the string "ToneMappingTODSequence"
  FUN_004d3bc0("ToneMappingTODSequence");
  
  // Get some sequence data
  FUN_004d3e20(local_10);
  
  // Get pointer to some data (offset +0x10)
  puVar2 = (undefined1 *)this[4];
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e;
  }
  
  // Process the data
  uVar1 = FUN_004dafd0(puVar2);
  this[3] = uVar1;
  
  // Cleanup if needed
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]);
  }
  
  return this;
}