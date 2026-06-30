// FUNC_NAME: HandleTable::releaseHandle (at 0x006fc4c0)
// Role: Releases a handle from a fixed-size table of 5 entries. 
// Each entry contains 4 data ints (first set to 0x80000000 as sentinel on removal) and a handle int.
// The count of active entries (at this+0x74) is decremented when the matching handle is found.

void __thiscall HandleTable::releaseHandle(int this, int unusedParam, int handle) {
    // Entry layout (20 bytes each):
    //   +0x00: data[0] (int)
    //   +0x04: data[1] (int)
    //   +0x08: data[2] (int)
    //   +0x0c: data[3] (int)
    //   +0x10: handle (int) — the unique ID for this slot
    // So first entry starts at this+0x10, second at this+0x24, etc.
    // Count of active slots is at this+0x74.

    int* count = reinterpret_cast<int*>(this + 0x74); // +0x74: active count

    // Check slot 0 (data at +0x10, handle at +0x20)
    if (*reinterpret_cast<int*>(this + 0x20) == handle) {
        *reinterpret_cast<int*>(this + 0x10) = 0x80000000; // sentinel
        *reinterpret_cast<int*>(this + 0x14) = 0;
        *reinterpret_cast<int*>(this + 0x18) = 0;
        *reinterpret_cast<int*>(this + 0x1c) = 0;
        *reinterpret_cast<int*>(this + 0x20) = 0; // clear handle
        (*count)--;
    }

    // Slot 1 (data at +0x24, handle at +0x34)
    if (*reinterpret_cast<int*>(this + 0x34) == handle) {
        *reinterpret_cast<int*>(this + 0x24) = 0x80000000;
        *reinterpret_cast<int*>(this + 0x28) = 0;
        *reinterpret_cast<int*>(this + 0x2c) = 0;
        *reinterpret_cast<int*>(this + 0x30) = 0;
        *reinterpret_cast<int*>(this + 0x34) = 0;
        (*count)--;
    }

    // Slot 2 (data at +0x38, handle at +0x48)
    if (*reinterpret_cast<int*>(this + 0x48) == handle) {
        *reinterpret_cast<int*>(this + 0x38) = 0x80000000;
        *reinterpret_cast<int*>(this + 0x3c) = 0;
        *reinterpret_cast<int*>(this + 0x40) = 0;
        *reinterpret_cast<int*>(this + 0x44) = 0;
        *reinterpret_cast<int*>(this + 0x48) = 0;
        (*count)--;
    }

    // Slot 3 (data at +0x4c, handle at +0x5c)
    if (*reinterpret_cast<int*>(this + 0x5c) == handle) {
        *reinterpret_cast<int*>(this + 0x4c) = 0x80000000;
        *reinterpret_cast<int*>(this + 0x50) = 0;
        *reinterpret_cast<int*>(this + 0x54) = 0;
        *reinterpret_cast<int*>(this + 0x58) = 0;
        *reinterpret_cast<int*>(this + 0x5c) = 0;
        (*count)--;
    }

    // Slot 4 (data at +0x60, handle at +0x70)
    if (*reinterpret_cast<int*>(this + 0x70) == handle) {
        *reinterpret_cast<int*>(this + 0x60) = 0x80000000;
        *reinterpret_cast<int*>(this + 0x64) = 0;
        *reinterpret_cast<int*>(this + 0x68) = 0;
        *reinterpret_cast<int*>(this + 0x6c) = 0;
        *reinterpret_cast<int*>(this + 0x70) = 0;
        (*count)--;
    }
}