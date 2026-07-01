// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(undefined4 *this)
{
  int *piVar1;
  
  piVar1 = this + 0x9e; // +0x278 - some state/type field
  *this = &PTR_FUN_00d770d0; // vtable pointer
  this[0xf] = &PTR_LAB_00d770c0; // +0x3C - another vtable or function pointer
  this[0x12] = &PTR_LAB_00d770bc; // +0x48 - another vtable or function pointer
  if ((*piVar1 != 0) && (*piVar1 != 0x48)) {
    FUN_0088f360(this); // likely cleanup specific to non-zero/non-0x48 state
  }
  FUN_0088dcb0(this); // likely base class destructor or cleanup
  FUN_004086d0(&DAT_01206a20); // release singleton or global resource
  FUN_004086d0(&DAT_0120e93c); // release singleton or global resource
  FUN_0088c000(); // static cleanup function
  if (*piVar1 != 0) {
    FUN_004daf90(piVar1); // free memory at +0x278
  }
  if (this[0x97] != 0) { // +0x25C - pointer to allocated object
    FUN_009c8f10(this[0x97]); // delete/release object
  }
  FUN_008871f0(); // static cleanup function
  if (this[0x27] != 0) { // +0x9C - pointer to allocated object
    FUN_009c8f10(this[0x27]); // delete/release object
  }
  if (this[0x23] != 0) { // +0x8C - pointer to allocated object
    FUN_009c8f10(this[0x23]); // delete/release object
  }
  if (this[0x1f] != 0) { // +0x7C - pointer to allocated object
    FUN_009c8f10(this[0x1f]); // delete/release object
  }
  FUN_0046c640(); // static cleanup function
  return;
}