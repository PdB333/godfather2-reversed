// FUNC_NAME: EntityManager::processEntityList
void __thiscall EntityManager::processEntityList(int* entityList)
{
    int count = entityList[1];          // number of entities
    int** entities = (int**)entityList[0];  // array of entity pointers

    while (int i = count; i > 0; ) {
        i--;
        int* entity = entities[i];
        Player* currentPlayer = Player::getCurrentPlayer(); // FUN_00791300

        // Check if no current player OR player is not paused (bit 25 of flags cleared)
        if (currentPlayer == nullptr || (currentPlayer->flags & 0x02000000) != 0) {
            // If entity is not flagged as dead/removed (bits 17-18 not set)
            if ((entity->stateFlags & 0x60000) == 0) {
                if (currentPlayer != nullptr && (currentPlayer->flags & 0x02000000) != 0) {
                    currentPlayer->resumeSomething(currentPlayer + 0x3c); // FUN_004088c0
                }
                if (this->m_bActive != 0) { // flag at +0xfc
                    entity->updateCommon(); // FUN_006bf230
                }

                SimManager* simMgr = SimManager::getInstance(); // FUN_007915b0
                if (simMgr->m_currentPlayerId == this->m_ownerId) { // compare +0x54 and +0x40
                    entity->updateForLocalPlayer(this); // FUN_008c2ab0
                } else {
                    entity->updateForRemotePlayer(this); // FUN_008c29f0
                }
            } else {
                // Entity is dead/removed, schedule removal (set bit 30)
                entity->stateFlags |= 0x40000000;
            }
        }
    }
}