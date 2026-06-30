// FUNC_NAME: EntityManager::removeFromActiveList
void __fastcall EntityManager__removeFromActiveList(EntityManager* this, Entity* entity)
{
    // get current count of active entities (offset 0x204)
    int activeCount = this->activeCount;
    // decrement count
    this->activeCount = activeCount - 1;
    // new count after removal
    int newCount = this->activeCount;

    // entity's current index (offset 0x2c)
    int entityIndex = entity->listIndex;

    if (entityIndex != newCount) {
        // entity is not the last active one, so swap with the last
        Entity** array = this->activeArray; // pointer to array of entity pointers (offset 0x1fc)
        Entity* lastEntity = array[newCount];   // entity currently at the new end

        // update the swapped entity's index
        lastEntity->listIndex = entityIndex;

        // move the last entity into the vacated slot
        array[entityIndex] = lastEntity;

        // place the entity being removed at the former end
        array[newCount] = entity;

        // update the entity's index to the new position (which is now beyond the active count)
        entity->listIndex = newCount;
    }
    // else: entity was already the last active element, just decrement count and let it be overwritten later
}