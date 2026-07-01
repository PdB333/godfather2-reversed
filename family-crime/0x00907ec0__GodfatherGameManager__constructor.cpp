// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __thiscall GodfatherGameManager::constructor(undefined4 *this, byte flags)

{
  *this = &GodfatherGameManager_vtable;
  GodfatherGameManager::initStaticData(&DAT_00d82fb8,0);
  GodfatherGameManager::resetState();
  *this = &GodfatherGameManager_vtable2;  // switch to second vtable or derived class pointer
  g_GodfatherGameManagerInstance = 0;     // _DAT_0112ff68 - global singleton pointer
  if ((flags & 1) != 0) {
    GodfatherGameManager::operatorDelete(this);  // or free instance if flag set
  }
  return this;
}