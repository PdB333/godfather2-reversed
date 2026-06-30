// FUNC_NAME: EntityComponent::EntityComponent
// Function address: 0x004cb440
// Role: Constructor for EntityComponent class, initializes fields and optionally sets up parent linkage.

extern void* PTR_FUN_00e3663c; // vtable pointer
extern void FUN_005dde90(); // unknown setup function

class EntityComponent {
public:
    void* vtable;          // +0x00
    int field_4;           // +0x04
    int parentOffset;      // +0x08 (self-relative offset to parent, adjusted to pointer)
    int field_C;           // +0x0C (set to parent + 0x38 if condition met)
    int field_10;          // +0x10 (set to parent pointer if condition met)
    int field_14;          // +0x14
    byte field_18;         // +0x18

    // __thiscall constructor, 'this' in ECX, 'parent' in EDI
    void __thiscall constructor(void* parent) {
        field_4 = 0;
        vtable = &PTR_FUN_00e3663c;
        field_C = 0;
        field_10 = 0;
        field_14 = 0;
        field_18 = 0;

        // Adjust self-relative pointer if non-zero
        if (parentOffset != 0) {
            parentOffset = parentOffset + (int)this;
        }

        // If parent is valid and its type at offset 0x20 equals 0xf, set up sub-object linkage
        if (parent != 0 && *(int*)(parentOffset + 0x20) == 0xf) {
            FUN_005dde90();
            field_C = parentOffset + 0x38;
            field_10 = (int)parent;
        }
    }
};