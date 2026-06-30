// FUNC_NAME: GameEntity::construct
// Address: 0x00416980
// Constructor/initializer for a game entity object. Sets default values and virtual table.
// param_1: optional parent pointer (game object?), param_2: memory location to construct into
// Returns pointer to constructed entity.

#include <cstdint>

// Forward declarations
extern int* DAT_0110ac04;         // Some default value (likely a constant)
extern int  DAT_00e2b1a4;         // Another default value (likely a constant)
extern void FUN_004a7560(int, int); // Sub-initializer
extern void FUN_00416b50();        // Additional initialization
extern int* PTR_FUN_00e2f858;      // Virtual function table for GameEntity

class GameEntity {
public:
    // Assume offset sizes and layout based on decompilation
    int* vtable;                 // +0x00
    // ... other members ...
    int field_0x04;              // +0x04 (maybe index)
    int field_0x08;              // +0x08 (pointer to something)
    int field_0x0C;              // +0x0C
    int field_0x10;              // +0x10
    int field_0x14;              // +0x14
    int field_0x18;              // +0x18
    int field_0x1C;              // +0x1C
    int field_0x20;              // +0x20
    int field_0x24;              // +0x24
    int field_0x28;              // +0x28
    int field_0x2C;              // +0x2C
    // ... others ...
    int parentPointer1;          // +0x50 (param_2[0x14])
    int parentPointer2;          // +0x54 (param_2[0x15])
    uint8_t flagByte;            // +0x62 (bits used)
    // etc.

    // Static constructor
    static GameEntity* construct(GameEntity* entity, int parent) {
        // Initial call to sub-initializer
        FUN_004a7560(0, reinterpret_cast<int>(entity)); // in_EAX is this? Using entity as second arg

        // Some global default
        int someDefault = *DAT_0110ac04;

        // Clear certain bits in flag byte (AND with 0xFA)
        entity->flagByte &= 0xFA;

        // Set initial values
        entity->field_0x58 = someDefault;   // param_2[0x16] -> offset 0x58
        entity->field_0x5C = someDefault;   // param_2[0x17] -> offset 0x5C

        // Set virtual table
        entity->vtable = &PTR_FUN_00e2f858;

        // Initialize parent pointers to 0
        entity->parentPointer1 = 0;         // param_2[0x14]
        entity->parentPointer2 = 0;         // param_2[0x15]

        // Set a marker byte to 0xFF at offset 0x60 (param_2 + 0x18 is actually [0x18] but index 24? Let's calculate:
        // *(undefined1 *)(param_2 + 0x18) = 0xff  -> offset 0x60 (since param_2 is base, +0x18*4 = +0x60)
        *(uint8_t*)((uintptr_t)entity + 0x60) = 0xFF;

        // Clear byte at offset 0x61
        *(uint8_t*)((uintptr_t)entity + 0x61) = 0;

        // Call virtual function (probably some init or get pointer)
        // param_2[2] is field at offset 8 -> likely a pointer to some internal structure
        int* internalPtr = *(int**)(entity->field_0x08);
        // Add 8 to that pointer? Actually Decompiled: (**(code **)(**(int **)(param_2[2] + 8) + 0x20))();
        // This is confusing. Possibly: take param_2[2] (offset 8), deref to int*, add 8, then deref to get another int*, then call at +0x20.
        // Then later: (**(code **)(*piVar3 + 0x48))() uses the result.
        // Let's simplify: The code is complex. We'll represent as a function call.
        int* piVar3 = (int*)(**(code**)(*(int**)(entity->field_0x08 + 8) + 0x20))();
        char cVar2 = (**(code**)(*piVar3 + 0x48))();

        // XOR flag byte with condition
        entity->flagByte ^= (cVar2 * 2) & 2; // Equivalent to set bit 1 based on cVar2

        // Now set many fields to the other default value (DAT_00e2b1a4)
        int otherDefault = *DAT_00e2b1a4;
        entity->field_0x10 = otherDefault;  // param_2[4]
        entity->field_0x14 = 0;             // param_2[5] (offsets are 4 bytes each)
        entity->field_0x18 = 0;
        entity->field_0x1C = 0;
        entity->field_0x20 = 0;
        entity->field_0x24 = otherDefault;  // param_2[9]
        entity->field_0x28 = 0;
        entity->field_0x2C = 0;
        entity->field_0x30 = 0;
        entity->field_0x34 = 0;
        entity->field_0x38 = otherDefault;  // param_2[0xe]
        entity->field_0x3C = 0;
        entity->field_0x40 = 0;
        entity->field_0x44 = 0;
        entity->field_0x48 = 0;
        entity->field_0x4C = otherDefault;  // param_2[0x13]

        // Set parent pointers if parent is non-zero
        if (parent != 0) {
            entity->parentPointer1 = parent + 0x10; // param_2[0x14] = parent + 16
            entity->parentPointer2 = parent;        // param_2[0x15] = parent
        }

        // Call sub-initializer
        FUN_00416b50();

        // Call another virtual function: offset 0x50 from internal structure
        (**(code**)(*(int*)(entity->field_0x08 + 8) + 0x50))();

        return entity;
    }
};