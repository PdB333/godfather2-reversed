// Xbox PDB: EARS_Godfather_SetFogMessage_GetClassName
// FUNC_NAME: WeatherManager::constructor
undefined4 * __fastcall WeatherManager::constructor(undefined4 *this)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  int local_10 [3];
  code *local_4;
  
  // Initialize member variables
  this[1] = 0;  // +0x04: some flag/state
  this[2] = 0;  // +0x08: 
  this[3] = 0;  // +0x0C: 
  this[4] = 0;  // +0x10: 
  this[5] = 0;  // +0x14: 
  this[6] = 0;  // +0x18: 
  this[7] = 0;  // +0x1C: 
  *(undefined1 *)(this + 8) = 1;  // +0x20: boolean flag (true)
  *this = &PTR_FUN_00d738c0;  // +0x00: vtable pointer
  this[9] = 1;  // +0x24: some count/index
  FUN_008334a0();  // Subsystem initialization
  this[0xc] = &PTR_LAB_00d7366c;  // +0x30: another vtable/function pointer
  *(undefined8 *)(this + 0x24) = 0;  // +0x90: clear 8 bytes
  *(undefined8 *)(this + 0x26) = 0;  // +0x98: clear 8 bytes
  *(undefined8 *)(this + 0x28) = 0;  // +0xA0: clear 8 bytes
  *(undefined8 *)(this + 0x2a) = 0;  // +0xA8: clear 8 bytes
  FUN_009cbee0();  // Another initialization
  this[0x2c] = &PTR_FUN_00d73784;  // +0xB0: vtable/function pointer
  this[0x2d] = 0;  // +0xB4: null
  uVar1 = FUN_009c8e80(0x40);  // Allocate 0x40 bytes
  this[0x2e] = uVar1;  // +0xB8: pointer to allocated memory
  this[0x2f] = 0;  // +0xBC: null
  this[0x30] = 0x10;  // +0xC0: size/count (16)
  
  // Setup message handler for "SetFogMessage"
  local_10[0] = 0;
  local_10[1] = 0;
  local_10[2] = 0;
  local_4 = (code *)0x0;
  FUN_004d4ad0(local_10, &DAT_00e2f0b0, "SetFogMessage", "Sequence");
  FUN_004d3e20(local_10);
  
  // Get string from this[4] or use default
  puVar2 = (undefined1 *)this[4];  // +0x10: string pointer
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e;  // Default string
  }
  uVar1 = FUN_004dafd0(puVar2);  // Hash/register string
  this[3] = uVar1;  // +0x0C: store result
  
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]);  // Cleanup message handler
  }
  return this;
}