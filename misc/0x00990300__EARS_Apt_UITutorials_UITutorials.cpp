// Xbox PDB: EARS_Apt_UITutorials_UITutorials
// FUNC_NAME: DonControlManager::constructor
undefined4 * __fastcall DonControlManager::constructor(undefined4 *this)
{
  undefined4 *puVar1;
  
  FUN_005bf9b0(); // Base class constructor (likely EARS::Framework::Object or similar)
  this[0x13] = &PTR_FUN_00e2f19c; // vtable pointer for DonControlManager +0x4C
  this[0x14] = 1; // +0x50: some flag (e.g., isActive)
  this[0x15] = 0; // +0x54: some state
  this[0x16] = &PTR_LAB_00d91c2c; // +0x58: another vtable/function pointer
  puVar1 = this + 0x13; // pointer to offset 0x4C
  DAT_01130910 = this; // Global singleton pointer
  *this = &PTR_FUN_00d91c68; // vtable for base class (offset 0x00)
  this[4] = &PTR_LAB_00d91c44; // +0x10: another vtable entry
  *puVar1 = &PTR_LAB_00d91c34; // +0x4C: vtable entry
  this[0x16] = &PTR_LAB_00d91c30; // +0x58: vtable entry
  this[0x17] = 0; // +0x5C: some pointer (null)
  this[0x18] = 0; // +0x60: some pointer (null)
  this[0x19] = &PTR_LAB_00d83b18; // +0x64: default string/function pointer
  this[0x3a] = &PTR_LAB_00d83b18; // +0xE8: same default pointer
  this[0x5b] = 0; // +0x16C: some pointer (null)
  this[0x5c] = 0; // +0x170: some pointer (null)
  this[0x5d] = 0; // +0x174: some pointer (null)
  this[0x5e] = 0; // +0x178: some pointer (null)
  this[0x5f] = 0; // +0x17C: some pointer (null)
  *(undefined2 *)(this + 0x60) = 0; // +0x180: short (0)
  *(undefined2 *)((int)this + 0x182) = 0; // +0x182: short (0)
  *(undefined1 *)(this + 0x61) = 0; // +0x184: byte (0)
  *(undefined1 *)((int)this + 0x185) = 0; // +0x185: byte (0)
  *(undefined1 *)((int)this + 0x186) = 0; // +0x186: byte (0)
  if (this[0x5b] != 0) {
    (*(code *)this[0x5e])(this[0x5b]); // Call destructor on existing object
  }
  this[0x5b] = 0; // +0x16C: null
  this[0x5d] = 0; // +0x174: null
  this[0x5c] = 0; // +0x170: null
  FUN_00408240(&DAT_01130930,"iMsgTutorialMovieDone"); // Register message "iMsgTutorialMovieDone"
  FUN_00408240(&DAT_01130918,"iMsgIsDonControlLocked"); // Register message "iMsgIsDonControlLocked"
  FUN_00408240(&DAT_01130928,"iMsgDonControlIsLocked"); // Register message "iMsgDonControlIsLocked"
  FUN_00408240(&DAT_01130920,"iMsgDonControlIsUnlocked"); // Register message "iMsgDonControlIsUnlocked"
  if (DAT_01130930 != 0) {
    FUN_00408900(puVar1,&DAT_01130930,0x8000); // Subscribe to message with priority 0x8000
  }
  if (DAT_01130928 != 0) {
    FUN_00408900(puVar1,&DAT_01130928,0x8000); // Subscribe to message
  }
  if (DAT_01130920 != 0) {
    FUN_00408900(puVar1,&DAT_01130920,0x8000); // Subscribe to message
  }
  return this;
}