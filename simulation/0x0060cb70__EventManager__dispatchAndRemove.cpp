// FUNC_NAME: EventManager::dispatchAndRemove
void EventManager::dispatchAndRemove(EventManager* this, HandlerObject* handler, uint arg0, uint arg1, uint arg2, uint arg3) {
    if (!handler) {
        return;
    }

    // +0x28: registered flag
    if (!handler->registered) {
        ensureHandlerRegistered();
        if (!handler->registered) {
            return;
        }

        EnterCriticalSection(&g_handlerLock);

        int count = g_handlerCount;
        for (int i = 0; i < count; i++) {
            if (g_handlerList[i] == handler) {
                count--;
                g_handlerCount = count;
                if (count > 0) {
                    g_handlerList[i] = g_handlerList[count];
                }
                break;
            }
        }

        LeaveCriticalSection(&g_handlerLock);

        if (!handler->registered) {
            return;
        }
    }

    // Remove the handler and then call the actual callback
    callHandler(this, arg0, arg1, arg2, arg3);
}