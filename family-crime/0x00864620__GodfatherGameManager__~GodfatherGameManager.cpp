// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager
void __thiscall GodfatherGameManager::~GodfatherGameManager(GodfatherGameManager *this)
{
  // Set vtable pointers for base classes / sub-objects during destruction
  // +0x00: main vtable
  *this = &PTR_FUN_00d759c0;
  // +0x3C (0xF*4): sub-object vtable
  this[0xF] = &PTR_LAB_00d759b0;
  // +0x48 (0x12*4): another sub-object vtable
  this[0x12] = &PTR_LAB_00d759ac;
  // +0x50 (0x14*4): another sub-object vtable
  this[0x14] = &PTR_LAB_00d759a8;
  // +0x54 (0x15*4): another sub-object vtable
  this[0x15] = &PTR_LAB_00d75948;
  // +0x58 (0x16*4): another sub-object vtable
  this[0x16] = &PTR_LAB_00d758e0;
  // +0x2E0 (0xB8*4): another vtable
  this[0xB8] = &PTR_FUN_00d758c8;
  // +0x2E4 (0xB9*4): another vtable
  this[0xB9] = &PTR_LAB_00d758b4;
  // +0x7B0 (0x1EC*4): another vtable
  this[0x1EC] = &PTR_LAB_00d758a0;

  // Initialize sub-objects at offsets 0xF and 0x10 (60 and 64 bytes)
  subObjectInit(0xF, this);
  subObjectInit(0x10, this);

  // Register global references (increment reference counts or add to lists)
  registerGlobal(&DAT_0112b18c);
  registerGlobal(&DAT_0112fe64);
  registerGlobal(&DAT_0112b36c);
  registerGlobal(&DAT_0112fc60);
  registerGlobal(&DAT_0112adb8);
  registerGlobal(&DAT_0112dfb8);

  // Release sub-object at offset 0x3E5 (997*4 = 3988 bytes) if present
  if (this[0x3E5] != 0) {
    releaseSubObject(this[0x3E5]);
    cleanupSubObject();
  }

  // Check if this object is the current singleton instance (global pointer at DAT_0112dfd4)
  // The global stores a pointer to the object's base at offset -0x48? (subtract 0x48 bytes)
  GodfatherGameManager *singletonBase;
  if (DAT_0112dfd4 == 0) {
    singletonBase = 0;
  } else {
    singletonBase = (GodfatherGameManager *)(DAT_0112dfd4 - 0x48);
  }
  if ((this == singletonBase) && (DAT_0112dfd4 != 0)) {
    releaseSingleton(&DAT_0112dfd4);
    DAT_0112dfd4 = 0;
  }

  // Release sub-object at offset 0x465 (1125*4 = 4500 bytes) if present
  if (this[0x465] != 0) {
    releaseSubObject(this + 0x465);
  }

  // Global shutdown routine
  globalShutdown();

  // Release sub-object at offset 0x411 (1041*4 = 4164 bytes) if present
  if (this[0x411] != 0) {
    releaseSubObject(this + 0x411);
  }

  // Release sub-object at offset 0x40E (1038*4 = 4152 bytes) if present
  if (this[0x40E] != 0) {
    releaseSubObject(this + 0x40E);
  }

  // Final cleanup
  finalCleanup();
}