// FUNC_NAME: HandleTable::getObjectFromSlot

struct SlotEntry {
    unsigned int id0;      // +0x00: first part of object ID
    unsigned int id1;      // +0x04: second part
    unsigned int id2;      // +0x08: third part
    unsigned int id3;      // +0x0C: fourth part
    unsigned int typeOrVtable; // +0x10: type flag or vtable pointer (if non-zero, object exists)
    // remaining 0x14 bytes unused in this function
};

// External functions (probably from EARS engine)
int __stdcall allocOrResolveObject(void* slot, int zero); // FUN_00446100
void __stdcall releaseObject(int obj);                    // FUN_0078cfd0

int __thiscall HandleTable::getObjectFromSlot(void* this, int index) {
    // Slot array starts at this+0x5c, each entry is 0x24 bytes
    SlotEntry* slot = (SlotEntry*)((char*)this + 0x5c + index * 0x24);

    unsigned int type = slot->typeOrVtable;

    // Freed sentinel values (0xBABABABA, 0xBEEFBEEF, 0xEAC15A55, 0x91100911)
    bool isIdFreed = (slot->id0 == 0xBABABABA &&
                      slot->id1 == 0xBEEFBEEF &&
                      slot->id2 == 0xEAC15A55 &&
                      slot->id3 == 0x91100911);

    bool isIdZero = (slot->id0 == 0 && slot->id1 == 0 && slot->id2 == 0 && slot->id3 == 0);
    bool isTypeEmpty = (type == 0 || type == 0x48);

    // If the slot appears empty (type 0 or 0x48) but has a non‑zero non‑freed ID,
    // it’s a stale entry – clean up the associated object.
    if (isTypeEmpty && !isIdFreed && !isIdZero) {
        int obj = allocOrResolveObject(slot, 0);
        if (obj != 0) {
            releaseObject(obj);
        }
    }

    if (type != 0) {
        // Convert stored pointer (vtable at offset +0x48 from object base) to the object pointer
        return type - 0x48;
    }
    return 0;
}