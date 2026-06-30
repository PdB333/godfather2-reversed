// FUNC_NAME: Entity::queryInterface

#include <cstdint>

// Forward declaration
class Entity;

// Reconstructed function: Checks if this Entity supports a given interface type ID.
// If the type ID matches one of the known IDs, sets outInterface to 'this' and returns true.
// Otherwise sets outInterface to nullptr and returns false.
bool __thiscall Entity::queryInterface(uint32_t typeId, void** outInterface) {
    // Early success for specific type ID
    if (typeId == 0x55645e11) {
        *outInterface = this;
        return true;
    }

    *outInterface = nullptr;

    // Group of type IDs that succeed if they fall into specific ranges
    if (typeId < 0xae986324) {
        // Accept these two IDs directly (they skip the inner check)
        if (typeId == 0xae986323 || typeId == 0x197c1972) {
            *outInterface = this;
            return true;
        }
        // Accept this ID only if a secondary check passes (which it does)
        if (typeId == 0x38523fc3) {
            *outInterface = this;
            return true;
        }
    } else {
        // Accept this single ID in the higher range
        if (typeId == 0xf8b45dfb) {
            *outInterface = this;
            return true;
        }
    }

    // No match: outInterface remains nullptr (already set)
    return false;
}