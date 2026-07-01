// FUNC_NAME: ResourceManager::onResourceEvent
void __thiscall ResourceManager::onResourceEvent(int* eventData)
{
    int* originalEventData = eventData;
    char result;
    int* foundObject;
    int* resource;

    // First case: event type matches active slot (offset 0x14)
    if (*eventData == *(int*)(this + 0x14)) {
        foundObject = (int*)findInMap((int*)(this + 0x24), 0); // query with key 0
        if (foundObject != (int*)0x0) {
            eventData = (int*)0x0;
            // vtable+0x10 is likely a method like getResource(hash, &outPtr)
            result = (*(code**)(*foundObject + 0x10))(0xa7039c8, &eventData);
            resource = eventData;
            if ((result != '\0') && (eventData != (int*)0x0)) {
                if (*(int*)(this + 0x1c) != 0) {
                    processResource(eventData); // FUN_008b6730
                }
                assignResource(resource, (int*)(this + 0x34), 0); // FUN_008b6850
            }
        }
    }

    // Second case: event type matches pending slot (offset 0x1c) and there's something to replace
    if ((*originalEventData == *(int*)(this + 0x1c)) && (*(int*)(this + 0x50) != 0)) {
        foundObject = (int*)findInMap((int*)(this + 0x24), 0);
        if (foundObject != (int*)0x0) {
            eventData = (int*)0x0;
            result = (*(code**)(*foundObject + 0x10))(0xa7039c8, &eventData);
            if ((result != '\0') && (eventData != (int*)0x0)) {
                assignResource(eventData, *(int**)(this + 0x50), 1); // FUN_008b6850
            }
        }
        if (*(int*)(this + 0x50) != 0) {
            freeResource(*(int*)(this + 0x50)); // FUN_009c8eb0
            *(int*)(this + 0x50) = 0;
        }
    }
}