// FUNC_NAME: Entity::deactivateIfActive
// Address: 0x00984eb0
// Role: Deactivates the entity's subsystems if the entity is active and has an attached system pointer.

// +0xCC: m_bActive (byte, flag indicating entity is active)
// +0x5C: m_pSystem (int/pointer, associated system or component)

void __fastcall Entity::deactivateIfActive(Entity* this)
{
    // Only proceed if entity is active and a system exists
    if (this->m_bActive != 0 && this->m_pSystem != 0) {
        // Shut down subsystems; parameter 0 likely means "stop immediately"
        stopAudioSystem(0);     // e.g., stop sound effects, music
        stopAnimationSystem(0); // e.g., halt character animations
        finalCleanup();         // e.g., release resources, clear state
    }
}