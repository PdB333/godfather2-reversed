// FUNC_NAME: NPC::updateReactionAnimation

void NPC::updateReactionAnimation()
{
    // Check if game is paused/cutscene active and if this character's state allows animation changes
    bool isPaused = isGamePaused(); // Helper function (address 0x007fd640)
    if (!isPaused)
    {
        // Access character's state machine component at offset +0xA0 (this->m_pStateMachine)
        byte* stateMachine = reinterpret_cast<byte*>(this->m_pStateMachine);
        // Bit 0 at offset 0x8E2 (e.g., disabled/dead flag)
        if (!(stateMachine[0x8E2] & 1))
        {
            // Read state index from offset 0x1B8C (0 = idle, 1 = aggressive)
            byte state = stateMachine[0x1B8C];
            if (state == 0)
            {
                this->m_reactionHash = 0x2ca3cff6; // e.g., "idle_react"
            }
            else if (state == 1)
            {
                this->m_reactionHash = 0x7fa41daa; // e.g., "aggressive_react"
            }

            // Call virtual function at vtable+0x2c (index 11) to play animation
            // Signature: playAnimation(uint hash, int param1, int param2, int param3, float speed, float blend)
            (this->vtable->playAnimation)(this->m_reactionHash, 1, 1, 0, 1.0f, 1.0f);
        }
    }
}