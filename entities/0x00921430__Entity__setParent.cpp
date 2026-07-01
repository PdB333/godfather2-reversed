//FUNC_NAME: Entity::setParent
void __thiscall Entity::setParent(Entity* this, Entity* newParent)
{
    int** ppNext = (int**)(this + 0xA4); // +0xA4: pointer to next sibling in parent's child list
    int* newNext = (newParent != 0) ? (int*)(newParent + 0x48) : 0; // +0x48: parent's child list head pointer

    if (*ppNext != newNext) {
        if (*ppNext != 0) {
            // Remove from old parent's child list
            Entity::removeFromList(ppNext);
        }
        *ppNext = newNext;
        if (newNext != 0) {
            // Insert at end of new parent's child list
            *(int**)(this + 0xA8) = *(int**)(newNext + 4); // +0xA8: previous sibling pointer
            *(int**)(newNext + 4) = ppNext; // update parent's tail pointer (at +0x4C)
        }
    }

    if ((newParent != 0) && (*(char*)(gGameManager + 0x50) == '\0')) { // gGameManager+0x50: m_bPaused
        int gameTime = Entity::getGameTime();
        int componentId = *(int*)(newParent + 0x164); // +0x164: some component ID or handle
        if (gameTime != 0) {
            char isValid = Entity::isValid(componentId);
            if (isValid != '\0') {
                Entity::scheduleTimer(componentId, gameTime, 500, gTimerCallback); // 500ms delay
                Entity::onParentChanged();
            }
        }
    }
}