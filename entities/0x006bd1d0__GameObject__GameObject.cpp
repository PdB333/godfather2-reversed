// FUNC_NAME: GameObject::GameObject
#include <cstdint>

class GameObject {
public:
    // vtable at offset 0x00
    // +0x3C: secondary vtable (interface)
    // +0x48: tertiary vtable (another interface)
    // +0x50: first byte of a flag/union (1 byte)
    // +0x54: int32 zero
    // +0x58: int32 zero
    // +0x5C: int32 zero
    // +0x60: int32 zero
    // +0x64: int32 zero
    // +0x68: int32 zero
    // +0x6C: int32 zero
    // +0x70: int32 zero
    // +0x74: int32 zero
    // +0x78: int32 zero
    // +0x7C: int32 zero

    static GameObject** g_objectArray; // DAT_0112a6a0
    static int g_objectArrayCount;     // DAT_0112a6a4
    static int g_objectArrayCapacity;  // DAT_0112a6a8

    // Constructor
    __thiscall GameObject(uint32_t arg) {
        // Call base class initializer (likely some EARS framework init)
        baseClassInit(arg);

        // Set vtable pointers
        *this = &PTR_FUN_00d5ea20; // primary vtable
        this[0x0F] = &PTR_LAB_00d5ea10; // secondary vtable at +0x3C
        this[0x12] = &PTR_LAB_00d5ea0c; // tertiary vtable at +0x48

        // Zero out data block from +0x50 to +0x7C
        // +0x50: single byte (flag)
        *(uint8_t*)(this + 0x14) = 0;
        this[0x15] = 0; // +0x54
        this[0x16] = 0; // +0x58
        this[0x17] = 0; // +0x5C
        this[0x18] = 0; // +0x60
        this[0x19] = 0; // +0x64
        this[0x1A] = 0; // +0x68
        this[0x1B] = 0; // +0x6C
        this[0x1C] = 0; // +0x70
        this[0x1D] = 0; // +0x74
        this[0x1E] = 0; // +0x78
        this[0x1F] = 0; // +0x7C

        // Grow the global object array if needed
        if (g_objectArrayCount == g_objectArrayCapacity) {
            int newCapacity = (g_objectArrayCapacity == 0) ? 1 : (g_objectArrayCapacity * 2);
            resizeGlobalObjectArray(newCapacity); // FUN_006bca00
        }

        // Register this object into the global array
        GameObject** slot = g_objectArray + g_objectArrayCount;
        g_objectArrayCount++;
        if (slot != nullptr) {
            *slot = this;
        }

        // Set global flags/masks
        setGlobalFlag(&DAT_01206778, 0x8001); // FUN_004086b0
        setGlobalFlag(&DAT_0120e93c, 0x7FFF); // FUN_004086b0
    }

private:
    void baseClassInit(uint32_t arg); // FUN_0046c590
    static void resizeGlobalObjectArray(int newCapacity); // FUN_006bca00
    static void setGlobalFlag(uint32_t* flagAddr, uint16_t mask); // FUN_004086b0
};

// Global static definitions would go here (from DAT addresses)
GameObject** GameObject::g_objectArray = nullptr;
int GameObject::g_objectArrayCount = 0;
int GameObject::g_objectArrayCapacity = 0;
```