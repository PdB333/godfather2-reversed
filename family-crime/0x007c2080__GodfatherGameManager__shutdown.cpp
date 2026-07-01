// FUNC_NAME: GodfatherGameManager::shutdown
void __fastcall GodfatherGameManager::shutdown(undefined4 *this)

{
  char cVar1;
  int *piVar2;
  undefined8 uStack_18;
  undefined4 uStack_10;
  
  // Set vtable to base class (likely framework shutdown vtable)
  *this = &PTR_LAB_00d6e3e8;
  
  // Release soundbanks/stream managers
  piVar2 = (int *)FUN_007ab130(); // AudioDataManager::getSingleton
  (**(code **)(*piVar2 + 4))(this[0x1d]); // Release soundbank 0x1d
  
  piVar2 = (int *)FUN_007ab140(); // BNKStreamManager::getSingleton
  (**(code **)(*piVar2 + 4))(this[0x1e]); // Release stream 0x1e
  
  piVar2 = (int *)FUN_007ab150(); // MultiTrackStream::getSingleton
  (**(code **)(*piVar2 + 4))(this[0x1f]); // Release multitrack stream
  
  // Shutdown subsystems
  FUN_007e0b90(0); // EntityDataManager::shutdown
  FUN_007f6420(0x5c); // UILoadingScreen::hide (0x5c = loading ID?)
  
  // Check for and handle online services
  cVar1 = FUN_00481660(); // OnlineServices::isConnected
  if (cVar1 != '\0') {
    cVar1 = FUN_007f47a0(); // NetSession::isActive
    if (cVar1 == '\0') {
      FUN_0079fb90(5,1,0,uStack_18,uStack_10); // GamePlayLogging::logEvent(5,1,0,...)
    }
  }
  
  // Shutdown more managers
  FUN_007ab120(); // Presentation::shutdown
  FUN_00896e10(this[0x20]); // SimManager::destroy(this->simManager)
  FUN_00897830(0x100); // Memory::free(0x100 bytes?)
  
  // Delete family tree if exists
  if (this[0x21] != 0) {
    FUN_004daf90(this + 0x21); // FamilyManager::~FamilyManager
  }
  
  // Set final vtable and call base destructor
  *this = &PTR_LAB_00d6b95c; // Base class vtable
  FUN_0080ea60(); // EARSObject::destructor
  return;
}