// FUNC_NAME: NPC::playReactionAudio
void __fastcall NPC::playReactionAudio(NPC* this) {
    // Check if reaction audio has already been played (bit 0 of byte at +0x37)
    if (!(this->m_reactionPlayed & 1)) {
        // Set flag at +0x34 (bit 24) to mark that audio is pending/triggered
        this->m_flags |= 0x1000000;
        // +0xC4 holds current state (e.g., 1 = combat, other = normal)
        if (this->m_state == 1) {
            // Play combat reaction audio (hash 0x4214d561)
            playAudioEvent(0x4214d561);
        } else {
            // Play default reaction audio (hash 0x7073082c)
            playAudioEvent(0x7073082c);
        }
    }
}