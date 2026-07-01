// FUNC_NAME: SimManager::forEachSim
void __fastcall SimManager::forEachSim(SimManager* this)
{
    char hasMore;
    int* context;
    int* simManager;
    int playerOrContext;
    int* currentSim;
    int iterator[2] = {0, 0}; // iterator state (e.g., current and next indices)

    // Default context is this manager itself
    context = (int*)this;

    // Attempt to get a global context from the game manager singleton
    if (this != nullptr && (simManager = (int*)FUN_0043b870(DAT_01131018), simManager != nullptr))
    {
        // Call vtable+0x34 on the global manager (likely getPlayer() or getCurrentContext())
        playerOrContext = (**(code **)(*simManager + 0x34))();

        // If the player object at offset +0xc is null, or the derived context is null,
        // fall back to this manager's own context getter (vtable+0x1e4)
        if (*(int*)(playerOrContext + 0xc) == 0 ||
            (context = (int*)(*(int*)(playerOrContext + 0xc) - 0x48), context == nullptr))
        {
            context = (int*)(**(code **)(*this + 0x1e4))(); // this->getContext()
        }
    }

    // Begin iteration over all sim objects
    // vtable+0x1cc: getFirst(iterator) - initializes iterator and returns true if any elements exist
    hasMore = (**(code **)(*this + 0x1cc))(&iterator);
    while (hasMore != '\0')
    {
        // vtable+0x1f4 (500): getCurrent(iterator) - returns pointer to current sim object
        currentSim = (int*)(**(code **)(*this + 500))(&iterator);
        if (currentSim != nullptr)
        {
            // Apply the callback function to the current sim with the context
            FUN_00876bb0(currentSim, context);
        }
        // vtable+0x1d0: getNext(iterator) - advances iterator and returns true if more elements exist
        hasMore = (**(code **)(*this + 0x1d0))(&iterator);
    }
}