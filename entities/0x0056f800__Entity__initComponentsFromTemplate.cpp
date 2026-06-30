// FUNC_NAME: Entity::initComponentsFromTemplate
void Entity::initComponentsFromTemplate(const Entity* source)
{
    // Check and initialize AI component (offset +0x34)
    if (source->aiComponent != 0 && this->aiComponent == 0) {
        // FUN_0056f270 likely creates an AI component from a resource ID stored at source->aiComponent->resourceId (+0x0C)
        this->aiComponent = createAIComponent(source->aiComponent->resourceId);
    }

    // Check and initialize physics component (offset +0x38)
    if (source->physicsComponent != 0 && this->physicsComponent == 0) {
        // FUN_0056ef10 creates physics component
        this->physicsComponent = createPhysicsComponent(source->physicsComponent->resourceId);
    }

    // Check and initialize audio component (offset +0x3C)
    if (source->audioComponent != 0 && this->audioComponent == 0) {
        // FUN_005807d0 creates audio component
        this->audioComponent = createAudioComponent(source->audioComponent->resourceId);
        // FUN_005804f0 likely post-initializes audio
        postInitAudio();
    }

    // Check and initialize animation component (offset +0x40)
    if (source->animationComponent != 0 && this->animationComponent == 0) {
        // FUN_00580b40 creates animation component
        this->animationComponent = createAnimationComponent(source->animationComponent->resourceId);
        // FUN_00580920 post-initializes animation
        postInitAnimation();
    }

    // Check and initialize inventory component (offset +0x44)
    if (source->inventoryComponent != 0 && this->inventoryComponent == 0) {
        // FUN_0056eb00 creates inventory component, returns pointer to it
        InventoryComponent* inv = createInventoryComponent(source->inventoryComponent->resourceId);
        this->inventoryComponent = inv;
        // Initialize inventory slots: each slot is 8 bytes (two ints) starting at +0x10 from inv
        int numSlots = inv->slotCount;  // +0x0C
        int* slotData = inv->slots;     // +0x10
        int defaultValue = DAT_00e2b1a4; // some global constant (e.g., -1 or 0)
        for (int i = 0; i < numSlots; i++) {
            slotData[i * 2] = 0xFFFFFFFF;     // first field = -1 (empty slot id)
            slotData[i * 2 + 1] = defaultValue; // second field = default value
        }
    }
}