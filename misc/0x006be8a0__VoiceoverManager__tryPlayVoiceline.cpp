// FUNC_NAME: VoiceoverManager::tryPlayVoiceline
void VoiceoverManager::tryPlayVoiceline(Entity* object1, Entity* object2, uint32_t voiceLineHash) {
    char localizedBuffer[4116]; // alloca probe allocates 0x1014 bytes (4116)
    const uint32_t kPlayerTypeHash = 0x637b907; // hash identifier for "Player" entity type

    if (object1->typeHash == kPlayerTypeHash) {
        if (!isMultiplayerSession()) {
            showLocalizedDialog(0xff92ca40, voiceLineHash, nullptr);
            return;
        }
    } else if (object2->typeHash == kPlayerTypeHash) {
        showLocalizedDialog(0xf5f69f67, voiceLineHash, nullptr);
        return;
    } else {
        if (!isMultiplayerSession()) {
            beginDebugOutput();
            uint32_t* debugConsolePtr = getDebugConsolePointer();
            const char* debugString = reinterpret_cast<const char*>(*debugConsolePtr);
            if (debugString == nullptr) {
                debugString = "Voiceline system unavailable (default message)"; // DAT_0120546e
            }
            writeDebugOutput(100, debugString);
            showLocalizedDialog(0x9518e280, voiceLineHash, localizedBuffer);
            endDebugOutput();
        }
    }
}