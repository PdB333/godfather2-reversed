// FUNC_NAME: Entity::Entity

#include <cstdint>

// Forward declarations of external functions called in constructor
void __thiscall baseInit(void);  // at 0x0078f950
void __thiscall registerObject(void* ptr, uint32_t size);  // at 0x0043b960

// External vtable pointers (from data segment)
extern void* EntityVTable;      // 0x00d69c24
extern void* EntityVTable2;     // 0x00d69c14
extern void* EntityVTable3;     // 0x00d69c10
extern void* EntityVTable4;     // 0x00d69bf8

class Entity {
public:
    // Constructor with placement flag: if flag & 1, object is registered with a manager.
    // The object size is 0x134 (308 bytes).
    __thiscall Entity(uint8_t flag) {
        // Set primary vtable pointer at offset 0x00
        this->vtable = &EntityVTable;

        // Set additional vtable pointers for multiple inheritance
        // Offset 0x3C (15 * 4) - second vtable
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x3C) = &EntityVTable2;
        // Offset 0x48 (18 * 4) - third vtable
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x48) = &EntityVTable3;
        // Offset 0x50 (20 * 4) - fourth vtable
        *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(this) + 0x50) = &EntityVTable4;

        // Call base class initialization (likely sets up other members)
        baseInit();

        // If the flag indicates heap allocation (bit 0 set), register the object
        // with the global object manager (typically for lifecycle tracking).
        if (flag & 1) {
            registerObject(this, 0x134);
        }
    }

    // Vtable pointer (offset 0x00)
    void* vtable;
    // ... (remaining members fill through offset 0x133)
};