// FUNC_NAME: Entity::getDataIfGameActive
// Function address: 0x008c6d80
// Role: Returns data from the entity only if the game is active and the entity is valid.

class Entity {
public:
    void* getDataIfGameActive() {
        // Check if this entity pointer is valid
        if (this != nullptr) {
            // Check global game active state (likely from GameManager or similar)
            if (isGameActive()) {
                // Call internal method to retrieve the desired data
                return getData();
            }
        }
        return nullptr;
    }
};