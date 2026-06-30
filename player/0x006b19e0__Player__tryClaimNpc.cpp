// FUNC_NAME: Player::tryClaimNpc
undefined1 __thiscall Player::tryClaimNpc(Player *this, NPC *npc) {
    undefined1 result;
    
    // Check if the NPC is already owned by this player
    if (npc->ownerId == this->playerId)
        return 1;
    
    // If NPC is unowned and this player can claim it
    if ((npc->ownerId == 0) && (this->canClaimFlag != 0)) {
        // Attempt to claim the NPC (set owner to this player)
        result = NPC::setOwner(npc, (Player *)DAT_00d5e20c, 1);
    } else {
        result = 0;
    }
    return result;
}