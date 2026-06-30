// FUNC_NAME: GlobalManager::callHandlerWithGlobal
void __cdecl GlobalManager::callHandlerWithGlobal(uint eventData)
{
    // Thin wrapper: calls a member function on the global singleton at 0x012234bc
    // The global pointer is of an unknown class, likely a manager or dispatcher
    reinterpret_cast<GlobalManager*>(DAT_012234bc)->processEvent(eventData);
}