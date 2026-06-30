// FUNC_NAME: MessageManager::MessageManager

#include <cstdint>

// Global string variables (likely defined elsewhere)
extern uint32_t g_iMsgBankUpdateMoney;
extern uint32_t g_iMsgTransferStolenMoney;
extern uint32_t g_iMsgPlayerReset;
extern uint32_t g_iMsgEndTruckHeist;
extern uint32_t g_iMsgEndFakeBankHeist;

// Forward declaration of helper functions
uint32_t* __stdcall FUN_00408240(uint32_t* strPtr, const char* string);
void __stdcall FUN_00408900(void* obj, uint32_t* strPtr, uint32_t flags); // registers message

// Struct representing a single message slot (20 slots, each 48 bytes)
struct MessageSlot {
    int32_t field_00;  // +0x00
    int32_t field_04;  // +0x04
    int32_t field_08;  // +0x08
    int32_t field_0C;  // +0x0C
    int32_t id;        // +0x10 (initialized to -1)
    int32_t field_14;  // +0x14
    int32_t field_18;  // +0x18
    int32_t field_1C;  // +0x1C
    int32_t field_20;  // +0x20 (not explicitly set)
    int32_t type;      // +0x24 (initialized to 4)
    int32_t field_28;  // +0x28
    int32_t field_2C;  // +0x2C
};

// Main class
class MessageManager {
public:
    // Virtual table pointer at +0x00 (set to &PTR_FUN_00d5db44)
    // Second vtable pointer at +0x04 (set to &PTR_LAB_00d5db34)
    int32_t someFlag1;          // +0x08 (set to 1)
    int32_t someFlag2;          // +0x0C (set to 0)
    MessageSlot slots[20];       // +0x10 (each 48 bytes, total 960 bytes)
    int32_t maxSlotCount;        // +0x3D0 (set to 20)
    uint32_t* pBankUpdateMoney;  // +0x3F0 (points to g_iMsgBankUpdateMoney)
    uint16_t padding3F4;         // +0x3F4
    uint16_t padding3F6;         // +0x3F6
    // Following fields (0x3D4-3EC) are zeroed, but not named

    MessageManager() {
        // Set vtable pointers
        this->vtable1 = &PTR_FUN_00d5db44; // derived from actual binary
        this->vtable2 = &PTR_LAB_00d5db34; // second vtable

        this->someFlag1 = 1;
        this->someFlag2 = 0;

        // Initialize all 20 message slots
        for (int i = 0; i < 20; i++) {
            MessageSlot& slot = slots[i];
            slot.field_00 = 0;
            slot.field_04 = 0;
            slot.field_08 = 0;
            slot.field_0C = 0;
            slot.id = -1;
            slot.field_14 = 0;
            slot.field_18 = 0;
            slot.field_1C = 0;
            slot.type = 4;
            slot.field_28 = 0;
            slot.field_2C = 0;
        }

        this->maxSlotCount = 20;
        this->pBankUpdateMoney = 0;
        // Clear unknown fields at 0x3F4 and 0x3F6
        *(uint16_t*)((uintptr_t)this + 0x3F4) = 0;
        *(uint16_t*)((uintptr_t)this + 0x3F6) = 0;

        // Zero-fill fields from 0x3D4 to 0x3EC (7 ints)
        uint32_t* ptr = (uint32_t*)((uintptr_t)this + 0x3D4);
        for (int j = 0; j < 7; j++) {
            ptr[j] = 0;
        }

        // Initialize global string variables
        FUN_00408240(&g_iMsgBankUpdateMoney, "iMsgBankUpdateMoney");
        FUN_00408240(&g_iMsgTransferStolenMoney, "iMsgTransferStolenMoney");
        FUN_00408240(&g_iMsgPlayerReset, "iMsgPlayerReset");
        FUN_00408240(&g_iMsgEndTruckHeist, "iMsgEndTruckHeist");
        FUN_00408240(&g_iMsgEndFakeBankHeist, "iMsgEndFakeBankHeist");

        // Register each message if its string pointer is non-zero
        // Note: puVar1 = this+0x04 (second vtable pointer) is used as object reference
        void* obj = (void*)((uintptr_t)this + 0x04);
        if (g_iMsgBankUpdateMoney != 0) {
            FUN_00408900(obj, &g_iMsgBankUpdateMoney, 0x8000);
        }
        if (g_iMsgTransferStolenMoney != 0) {
            FUN_00408900(obj, &g_iMsgTransferStolenMoney, 0x8000);
        }
        if (g_iMsgPlayerReset != 0) {
            FUN_00408900(obj, &g_iMsgPlayerReset, 0x8000);
        }
        if (g_iMsgEndTruckHeist != 0) {
            FUN_00408900(obj, &g_iMsgEndTruckHeist, 0x8000);
        }
        if (g_iMsgEndFakeBankHeist != 0) {
            FUN_00408900(obj, &g_iMsgEndFakeBankHeist, 0x8000);
        }
    }
};

// Global instance pointer, set in constructor
MessageManager* g_pMessageManager = nullptr; // actually DAT_0112a554

// Note: The actual vtable symbols are defined elsewhere in the binary.
// The member variables at offsets 0x3D4-0x3EC are of unknown purpose.