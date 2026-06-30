//FUNC_NAME: SimManager::updateFrame
void SimManager::updateFrame()
{
    // Call pre-update callback if set (global singleton at DAT_012234c4, offset +0x34)
    if (g_simManager != nullptr && g_simManager->preUpdateCallback != nullptr)
    {
        g_simManager->preUpdateCallback();
    }

    // Iterate over all registered sim objects and call their update (vtable offset +0x18)
    for (int i = 0; i < g_simObjectCount; i++)
    {
        SimObject* obj = g_simObjectList[i];
        if (obj != nullptr)
        {
            obj->update(); // vtable entry at +0x18
        }
    }

    // Perform additional per-frame processing
    FUN_004e2480(); // likely SimManager::postUpdate or similar
}