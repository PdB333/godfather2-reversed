// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
void __fastcall GodfatherGameManager::GodfatherGameManager(GodfatherGameManager* this)
{
  // Set vtable pointers for multiple inheritance
  this->vtable0 = &PTR_FUN_00d5fdbc;           // +0x00
  this->vtable1 = &PTR_LAB_00d5fdac;           // +0x3C (offset 0xF)
  this->vtable2 = &PTR_LAB_00d5fda8;           // +0x48 (offset 0x12)

  // Construct member subobject at +0x60 (offset 0x18)
  subObjectConstructor(&this->memberAt60);

  // Two-phase construction of member at +0x50 (offset 0x14)
  subObjectInit(&this->memberAt50);            // Phase 1: init
  subObjectConstructor(&this->memberAt50);     // Phase 2: full construction

  // Two-phase construction of member at +0x58 (offset 0x16)
  subObjectInit(&this->memberAt58);            // Phase 1: init
  subObjectConstructor(&this->memberAt58);     // Phase 2: full construction

  // Initialize a global/static member
  subObjectInit(&DAT_012069c4);

  // Clear global singleton pointer if constructing the singleton instance
  if (this == DAT_0112a9c0) {
    DAT_0112a9c0 = nullptr;
  }

  // General initialization (e.g., startup systems)
  globalInitialization();
}