// FUNC_NAME: Entity::initInteraction
void __thiscall Entity::initInteraction(Entity* this, Entity* targetEntity, void* unknownParam3, int* data1, int* data2, int param6, int param7, int param8, char relationType, int param10)
{
    // Check if already initialized (byte at +0x40a)
    if (*(char*)((int)this + 0x40a) != 0) {
        return;
    }

    // If this is the same as target (self-interaction)
    if (this == targetEntity) {
        // Set state to 1 at +0x406
        *(char*)((int)this + 0x406) = 1;
        FUN_004ac8c0(unknownParam3); // Likely reference counting or init

        // Look up an object by hash 0x55859efa (e.g., "player" or "target")
        char* foundObj = nullptr;
        char result = (*(char(__thiscall**)(void*, int, void**))(*((int*)unknownParam3) + 0x10))(unknownParam3, 0x55859efa, &foundObj);
        if (result == 0) {
            foundObj = nullptr;
        } else if (foundObj != nullptr) {
            // Set some flags on found object
            *(char*)(foundObj + 0x1029) = 1;
            *(char*)((int)foundObj + 0x406) = 2; // state 2
            FUN_004ac8c0(targetEntity);
            targetEntity = foundObj; // Replace targetEntity with found object

            // Determine relation type from param9
            if (relationType == -1) {
                if (*(char*)(targetEntity + 0x6e3) == 3 || *(char*)(targetEntity + 0x6e3) == 2) {
                    *(char*)((int)this + 0x102a) = 0;
                    *(char*)(targetEntity + 0x102a) = 0;
                } else {
                    *(char*)((int)this + 0x102a) = 2;
                    *(char*)(targetEntity + 0x102a) = 2;
                }
            } else {
                *(char*)((int)this + 0x102a) = relationType;
                *(char*)(targetEntity + 0x102a) = relationType;
            }
            goto commonInit;
        }
        // If not found, set default relation type 0
        *(char*)((int)this + 0x102a) = 0;
    } else {
        // Different entities: set state on this to 2, target to 1
        *(char*)((int)this + 0x406) = 2;
        FUN_004ac8c0(targetEntity);
        *(char*)((int)this + 0x1029) = 1;
        *(char*)((int)targetEntity + 0x406) = 1;
        FUN_004ac8c0(unknownParam3);
    }

commonInit:
    // Store initial data from parameters
    this[0x401] = *data1;           // +0x1004
    this[0x402] = *data2;           // +0x1008
    this[0x404] = param6;           // +0x1010
    this[0x403] = param6;           // +0x100C (duplicate)
    this[0x405] = param7;           // +0x1014
    this[0x407] = param8;           // +0x101C
    this[0x409] = param10;          // +0x1024
    this[0x408] = param8;           // +0x1020 (duplicate)
    *(char*)((int)this + 0x40a) = 1; // mark initialized

    // If target exists, copy same data to target's equivalent fields (starting at +0x3ff int offset)
    if (targetEntity != nullptr) {
        // Pointer to target's field block at offset 0x3ff*4 (0xFFC)
        int* targetFields = targetEntity + 0x3ff;
        targetFields[2] = *data1;    // +0x1004
        targetFields[3] = *data2;    // +0x1008
        targetFields[5] = param6;    // +0x1010
        targetFields[4] = param6;    // +0x100C
        targetFields[6] = param7;    // +0x1014
        targetFields[8] = param8;    // +0x101C
        targetFields[10] = param10;  // +0x1024
        targetFields[9] = param8;    // +0x1020
        *(char*)(targetFields + 0xb) = 1; // mark target's initialized at +0x40a

        // Call vtable function at offset 0x2f4 (likely update)
        (**(void(__thiscall**)(int*))(*this + 0x2f4))(this);
    }

    // Set flag bits (0x20 and 0x40) at offset 0x25c
    this[0x25c] |= 0x20;
    this[0x25c] |= 0x40;
    if (targetEntity != nullptr) {
        targetEntity[0x25c] |= 0x20;
        targetEntity[0x25c] |= 0x40;

        // Compute direction from this to target (or vice versa)
        // Get positions from two objects (likely some component's matrix)
        int* posA = FUN_00471610(); // Get position A
        int* posB = FUN_00471610(); // Get position B
        float dx = *(float*)(posB + 0x30) - *(float*)(posA + 0x30); // x offset at +0x30
        float dz = *(float*)(posB + 0x38) - *(float*)(posA + 0x38); // z at +0x38
        float dy = *(float*)(posB + 0x34) - *(float*)(posA + 0x34); // y at +0x34

        // Normalize vector (in-place)
        FUN_0056afa0(&dx, &dx);

        // Store normalized direction in this (two floats packed, one float separate)
        *(ulonglong*)(this + 0x40b) = reinterpret_cast<ulonglong&>(dx); // low two floats (x,y)
        this[0x40d] = *(int*)&dz; // z component

        // Also store in target
        *(ulonglong*)(targetEntity + 0x40b) = reinterpret_cast<ulonglong&>(dx);
        targetEntity[0x40d] = *(int*)&dz;

        // Check dot product with another direction to decide facing
        int* obj1 = FUN_00471610(); // another position source
        int* obj2 = FUN_00471610(); // another position source
        int* local_30 = obj2 + 0x20; // forward vector start at +0x20
        int* obj3 = FUN_00471610(); // yet another
        float dot = *(float*)(obj1 + 0x20) * dx + *(float*)(local_30[1]) * dy + *(float*)(obj3 + 0x28) * dz;
        if (dot < 0.0f) {
            this[0x409] = DAT_00d71b08;    // global value
            targetEntity[0x409] = DAT_00d71b08;
        }
    }
}