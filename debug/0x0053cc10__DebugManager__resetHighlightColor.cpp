// FUNC_NAME: DebugManager::resetHighlightColor
void __fastcall DebugManager::resetHighlightColor()
{
    // Call to update debug system state (e.g., check if cheats enabled)
    updateDebugSystem();

    // +0x10: pointer to object currently tracked by this manager
    // Check if the tracked object matches the global selected object
    // and if highlighting is active
    if (*(uintptr_t*)(this + 0x10) == g_selectedObject && g_highlightEnabled != 0)
    {
        // Clear highlight color (RGBA zero)
        D3DXCOLOR clearColor = {0.0f, 0.0f, 0.0f, 0.0f};
        // Apply the cleared color to the object's highlight
        setObjectHighlightColor(*(uintptr_t*)(this + 0x10), g_highlightEnabled, &clearColor);
    }
}