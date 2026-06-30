// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObjectConstructor(undefined4 *this)
{
  *this = &PTR_FUN_00d5eb30;
  this[0xf] = &PTR_LAB_00d5eb20;
  this[0x12] = &PTR_LAB_00d5eb1c;
  FUN_004086d0(this + 0x16); // Initialize some sub-object at offset +0x58
  FUN_00408310(this + 0x16);  // Another sub-object init at +0x58
  FUN_00408310(this + 0x18);  // Sub-object at +0x60
  FUN_00408310(this + 0x1a);  // Sub-object at +0x68
  FUN_004086d0(&DAT_0112a620); // Global static init
  FUN_004086d0(&DAT_0120e93c); // Another global static init
  FUN_0046c640();              // Some engine initialization
  return;
}