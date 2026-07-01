// FUNC_NAME: Player::constructor
void __fastcall Player::constructor(Player *this)
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  int *piVar5;
  
  // Set vtable pointer
  *this = &PTR_FUN_00d803fc;
  // Initialize member pointers
  this[0xf] = &PTR_LAB_00d803ec;  // +0x3C
  this[0x12] = &PTR_LAB_00d803e8; // +0x48
  this[0x14] = &PTR_LAB_00d803d0; // +0x50
  
  // Call base class constructor
  FUN_008e35f0(); // Sentient::constructor
  
  // Initialize string members
  FUN_004086d0(&DAT_01130248); // String constructor
  FUN_004086d0(this + 0x67);   // +0x19C
  FUN_00408310(this + 0x67);   // +0x19C
  FUN_004086d0(this + 0x6B);   // +0x1AC
  FUN_00408310(this + 0x6B);   // +0x1AC
  FUN_00408310(this + 0x6F);   // +0x1BC
  FUN_00408310(this + 0x15);   // +0x54
  FUN_004086d0(this + 0x17);   // +0x5C
  FUN_00408310(this + 0x17);   // +0x5C
  FUN_00408310(this + 0x6D);   // +0x1B4
  
  // Initialize array of 3 elements (each 8 words = 32 bytes)
  puVar3 = this + 0x7A;  // +0x1E8
  iVar2 = 3;
  do {
    iVar1 = iVar2;
    FUN_00408310(puVar3 + -2);  // +0x1E0
    FUN_004086d0(puVar3);        // +0x1E8
    FUN_00408310(puVar3);        // +0x1E8
    FUN_00408310(puVar3 + 2);    // +0x1F0
    puVar3 = puVar3 + 8;         // Advance 32 bytes
    iVar2 = iVar1 + -1;
  } while (iVar2 != 0);
  
  // Initialize another array (3 elements, each 0x5C bytes)
  puVar3 = this + 0x2E;  // +0xB8
  iVar1 = iVar1 + 2;     // = 3
  do {
    FUN_00408310(puVar3);
    puVar3 = puVar3 + 0x17;  // Advance 92 bytes
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  
  // Call Player-specific initialization
  FUN_008e6220(this); // Player::init
  
  // Clean up if already initialized
  if (this[0x71] != 0) {  // +0x1C4
    FUN_004daf90(this + 0x71); // Free memory
  }
  
  // Clean up two more slots
  iVar2 = 2;
  piVar4 = this + 0x76;  // +0x1D8
  do {
    piVar5 = piVar4 + -0x17;  // +0x1A4
    if (piVar4[-0x15] != 0) {  // +0x1AC
      FUN_004daf90(piVar4 + -0x15);
    }
    if (*piVar5 != 0) {  // +0x1A4
      FUN_004daf90(piVar5);
    }
    iVar2 = iVar2 + -1;
    piVar4 = piVar5;
  } while (-1 < iVar2);
  
  // Final cleanup
  FUN_0046c640(); // Some global cleanup
  return;
}