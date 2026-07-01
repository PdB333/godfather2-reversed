// Xbox PDB: EARS_Modules_GameData_GameData
// FUNC_NAME: VibrationManager::VibrationManager
undefined4 * __fastcall VibrationManager::VibrationManager(undefined4 *this)
{
  undefined4 defaultVal;
  bool bVar2;

  defaultVal = _DAT_00d5780c; // Global default value (likely 0 or some constant)
  this[1] = &PTR_FUN_00e2f19c; // Vtable pointer for base class or interface
  this[3] = 0; // Some counter or index
  this[2] = 1; // Enabled flag or version
  this[4] = &PTR_LAB_00d834d8; // Another vtable or data pointer
  DAT_01129938 = this; // Store global singleton pointer
  this[0] = &PTR_FUN_00d834f0; // Primary vtable
  this[1] = &PTR_LAB_00d834e0; // Overwrite vtable pointer (multiple inheritance)
  this[4] = &PTR_LAB_00d834dc; // Overwrite again
  this[5] = 0; // Flags field
  this[6] = defaultVal; // Vibration motor left speed
  this[7] = defaultVal; // Vibration motor right speed
  this[8] = defaultVal; // Vibration duration or intensity
  this[9] = defaultVal; // Another vibration parameter
  this[10] = 0; // Some state
  this[0xb] = defaultVal; // Another field
  *(undefined1 *)(this + 0xc) = 0; // Byte at offset 0x30? Actually offset 0x30 from this? Wait: param_1 + 0xc is offset 0x30? No, param_1 is pointer to undefined4, so param_1 + 0xc means offset 0x30 bytes (since each undefined4 is 4 bytes). So this is byte at offset 0x30.
  *(undefined1 *)((int)this + 0x31) = 1; // Byte at offset 0x31
  this[0xd] = 0; // Offset 0x34
  this[0xe] = 0; // Offset 0x38
  this[0xf] = 3; // Offset 0x3C, maybe max vibration level or mode
  this[0x10] = 0; // Offset 0x40
  this[0x11] = 0; // Offset 0x44
  bVar2 = DAT_0112a7a4 == '\0'; // Global flag: vibration enabled?
  *(char *)((int)this + 0x32) = DAT_0112a7a4; // Store at offset 0x32
  if (bVar2) {
    this[5] = this[5] & 0xfffffff7; // Clear bit 3
  } else {
    this[5] = this[5] | 8; // Set bit 3
  }
  if (DAT_0112a7a5 == '\0') { // Another global flag
    this[5] = this[5] & 0xfffffffb; // Clear bit 2
  } else {
    this[5] = this[5] | 4; // Set bit 2
  }
  if (*(char *)((int)this + 0x31) == '\0') { // Check byte at offset 0x31
    this[5] = this[5] & 0xfffffffd; // Clear bit 1
  } else {
    this[5] = this[5] | 2; // Set bit 1
  }
  FUN_0090d130(); // Additional initialization (likely sets up default vibration patterns)
  FUN_00463980(0x584f55bf, this, 0x27); // Register this object with some system using hash and size
  if (DAT_0112fe10 != 0) {
    FUN_00408900(this + 1, &DAT_0112fe10, 0x8000); // Copy 0x8000 bytes from global config buffer to this+4? Actually this+1 is offset 4 bytes.
  }
  FUN_00408240(&DAT_0112ffd4, "iMsgVibrationSettingChanged"); // Register message handler for vibration settings changes
  return this;
}