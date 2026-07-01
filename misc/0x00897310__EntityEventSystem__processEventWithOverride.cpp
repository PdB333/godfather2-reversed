// FUNC_NAME: EntityEventSystem::processEventWithOverride
// Address: 0x00897310
// Role: Routes an event to either normal or forced handling based on a flag and the object's state.
// If not forced and object passes state check, handle normal path.
// Otherwise log, and if forced while state check passes, return (skip).
// Else handle forced path.

void EntityEventSystem::processEventWithOverride(void* pObject, uint32_t eventData, char isForced)
{
    char stateCheck = checkObjectState(pObject); // 0 = normal/ready
    if (isForced == 0 && stateCheck == 0) {
        handleNormalEvent(pObject, eventData);
        return;
    }
    logOverrideAttempt();
    if (isForced != 0 && stateCheck == 0) {
        return;
    }
    handleForcedEvent(pObject, eventData);
}