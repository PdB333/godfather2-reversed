// FUNC_NAME: SomeEntity::setActionState
void SomeEntity::setActionState(SomeEntity* this)
{
    // Get singleton manager (likely StateManager or ActionManager)
    StateManager* manager = StateManager::getSingleton(); // FUN_009c8f80

    // Action state data: type=2, subtype=0x10, flags=0
    ActionStateData stateData;
    stateData.type = 2;       // +0x00
    stateData.subType = 0x10; // +0x04
    stateData.flags = 0;      // +0x08

    // Call virtual function on manager (first vtable entry) to apply state to this entity
    manager->applyState(this, &stateData);
}