// FUNC_NAME: Sentient::processDeath
// Function address: 0x00653a60
// Role: Handles death animation, model transform update, and associated effects

void Sentient::processDeath()
{
    // Set animation state to death (2)
    // Likely a member function that triggers death animation
    this->setAnimationState(2);

    // Check if a death model/effect is attached (offset +0x1b0)
    if (this->m_deathModel != nullptr)
    {
        // Update the death model's transform using the entity's position data
        // +0x90 and +0x98 are likely floats for position/rotation (e.g. m_posX, m_posZ)
        // The fourth parameter (2) may indicate a specific state or layer
        updateDeathModelTransform(this->m_deathModel, this->field_0x98, this->field_0x90, 2);

        // Trigger a death-related effect with state 3 (e.g., decay, dissolve)
        triggerDeathEffect(3, this->m_deathModel);
    }

    // Update audio and particle effects associated with death
    updateDeathSound();
    updateDeathParticles();
}

// External helper functions (global or static):
// void updateDeathModelTransform(void* model, float param1, float param2, int state);
// void triggerDeathEffect(int state, void* model);
// void updateDeathSound();
// void updateDeathParticles();