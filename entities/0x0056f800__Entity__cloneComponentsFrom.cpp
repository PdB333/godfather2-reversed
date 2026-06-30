// FUNC_NAME: Entity::cloneComponentsFrom
void Entity::cloneComponentsFrom(Entity* source)
{
    // +0x34: AIComponent pointer
    if (source->aiComponent != 0 && this->aiComponent == 0) {
        this->aiComponent = createAIComponent(source->aiComponent->id); // FUN_0056f270
    }
    // +0x38: PhysicsComponent pointer
    if (source->physicsComponent != 0 && this->physicsComponent == 0) {
        this->physicsComponent = createPhysicsComponent(source->physicsComponent->id); // FUN_0056ef10
    }
    // +0x3c: RenderComponent pointer
    if (source->renderComponent != 0 && this->renderComponent == 0) {
        this->renderComponent = createRenderComponent(source->renderComponent->id); // FUN_005807d0
        initRenderComponent(); // FUN_005804f0
    }
    // +0x40: AudioComponent pointer
    if (source->audioComponent != 0 && this->audioComponent == 0) {
        this->audioComponent = createAudioComponent(source->audioComponent->id); // FUN_00580b40
        initAudioComponent(); // FUN_00580920
    }
    // +0x44: InputMappingComponent pointer
    if (source->inputMapping != 0 && this->inputMapping == 0) {
        this->inputMapping = createInputMapping(source->inputMapping->id); // FUN_0056eb00
        // Initialize mapping table: each entry is a pair (actionID, deviceID)
        int* mappingTable = this->inputMapping->mappingTable; // +0x10
        int numEntries = this->inputMapping->numEntries; // +0xc
        for (int i = 0; i < numEntries; i++) {
            mappingTable[i * 2] = -1; // actionID = -1 (unbound)
            mappingTable[i * 2 + 1] = DAT_00e2b1a4; // deviceID from global (likely default device)
        }
    }
}