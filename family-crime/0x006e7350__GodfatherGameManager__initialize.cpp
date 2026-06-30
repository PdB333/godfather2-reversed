// FUNC_NAME: GodfatherGameManager::initialize
void __fastcall GodfatherGameManager::initialize(GodfatherGameManager* this)
{
  // Call base class initialization
  GodfatherGameManager::initializeBase(this);
  
  // Store the game manager instance pointer
  GodfatherGameManager::storeInstance(*this);
}