// FUNC_NAME: AnimationManager::processDueEvents
void AnimationManager::processDueEvents(void)
{
    AnimationEventNode* node;
    uint flags;
    uint eventType;
    float* eventTime;

    // Traverse linked list of animation events starting at +0x60
    for (node = *(AnimationEventNode**)(*(int*)this + 0x60); node != nullptr; node = node->next) {
        flags = node->flags; // +0x00: bitfield
        eventType = flags & 0x7fff;
        // Check if event is active (bit 0x8000) and type is 0xd (13) or 0x12 (18)
        if (((flags & 0x8000) != 0) && ((eventType == 0xd) || (eventType == 0x12))) {
            // If node has a target object at +0x50 and its time (+0x7c) is >= global time
            if ((node->target == nullptr) ||
                (DAT_00e2cd54 >= node->eventTime)) {
                FUN_005b9340(); // process the event
            }
        }
    }
}