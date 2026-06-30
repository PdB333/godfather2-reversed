// FUNC_NAME: Player::handleCrewInteraction
void __thiscall Player::handleCrewInteraction(Player* this)
{
    // +0xD8: pointer to current crew member (or target interactable)
    if (this->m_pCrewMember != nullptr)
    {
        // Global game manager (DAT_0112afb8) check if interaction is allowed
        if (GameManager::isCrewInteractionAllowed((GodfatherGameManager*)DAT_0112afb8))
        {
            // Global audio manager (DAT_00d5e288) play UI sound (soundId=0, loop=1)
            AudioManager::playSound((AudioManager*)DAT_00d5e288, 0, 1);
        }
    }
    // +0x34: flags; set bit 25 (0x2000000) to mark crew interaction active
    this->m_flags |= 0x2000000;
}