// FUNC_NAME: GodfatherGameManager::initialize
void __fastcall GodfatherGameManager::initialize(GodfatherGameManager *this)

{
  // Set vtable to initial GodfatherGameManager vtable
  this->vtable = &PTR_FUN_00d58928;
  // Set pointer at offset 0x3C (15 * 4 = 0x3C) to initial vtable entry
  this[0xf] = &PTR_LAB_00d58918;
  // Set pointer at offset 0x48 (18 * 4 = 0x48) to initial vtable entry
  this[0x12] = &PTR_LAB_00d58914;
  
  // Call initial base initialization function
  FUN_006b8060();
  
  // Override vtable with final GodfatherGameManager vtable
  this->vtable = &PTR_FUN_00d5888c;
  // Override pointer at offset 0x3C with final vtable entry
  this[0xf] = &PTR_LAB_00d5887c;
  // Override pointer at offset 0x48 with final vtable entry
  this[0x12] = &PTR_LAB_00d58878;
  
  // Call post-initialization function
  FUN_0046c640();
  return;
}