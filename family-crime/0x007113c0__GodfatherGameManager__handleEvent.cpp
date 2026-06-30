// FUNC_NAME: GodfatherGameManager::handleEvent
void __thiscall GodfatherGameManager::handleEvent(GodfatherGameManager *this, int unused1, int unused2, Entity *entity)
{
  // Check if the entity is valid (e.g., active and in the game world)
  if (isEntityValid(entity) != 0) {
    // Forward the event to the entity manager with game context
    handleEntityEvent(*(EntityManager **)(this + 4), entity, g_gameContext);
  }
  return;
}