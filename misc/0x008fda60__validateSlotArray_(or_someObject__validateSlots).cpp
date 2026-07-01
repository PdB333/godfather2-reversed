// FUNC_NAME: validateSlotArray (or someObject::validateSlots)
// This function checks an array of three 8-byte slots. Each slot consists of a 4-byte ID field and a 4-byte name field (only first char checked).
// It returns 0 if any slot has a non-zero ID but an empty name (first null byte) – considered invalid – otherwise returns 1 (all slots valid).
// Address: 0x008fda60

typedef struct {
    int32_t id;       // +0x00 from slot base (e.g., object+0x78)
    char    name[4];  // +0x04 (only name[0] is checked for null)
} Slot;

__fastcall int validateSlotArray(uintptr_t obj) {
    uint32_t slotIndex = 0;
    char* slotBase = (char*)(obj + 0x7c); // points to name[0] of first slot, id is at slotBase-4

    while (true) {
        Slot* currentSlot = (Slot*)(slotBase - 4); // id at slotBase-4, name at slotBase
        // Continue if id is zero (slot unused) OR name first char is non-null (name present)
        if (currentSlot->id != 0 && currentSlot->name[0] == '\0') {
            return 0; // Found invalid slot: id present but empty name
        }
        ++slotIndex;
        slotBase += 8; // Move to next slot (each 8 bytes)
        if (slotIndex > 2) {
            return 1; // All slots checked, none invalid
        }
    }
}