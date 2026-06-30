// FUNC_NAME: SlotProcessor::processSlotByPointer
// Function address: 0x006f0e00
// Role: Searches a fixed array of 2 pointer slots at this+0x2c for a matching pointer, then invokes an action handler.

class SlotProcessor {
public:
    struct Slot {
        int* pointer;  // +0x00
        char pad[28];   // +0x04 to +0x1F (total 32 bytes per slot)
    };
    // slots array at this+0x2c: Slot slots[2]; // slots[0] at +0x2c, slots[1] at +0x4c

    void __thiscall processSlotByPointer(int* pointer, int param3) {
        if (pointer == nullptr || *pointer == 0) {
            return;
        }
        for (int i = 0; i < 2; ++i) {
            if (slots[i].pointer == pointer) {
                handleSlotAction(param3);
                return;
            }
        }
    }

private:
    void handleSlotAction(int param3); // FUN_006f09f0
};