//FUNC_NAME: countDeadEntities
int countDeadEntities(void)
{
    int deadCount = 0;
    uint entityCount = getEntityCount();          // FUN_00604350: total number of entities
    uint index = 0;
    if (entityCount != 0) {
        do {
            if (isEntityActive(index)) {          // FUN_00602f00: check if entity at index is active
                int entityHandle = getEntityByIndex(index); // FUN_00602e60: get entity handle
                int health = getEntityHealth(entityHandle); // FUN_00602ff0: get entity health (negative = dead)
                if (health < 0) {
                    deadCount++;
                }
            }
            index++;
        } while (index < entityCount);
    }
    return deadCount;
}