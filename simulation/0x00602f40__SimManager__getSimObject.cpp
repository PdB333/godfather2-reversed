// FUNC_NAME: SimManager::getSimObject
// Function address: 0x00602f40
// Returns a pointer to a sim object by index. If index is 0xFFFFFFFF, uses the current index stored at this+0x40.
// The object array is managed by a data structure pointed to by this+0x20.
// Each object is 0x60 bytes. The array base is at data+0xB0, count at data+0xA8.
// If index is out of range, returns a static null object at 0x012222C8.

class SimManager {
public:
    // +0x20: pointer to internal data array descriptor (struct with count at +0xA8 and base at +0xB0)
    // +0x40: current object index (uint)
    void* getSimObject(uint index) {
        if (index == 0xFFFFFFFF) {
            index = *(uint*)((uintptr_t)this + 0x40);
        }
        void* dataArray = *(void**)((uintptr_t)this + 0x20);
        uint count = *(uint*)((uintptr_t)dataArray + 0xA8);
        if (index < count) {
            uintptr_t base = *(uintptr_t*)((uintptr_t)dataArray + 0xB0);
            return (void*)(base + index * 0x60);
        }
        // Return static sentinel (null object)
        return (void*)0x012222C8;
    }
};