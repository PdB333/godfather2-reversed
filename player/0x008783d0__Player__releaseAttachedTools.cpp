// FUNC_NAME: Player::releaseAttachedTools
void __fastcall Player::releaseAttachedTools(Player* this) {
    // Release up to 4 attached tool/slot objects at offsets +0xB6C, +0xB70, +0xB74, +0xB78
    if (this->attachedToolSlots[0] != 0) { // +0xB6C
        releaseResource();
    }
    if (this->attachedToolSlots[1] != 0) { // +0xB70
        releaseResource();
    }
    if (this->attachedToolSlots[2] != 0) { // +0xB74
        releaseResource();
    }
    if (this->attachedToolSlots[3] != 0) { // +0xB78
        releaseResource();
        return;
    }
    return;
}