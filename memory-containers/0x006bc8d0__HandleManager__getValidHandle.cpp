// FUNC_NAME: HandleManager::getValidHandle
// Function address: 0x006bc8d0
// Role: Returns the given handle ID if it is valid according to the
//   virtual method at vtable offset 0x10, otherwise returns 0.
// The virtual method likely checks if the handle corresponds to a
//   valid object and returns a non‑zero char if so.

#include <cstdint>

class HandleManager {
public:
    uint32_t getValidHandle(uint32_t handleId) {
        int32_t out = 0;
        // Virtual function at vtable+0x10 (4th slot) – takes handleId and output pointer,
        // returns char (non‑zero = valid)
        typedef char (__thiscall *IsValidFunc)(void*, uint32_t, int32_t*);
        IsValidFunc isValid = (IsValidFunc)(*(int**)this)[4];
        char result = isValid(this, handleId, &out);
        // Return 0 if invalid, unchanged handle if valid
        return -(uint32_t)(result != 0) & handleId;
    }
};