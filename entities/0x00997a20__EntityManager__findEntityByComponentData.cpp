// FUNC_NAME: EntityManager::findEntityByComponentData
int __thiscall EntityManager::findEntityByComponentData(int componentData)
{
    int internalId;
    int entityCount;
    int entityIndex;
    int componentCount;
    int componentIndex;
    int componentInfo[2];
    Entity** entityArray;

    internalId = convertToInternalId(componentData);
    entityCount = *(int *)(*(int *)(this + 0x20) + 0xc); // m_entities.count
    if (entityCount < 1) {
        return 0;
    }
    entityArray = *(Entity***)(*(int *)(this + 0x20) + 8); // m_entities.array
    for (entityIndex = 0; entityIndex < entityCount; entityIndex++) {
        componentCount = *(int *)(*entityArray + 0x78); // entity->componentCount
        if (0 < componentCount) {
            int* componentTypeArray = *(int**)(*entityArray + 0x74); // entity->componentTypes
            for (componentIndex = 0; componentIndex < componentCount; componentIndex++) {
                if (componentTypeArray[componentIndex] == 0x34133103) { // hash for specific component type
                    getComponentInfo(componentInfo, 0x34133103);
                    if (componentInfo[0] == internalId) {
                        // Found matching entity
                        return getEntityHandle(entityIndex);
                    }
                    break; // Only one component of this type per entity?
                }
            }
        }
        entityArray++;
    }
    return 0;
}