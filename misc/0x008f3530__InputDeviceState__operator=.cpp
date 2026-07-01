//FUNC_NAME: InputDeviceState::operator=
// Function address: 0x008f3530
// Role: Copy assignment operator for InputDeviceState (64-byte button array + 256-byte analog array + extra fields)
// Structure layout:
//   +0x000: uint8_t buttonState[0x40]   // 64 bytes of digital button states
//   +0x040: uint8_t analogState[0x100]  // 256 bytes of analog input states
//   +0x140: uint32_t flags1
//   +0x144: uint32_t flags2
//   +0x148: uint64_t timestamp1
//   +0x150: uint64_t timestamp2
//   +0x158: SubObject subObj            // copied via FUN_00accd60

class InputDeviceState {
public:
    InputDeviceState& operator=(const InputDeviceState& other) {
        // Copy first 64 bytes (button states)
        for (int i = 0; i < 0x40; i++) {
            reinterpret_cast<uint8_t*>(this)[i] = reinterpret_cast<const uint8_t*>(&other)[i];
        }
        // Copy next 256 bytes (analog states)
        for (int i = 0; i < 0x100; i++) {
            reinterpret_cast<uint8_t*>(this)[0x40 + i] = reinterpret_cast<const uint8_t*>(&other)[0x40 + i];
        }
        // Copy fields at offsets 0x140-0x158
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x140) = *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(&other) + 0x140);
        *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(this) + 0x144) = *reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(&other) + 0x144);
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(this) + 0x148) = *reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(&other) + 0x148);
        *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(this) + 0x150) = *reinterpret_cast<const uint64_t*>(reinterpret_cast<const uint8_t*>(&other) + 0x150);
        // Copy sub-object at offset 0x158
        FUN_00accd60(reinterpret_cast<uint8_t*>(this) + 0x158, reinterpret_cast<const uint8_t*>(&other) + 0x158);
        return *this;
    }
};

// External helper function for sub-object copy (likely another assignment or memcpy)
extern void FUN_00accd60(void* dest, const void* src);