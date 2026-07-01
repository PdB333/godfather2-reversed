//FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __thiscall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager *this)
{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;

  // Set vtable pointer (base class)
  *this = &PTR_FUN_00d720a8;
  // Set vtable pointers for sub-objects (interfaces)
  this->field_0x3c = &PTR_LAB_00d72098;   // +0x3c
  this->field_0x48 = &PTR_LAB_00d72094;   // +0x48
  this->field_0x50 = &PTR_LAB_00d72090;   // +0x50
  this->field_0x54 = &PTR_LAB_00d72030;   // +0x54
  this->field_0x58 = &PTR_LAB_00d71fc8;   // +0x58
  this->field_0x390 = &PTR_LAB_00d71fa8;  // +0x390
  this->field_0x394 = &PTR_FUN_00d71f94;  // +0x394
  this->field_0x3a0 = &PTR_LAB_00d71f8c;  // +0x3a0

  // If the character at +0x7c7 is not 'P', store it in a global log array
  if (*(char *)((int)this + 0x7c7) != 'P') {
    (&DAT_0112c7c0)[DAT_00e53770] = *(char *)((int)this + 0x7c7);
    DAT_00e53770 = DAT_00e53770 + 1;
  }

  // If there is a sound resource at +0x7c3, release it
  if (this->field_0x7c3 != 0) {
    FUN_004df600(); // Sound resource cleanup
  }

  // Cleanup subsystems
  FUN_006fc560(this); // Subsystem A cleanup
  FUN_006f0ea0(this); // Subsystem B cleanup
  FUN_006fbca0(this); // Subsystem C cleanup

  piVar1 = &this->field_0x7a2;
  if (this->field_0x7a2 != 0) {
    FUN_005f72f0(this->field_0x7a2); // Sub-object destructor
  }
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1); // Free memory
    *piVar1 = 0;
  }

  // Release COM-like objects at +0x1e9 and +0x1ea
  if (this->field_0x1e9 != 0) {
    (*(code *)*this->field_0x1e9)(1); // Release with refcount 1
    this->field_0x1e9 = 0;
  }
  if (this->field_0x1ea != 0) {
    (*(code *)*this->field_0x1ea)(1);
    this->field_0x1ea = 0;
  }

  // Debug/logging call
  FUN_008f67c0(0x16, this);

  // Destroy arrays of 8-byte structures at offsets +0x730 to +0x744
  FUN_00408310(&this->field_0x730); // Array destructor
  FUN_00408310(&this->field_0x732);
  FUN_00408310(&this->field_0x734);
  FUN_00408310(&this->field_0x736);
  FUN_00408310(&this->field_0x738);
  FUN_004086d0(&this->field_0x73a); // Different destructor for these
  FUN_00408310(&this->field_0x73a);
  FUN_004086d0(&this->field_0x73c);
  FUN_00408310(&this->field_0x73c);
  FUN_004086d0(&this->field_0x73e);
  FUN_00408310(&this->field_0x73e);
  FUN_004086d0(&this->field_0x740);
  FUN_00408310(&this->field_0x740);
  FUN_004086d0(&this->field_0x742);
  FUN_00408310(&this->field_0x742);
  FUN_004086d0(&this->field_0x744);
  FUN_00408310(&this->field_0x744);

  // Destroy global arrays (likely static members)
  FUN_004086d0(&DAT_0112f1dc);
  FUN_00408310(&DAT_0112f1dc);
  FUN_004086d0(&DAT_0112d9e4);
  FUN_00408310(&DAT_0112d9e4);
  FUN_004086d0(&DAT_0112ef7c);
  FUN_004086d0(&DAT_0112edf4);
  FUN_00408310(&DAT_0112ef7c);
  FUN_00408310(&DAT_0112edf4);

  // Release object at +0xed via vtable+0x14
  if (this->field_0xed != 0) {
    (**(code **)(this->field_0xed + 0x14))(1);
  }

  // Cleanup another subsystem
  if (this->field_0x6f2 != 0) {
    FUN_008051e0();
  }

  // Release object at +0x228 via vtable+4
  if (this->field_0x228 != 0) {
    (**(code **)(this->field_0x228 + 4))(1);
    this->field_0x228 = 0;
  }

  // Global cleanup calls
  FUN_007eea00();
  FUN_00800e60();

  // Release two sound-related objects at +0x721 and +0x722
  if (this->field_0x721 != 0) {
    FUN_0054e520();
    FUN_0054e2e0(this->field_0x721);
    this->field_0x721 = 0;
  }
  if (this->field_0x722 != 0) {
    FUN_0054e520();
    FUN_0054e2e0(this->field_0x722);
    this->field_0x722 = 0;
  }

  // Global cleanup
  FUN_007ff050(0);

  piVar1 = &this->field_0x790;
  // If field at +0x790 is not 0 and not 0x48, set a state flag
  if ((this->field_0x790 != 0) && (this->field_0x790 != 0x48)) {
    this->field_0x216 = 4;
  }
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1);
    *piVar1 = 0;
  }

  // Clear and release sound resource at +0x7c3
  if (this->field_0x7c3 != 0) {
    *(undefined4 *)(this->field_0x7c3 + 8) = 0;
    this->field_0x7c3 = 0;
  }

  // Free various pointers
  if (this->field_0x7b6 != 0) {
    FUN_004daf90(&this->field_0x7b6);
  }
  if (this->field_0x7a7 != 0) {
    FUN_004daf90(&this->field_0x7a7);
  }
  if (this->field_0x7a4 != 0) {
    FUN_004daf90(&this->field_0x7a4);
  }
  if (this->field_0x7a2 != 0) {
    FUN_004daf90(&this->field_0x7a2);
  }
  if (this->field_0x7a1 != 0) {
    *(undefined4 *)(this->field_0x7a1 + 8) = 0;
    this->field_0x7a1 = 0;
  }
  if (this->field_0x79c != 0) {
    *(undefined4 *)(this->field_0x79c + 8) = 0;
    this->field_0x79c = 0;
  }
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1);
  }

  // More global cleanup
  FUN_007eeef0();
  FUN_007ee840();

  // Free more pointers
  if (this->field_0x71e != 0) {
    FUN_004daf90(&this->field_0x71e);
  }
  if (this->field_0x6fc != 0) {
    FUN_004daf90(&this->field_0x6fc);
  }
  if (this->field_0x6ea != 0) {
    FUN_004daf90(&this->field_0x6ea);
  }

  // Call a cleanup function 10 times (likely for a timer or update list)
  iVar2 = 9;
  do {
    FUN_00549cb0();
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);

  // Free more pointers
  if (this->field_0x3ff != 0) {
    FUN_004daf90(&this->field_0x3ff);
  }
  if (this->field_0x3fc != 0) {
    FUN_004daf90(&this->field_0x3fc);
  }
  if (this->field_0x226 != 0) {
    FUN_004daf90(&this->field_0x226);
  }

  // Call a function pointer at +0x214 with argument at +0x211
  if (this->field_0x211 != 0) {
    (*(code *)this->field_0x214)(this->field_0x211);
  }

  // Loop over an array of 6 pairs at +0x207 (each pair is 2 ints)
  puVar3 = &this->field_0x207;
  iVar2 = 6;
  do {
    piVar1 = puVar3 + -2;
    puVar3 = puVar3 + -2;
    if (*piVar1 != 0) {
      FUN_004daf90(puVar3);
    }
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);

  // Loop over an array of 7 pairs at +0x1e7
  puVar3 = &this->field_0x1e7;
  iVar2 = 7;
  do {
    piVar1 = puVar3 + -2;
    puVar3 = puVar3 + -2;
    if (*piVar1 != 0) {
      FUN_004daf90(puVar3);
    }
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);

  // Free pointer at +0x1d3
  if (this->field_0x1d3 != 0) {
    FUN_004daf90(&this->field_0x1d3);
  }

  // Final global cleanup calls
  FUN_00704540();
  FUN_005fdd00();
  FUN_0054eed0();
  FUN_00625030();

  // Set vtable pointer for a sub-object and call a global cleanup
  this->field_0x390 = &PTR_LAB_00d71bdc;
  FUN_009c5380();
  return;
}