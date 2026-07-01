// FUNC_NAME: EventManager::dispatchEvent
void EventManager::dispatchEvent(int eventId, void* eventData)
{
    unsigned int eventHash = 0;

    // Handle event IDs with specific hash values
    // Many IDs map to the same hash, indicating grouped events
    switch (eventId)
    {
    // --- Events that result in default hash (0xa08a43df) ---
    case 0x001:
    case 0x002:
    case 0x004:
    case 0x008:
    case 0x020:
    case 0x1000:
    case 0x10000:
    case 0x20000:
    case 0x40000:
    case 0x80000:
    case 0x100000:
    case 0x400000:
    case 0x2000000:
    case 0x8000000:
    case 0x40000000:
        eventHash = 0xa08a43df;
        break;

    // --- Explicit event IDs ---
    case 0x040:
        eventHash = 0xed41087b;
        break;

    case 0x080:
        // "Throw over" diagnostic event – just log and return without further dispatch
        debugLog("[b=THROW_OVER]");
        return;

    case 0x100:
    case 0x800:
        eventHash = 0x8c036aab;
        break;

    case 0x200:
        eventHash = 0x1a271621;
        break;

    case 0x400:
        eventHash = 0xd7d6fc22;
        break;

    case 0x2000:
        // Direct handler for a specific event; bypass hash-based dispatch
        if (g_eventManager != 0)
        {
            handleEvent2000(eventData);
        }
        return;

    case 0x4000:
    case 0x8000:
        eventHash = 0xf0c639eb;
        break;

    case 0x200000:
        eventHash = 0xa7879506;
        break;

    case 0x10000000:
    case 0x20000000:
        eventHash = 0x5855e99b;
        break;

    // --- Events that return immediately without any action ---
    case 0x800000:
    case 0x1000000:
        return;

    default:
        // Unhandled event IDs – no action (original behaviour: unreachable paths would return)
        // Note: some IDs that fall through in the original decompiled code are covered above
        return;
    }

    // Dispatch the event via hash if the manager exists
    if (g_eventManager != 0)
    {
        fireEvent(eventHash, eventData);
    }
}