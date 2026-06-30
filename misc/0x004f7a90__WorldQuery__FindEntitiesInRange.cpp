// FUNC_NAME: WorldQuery::FindEntitiesInRange
// Address: 0x004f7a90
// This function iterates a linked list of game entities, filters them by four integer fields (presumably type/group IDs)
// and optionally by distance to a point. Matching entities are stored in a result array up to a maximum count.
// The filter is passed in register EDI (int[4]) and extraRadius in XMM2.
// The calling convention is __fastcall with result in EDX, maxCount on stack, position on stack, extraRadius in XMM2.

struct GameEntity {
    // +0x00: unknown data
    // +0x10: flags (bit0 must be 0 for valid entity)
    unsigned char flags[0x10];  // offset 0x10
    int filterField0;           // +0x18
    int filterField1;           // +0x1C
    int filterField2;           // +0x20
    int filterField3;           // +0x24
    float radius;               // +0x28
    // +0x2C: unknown padding
    // +0x70: position
    float posX;                 // +0x70
    float posY;                 // +0x74
    float posZ;                 // +0x78
    GameEntity* next;           // +0xC4
};

struct FindEntitiesResult {
    char unknown_0x10[0x10];       // +0x00
    GameEntity* entityList;        // +0x10  (linked list head)
    GameEntity* results[10];       // +0x1C  (up to 10 pointers)
    int count;                     // +0x44
};

// __fastcall: ECX unused, EDX = result pointer, EDI = filter pointer (const int[4])
void __fastcall FindEntitiesInRange(FindEntitiesResult* result, int maxCount, const float* position, float extraRadius, const int* filter) {
    GameEntity* current = result->entityList;  // param_2 + 0x10

    // clamp maxCount to 10
    if (maxCount <= 0 || maxCount > 10) {
        maxCount = 10;
    }

    result->count = 0;

    while (current != nullptr) {
        // Filter check: compare entity fields with filter[0..3] and check flag bit0
        bool matches = (current->filterField2 == filter[2]) &&
                       (current->filterField3 == filter[3]) &&
                       (current->filterField0 == filter[0]) &&
                       (current->filterField1 == filter[1]) &&
                       ((current->flags[0x10] & 1) == 0);  // +0x10 byte, bit0 must be zero

        if (matches) {
            // Optionally check distance
            if (position != nullptr) {
                float dx = position[0] - current->posX;   // param_4[0]
                float dy = position[1] - current->posY;   // param_4[1]
                float dz = position[2] - current->posZ;   // param_4[2]
                float distSq = dx*dx + dy*dy + dz*dz;
                float checkRadius = current->radius + extraRadius;  // extraRadius from XMM2
                if (extraRadius == 0.0f || distSq < checkRadius * checkRadius) {
                    // Within distance
                } else {
                    matches = false;
                }
            }
        }

        if (matches) {
            // Add to results array if still space
            if (result->count >= maxCount) {
                return;  // buffer full, return current count
            }
            result->results[result->count] = current;
            result->count++;
        }

        current = current->next;  // +0xC4
    }

    // Return final count (implicitly via EDX? but function returns int)
    // The original returns result->count at the end
}