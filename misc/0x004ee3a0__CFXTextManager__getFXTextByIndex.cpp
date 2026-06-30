// FUNC_NAME: CFXTextManager::getFXTextByIndex
// Address: 0x004ee3a0
// This function iterates through a list of text slots and returns a pointer to the n-th active CFXText object.
// The container has a count at +0x80 (short), and an array of slot structures starting at +0xF0.
// Each slot is 0x14 bytes; at slot offset +4 is a pointer to the text object.
// It checks the object's vtable function at +8 returns "FXText" class name, and field at +0x24 is non-zero.

class CFXText; // Forward declaration

class CFXTextManager {
public:
    CFXText* getFXTextByIndex(int index);
    // Offset 0x80: short m_nTextSlotCount;
    // Offset 0xF0: Slot m_TextSlots[?]; each slot is 0x14 bytes.
};

// Slot structure assumed (partial):
struct TextSlot {
    int someField;      // +0x00
    CFXText* pText;     // +0x04
    // ... remaining 0x10 bytes ...
};

CFXText* CFXTextManager::getFXTextByIndex(int index) {
    short count;
    if (*(int*)this == 0) {
        count = 0;
    } else {
        count = *(short*)(*(int*)this + 0x80);
    }

    if (count == 0) {
        return nullptr;
    }

    int foundCount = 0;
    int slotOffset = 0xF0; // Start of slots array

    for (int i = 0; i < count; i++) {
        if (*(int*)this != 0) {
            int slotAddr = *(int*)this + slotOffset;
            if (slotAddr != 0) {
                CFXText* pText = *(CFXText**)(slotAddr + 4);
                if (pText != nullptr) {
                    // Call virtual function at vtable+8 to get class name/identifier
                    // This function returns a pointer to a string (or type info)
                    void* typeInfo = (**(code**)(*(int*)pText + 8))();
                    if (typeInfo != 0) {
                        // Compare class name to "FXText" (7 characters)
                        bool match = true;
                        char* name = *(char**)((int)typeInfo + 4);
                        char* target = "FXText";
                        for (int j = 0; j < 6; j++) { // Actually loop iterates 7 times? In asm: iVar3=7, do while-- -> 7 compares
                            if (name[j] != target[j]) {
                                match = false;
                                break;
                            }
                        }
                        if (match && *(int*)(pText + 9) != 0) { // +0x24 (since int* offset 9 = 9*4=36=0x24)
                            if (foundCount == index) {
                                return pText;
                            }
                            foundCount++;
                        }
                    }
                }
            }
        }
        slotOffset += 0x14; // Move to next slot (20 bytes stride)
    }
    return nullptr;
}