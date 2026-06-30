// FUN_006b3460: Entity::tryTriggerAudioEvent
void __fastcall Entity::tryTriggerAudioEvent(Entity *this) {
    // Check if the low bit of the byte at +0x37 is clear
    if (!(this->flags & 1)) {                 // +0x37: flags byte (bit0 = processed?)
        this->stateFlags |= 0x1000000;        // +0x34: state flags (sets 25th bit)
        // Determine which audio event to play based on the value at +0xC4
        if (this->audioEventType == 1) {      // +0xC4: audio event type (0 or 1)
            AudioEventManager::playEvent(0x4214d561);  // hash for event type 1
        } else {
            AudioEventManager::playEvent(0x7073082c);  // hash for other types
        }
    }
}