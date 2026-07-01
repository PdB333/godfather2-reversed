// FUNC_NAME: GodfatherGameManager::destructor
void __fastcall GodfatherGameManager::~GodfatherGameManager(undefined4 *this)
{
  // Set vtable to GodfatherGameManager vtable (0xd73d94)
  *this = &PTR_FUN_00d73d94;
  // Set base class vtable pointer (likely EARSObject or similar)
  this[1] = &PTR_LAB_00d73d90;
  
  // Call cleanup function with a hash/ID (0xc14c90e8)
  FUN_004639e0(0xc14c90e8);
  
  // Call another destructor helper
  FUN_00837dc0();
  
  // If there's a child object at offset +0x10 (this[4]), delete it
  if (this[4] != 0) {
    FUN_009c8f10(this[4]); // likely operator delete or destructor call
  }
  
  // Update vtable pointers for base class destruction chain
  this[1] = &PTR_LAB_00d73d84;
  // Reset global singleton pointer (0x11299bc)
  DAT_011299bc = 0;
  
  // Final vtable update (likely to base class vtable at 0xe30fe0)
  *this = &PTR_LAB_00e30fe0;
  
  return;
}