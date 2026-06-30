// FUNC_NAME: SomeClass::clearAllSlots
// Address: 0x005e8470
// This function clears all slots in 4 groups of 5 slots each.
// Each slot holds a pointer to an object and a destructor function pointer.
// The slot structure (16 bytes):
//   +0x00: void* object
//   +0x04: int unknown1
//   +0x08: int unknown2
//   +0x0C: void (*destructor)(void*)
// The class has a member at +0x1C that points to the start of a group of 4 such slot arrays.
// Each group contains 5 slots spaced 16 bytes apart, but the base pointer is offset by 24 bytes from the first slot.
// After destroying, the object pointer and the two unknown fields are zeroed.

#include <cstdint>

class SomeClass {
public:
    void clearAllSlots() {
        // 'this' is passed in EAX
        uint32_t* base = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x1C);
        // There are 4 groups (chunks) of 5 slots each.
        for (int chunk = 0; chunk < 4; ++chunk) {
            // Slot 0: object at base[-6], destructor at base[-3], unknowns at base[-5] and base[-4]
            if (base[-6] != 0) {
                reinterpret_cast<void (*)(void*)>(base[-3])(reinterpret_cast<void*>(base[-6]));
            }
            base[-6] = 0;
            base[-5] = 0;
            base[-4] = 0;

            // Slot 1: object at base[-2], destructor at base[1], unknowns at base[-1] and base[0]
            if (base[-2] != 0) {
                reinterpret_cast<void (*)(void*)>(base[1])(reinterpret_cast<void*>(base[-2]));
            }
            base[-2] = 0;
            base[-1] = 0;
            base[0] = 0;

            // Slot 2: object at base[2], destructor at base[5], unknowns at base[3] and base[4]
            if (base[2] != 0) {
                reinterpret_cast<void (*)(void*)>(base[5])(reinterpret_cast<void*>(base[2]));
            }
            base[2] = 0;
            base[3] = 0;
            base[4] = 0;

            // Slot 3: object at base[6], destructor at base[9], unknowns at base[7] and base[8]
            if (base[6] != 0) {
                reinterpret_cast<void (*)(void*)>(base[9])(reinterpret_cast<void*>(base[6]));
            }
            base[6] = 0;
            base[7] = 0;
            base[8] = 0;

            // Slot 4: object at base[10], destructor at base[13], unknowns at base[11] and base[12]
            if (base[10] != 0) {
                reinterpret_cast<void (*)(void*)>(base[13])(reinterpret_cast<void*>(base[10]));
            }
            base[10] = 0;
            base[11] = 0;
            base[12] = 0;

            // Move to the next chunk: each chunk is 108 bytes (27 * 4)
            base += 27; // 27 * 4 bytes = 108 bytes
        }
    }
};