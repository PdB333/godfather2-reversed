// Xbox PDB: EARS_Modules_TOD_NightDayControlTODSequence_NightDayControlTODSequence
// FUNC_NAME: NightDayControlTODSequence::constructor
undefined4 * __fastcall NightDayControlTODSequence::constructor(undefined4 *this)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  int local_10 [3];
  code *local_4;
  
  FUN_00830040(); // Base class constructor
  *this = &PTR_FUN_00d73a38; // vtable pointer
  this[9] = 1; // +0x24 - some flag (e.g., enabled)
  FUN_004d3bc0("NightDayControlTODSequence"); // String allocation/registration
  FUN_004d3e20(local_10); // Get current time of day (TOD) data
  puVar2 = (undefined1 *)this[4]; // +0x10 - pointer to sequence data
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e; // Default sequence data
  }
  uVar1 = FUN_004dafd0(puVar2); // Initialize sequence from data
  this[3] = uVar1; // +0x0C - store sequence handle/ID
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]); // Cleanup TOD data
  }
  return this;
}