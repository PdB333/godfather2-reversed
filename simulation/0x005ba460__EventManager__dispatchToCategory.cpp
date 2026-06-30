// FUNC_NAME: EventManager::dispatchToCategory

// Function address: 0x005ba460
// Role: Dispatches an event to all handlers registered under a specific category index.
// Assumes the object (this) has two fields:
//   - m_categoryCount at offset 0x00 (int)
//   - m_categories at offset 0x04 (pointer to array of Category structures)
// Each Category is 8 bytes: count (int) at +0x00, handlers (int**) at +0x04.
// Each handler is a struct of two ints: type (int) and data (int).
// If type == 1, calls processHandlerEvent(data, eventCode, g_global).

int g_global = DAT_012055ac;  // global singleton or state (address 0x012055ac)

void EventManager::dispatchToCategory(int categoryIndex, unsigned int eventCode)
{
    if (eventCode < 0x1000)
    {
        // Event code too small - fallback handler
        errorHandler();
        return;
    }

    if (categoryIndex < 0 || categoryIndex >= m_categoryCount)
    {
        // Invalid category index
        errorHandler();
        return;
    }

    Category* cat = &m_categories[categoryIndex];
    for (int i = 0; i < cat->count; i++)
    {
        Handler* handler = cat->handlers[i];
        if (handler->type == 1)
        {
            // handler is active: call the processing function with the data field
            processHandlerEvent(&handler->data, eventCode, g_global);
        }
    }
}

// Stubs for called functions (not provided)
void errorHandler(void);
void processHandlerEvent(int* data, unsigned int eventCode, int global);