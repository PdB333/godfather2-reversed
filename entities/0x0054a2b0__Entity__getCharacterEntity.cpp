// FUNC_NAME: Entity::getCharacterEntity
// Address: 0x0054a2b0
// Returns the character entity from a target pointer, handling vehicles (type 0xb) returning their driver (offset +0x34) if it is a character (type 0xa).

// Known enum (likely from game code):
enum EntityType : int {
    eTypeUnknown = 0,
    eTypeCharacter = 0xa,
    eTypeVehicle = 0xb
};

class Entity {
public:
    // Offsets:
    // +0x10: m_pTargetEntity (Entity*)
    // +0x0c: m_eType (EntityType)
    // For vehicles:
    // +0x34: m_pDriver (Entity*)

    Entity* __thiscall getCharacterEntity();
};

Entity* __thiscall Entity::getCharacterEntity() {
    Entity* entity = *(Entity**)(this + 0x10);          // Get target entity
    Entity* result = nullptr;

    if (entity) {
        int type = *(int*)(entity + 0xc);               // Read type
        if (type == eTypeVehicle) {
            Entity* driver = *(Entity**)(entity + 0x34); // Get driver
            if (driver) {
                int driverType = *(int*)(driver + 0xc);  // Driver's type
                if (driverType == eTypeCharacter) {
                    result = driver;
                }
            }
        } else if (type == eTypeCharacter) {
            result = entity;
        }
    }
    return result;
}