// FUNC_NAME: Entity::getEntityType
int Entity::getEntityType(void) {
    int result = 0; // default return for invalid/case7 fallthrough
    EntityData* data = getEntityData(this); // FUN_008c6d50, returns pointer to entity data
    if (data != nullptr) {
        int typeID = *(int*)(data + 0x4); // +0x4: entity type enum (1-7)
        switch (typeID) {
            case 1: return 1;
            case 2: return 2;
            case 3: return 3;
            case 4: return 4;
            case 5: return 5;
            case 6: return 6;
            case 7:
                result = 7;
                break;
        }
    }
    return result; // 0 for invalid data, or 7 for case 7
}