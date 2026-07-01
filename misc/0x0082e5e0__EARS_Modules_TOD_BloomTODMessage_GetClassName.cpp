// Xbox PDB: EARS_Modules_TOD_BloomTODMessage_GetClassName
// FUNC_NAME: BloomTODManager::constructor

undefined4 * __fastcall BloomTODManager::constructor(BloomTODManager *this)
{
  undefined4 uVar1;
  byte *pString;
  int msgKey[3]; // stack-based message key structure
  code *cleanupFunc; // destructor/cleanup for msgKey
  
  // Initialize fields at offset +4 to +28 (indices 1-7) to 0
  this->field_04 = 0;
  this->field_08 = 0;
  this->field_0C = 0;
  this->field_10 = 0;
  this->field_14 = 0;
  this->field_18 = 0;
  this->field_1C = 0;
  
  // Set byte at offset +32 to 1 (likely a flag)
  *(byte *)&this->field_20 = 1;
  
  // Set vtable pointer at offset 0
  this->vtable = &BloomTODManager_vtable_00d73790;
  
  // Set field at offset +36 to 1
  this->field_24 = 1;
  
  // Call base class or other initialization
  unknownBaseClassInit(); // FUN_008297a0
  
  // Set second vtable pointer at offset +224
  this->secondVtable = &BloomTODManager_vtable2_00d7378c;
  this->field_0xE4 = 0;
  
  // Allocate 64 bytes for a buffer
  uVar1 = heapAllocate(0x40); // FUN_009c8e80
  this->buffer = uVar1;
  this->bufferSize = 0;
  this->bufferCapacity = 0x10; // 16 elements?
  
  // Initialize message key structure
  msgKey[0] = 0;
  msgKey[1] = 0;
  msgKey[2] = 0;
  cleanupFunc = (code *)0x0;
  
  // Register a message named "BloomTODMessage" with component "Sequence"
  registerMessage(msgKey, &BloomTODString, "BloomTODMessage", "Sequence"); // FUN_004d4ad0
  
  // Execute or finalize message registration
  finalizeMessage(msgKey); // FUN_004d3e20
  
  // Get string at offset +16 (raw pointer)
  pString = (byte *)this->field_10;
  if (pString == (byte *)0x0) {
    pString = (byte *)&defaultString_0120546e;
  }
  
  // Process string to get some ID or value
  uVar1 = processString(pString); // FUN_004dafd0
  this->field_0C = uVar1;
  
  // Cleanup message key if needed
  if (msgKey[0] != 0) {
    (*cleanupFunc)(msgKey[0]);
  }
  
  return (undefined4 *)this;
}

// Member field offsets (in bytes from this):
// +0x00: vtable
// +0x04: field_04
// +0x08: field_08
// +0x0C: field_0C (result of processString)
// +0x10: field_10 (string pointer)
// +0x14: field_14
// +0x18: field_18
// +0x1C: field_1C
// +0x20: byte flag
// +0x24: field_24
// +0xE0: secondVtable
// +0xE4: field_0xE4
// +0xE8: buffer (pointer)
// +0xEC: bufferSize
// +0xF0: bufferCapacity