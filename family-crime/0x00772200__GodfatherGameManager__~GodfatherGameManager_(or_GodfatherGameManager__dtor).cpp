// FUNC_NAME: GodfatherGameManager::~GodfatherGameManager (or GodfatherGameManager::dtor)
undefined4 __thiscall GodfatherGameManager::dtor(undefined4 this, byte param_2)

{
  // Call the base destructor or internal cleanup
  FUN_00771f40();
  // If param_2 indicates deletion (bit 0 set), call operator delete
  if ((param_2 & 1) != 0) {
    FUN_00624da0(this);
  }
  return this;
}