// FUNC_NAME: ActionManager::tick
void ActionManager::tick(ActionManager* this)
{
    // Delegates to the core update function at 0x008d5d40
    // This is a thin wrapper likely for debug or profiling purposes
    ActionManager::update(this);
    return;
}