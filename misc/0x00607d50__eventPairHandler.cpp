// FUNC_NAME: eventPairHandler
void eventPairHandler(int entityType, int entityId)
{
    uint i;

    if (g_eventPairCount != 0) {
        int *entry = g_eventPairArray;
        do {
            if ((entry[-1] == entityType) && (*entry == entityId)) {
                handleEventPair();
                return;
            }
            i++;
            entry += 3;
        } while (i < g_eventPairCount);
    }
    return;
}