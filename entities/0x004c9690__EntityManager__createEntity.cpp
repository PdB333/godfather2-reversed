// FUNC_NAME: EntityManager::createEntity
void EntityManager::createEntity(uint32_t param_1)
{
    // Global entity manager singleton pointer
    EntityManager* entityManager = reinterpret_cast<EntityManager*>(g_entityManager);
    if (entityManager == nullptr)
        return;

    // Check that the container and related data are valid (offsets +0x10 and +0x14)
    if (entityManager->container == nullptr || entityManager->containerData == nullptr)
        return;

    // Allocate memory for a new entity (size 0x37c = 892 bytes)
    Entity* newEntity = reinterpret_cast<Entity*>(Alloc(0x37c));
    if (newEntity == nullptr) {
        newEntity = nullptr; // Redundant, but matches code
    } else {
        // Initialize the new entity with the given parameter (likely an ID or type)
        Entity::constructor(newEntity, param_1);
    }

    // Pack the entity pointer and its type field (+0x08) into a 64-bit value
    uint64_t packedData = (static_cast<uint64_t>(newEntity->type) << 32) | reinterpret_cast<uint32_t>(newEntity);

    // Buffer for key (16 bytes, used by the add function)
    uint8_t keyBuffer[16];

    // Add the entity to the container (offset +0x10 in the manager)
    AddResult* result = reinterpret_cast<AddResult*>(
        entityManager->container->add(keyBuffer, &packedData)
    );

    // Unpack the result
    uint64_t resultData = result->data;
    uint32_t resultFlags = result->flags;

    // If the low byte of result flags is zero, the add failed
    if ((resultFlags & 0xFF) == 0) {
        // Delete the entity on failure
        Free(newEntity);
    }
}