// FUNC_NAME: UIWidget::handleMessage
// Address: 0x00624c20
// Dispatches two types of UI messages:
//   type 1: sets a flag bit based on message data and iterates over an item list, calling a virtual method for each
//   type 2: triggers a helper function if a condition is met (flags bit 1 clear and state non‑zero)
// Returns 1 for known types, 0 for unknown.

class UIWidget {
public:
    // Virtual method at vtable+0x20; called with (param2, param3, itemData)
    virtual void onItemAction(int param2, int param3, int itemData) = 0;

    // Offsets from this:
    // +0x00: vtable pointer
    // +0x14: m_flags (int)
    // +0x18: m_state (int)
    int m_flags;   // offset 20
    int m_state;   // offset 24

    // Message data structure: param_6 is pointer to this
    struct Message {
        int   unknown;    // offset 0
        void* itemListPtr; // offset 4 – points to ItemList
    };

    struct ItemList {
        uint8_t flags;    // byte at offset 0
        uint8_t _pad1;    // alignment
        uint16_t count;   // offset 2
        int32_t* items;   // offset 4
    };

    int __thiscall handleMessage(int param2, int param3, int param4, int messageType, Message* msg) {
        if (messageType == 1) {
            ItemList* list = static_cast<ItemList*>(msg->itemListPtr);
            // Set/clear bit 2 (0x4) of m_flags based on first byte's bit 0
            if ((list->flags & 1) == 0) {
                m_flags &= ~0x4;
            } else {
                m_flags |= 0x4;
            }
            // Iterate over item list and call virtual action
            uint16_t count = list->count;
            if (count != 0) {
                for (uint16_t i = 0; i < count; i++) {
                    int item = list->items[i];
                    // Call virtual method at vtable slot 0x20
                    (reinterpret_cast<void(__thiscall*)(UIWidget*, int, int, int)>
                        (reinterpret_cast<void**>(this)[0x20 / 4]))(this, param2, param3, item);
                }
            }
            return 1;
        }
        else if (messageType == 2) {
            // Trigger helper if bit 1 is clear and state is non‑zero
            if (((m_flags & 0x2) == 0) && (m_state != 0)) {
                FUN_00624f30(reinterpret_cast<int*>(this)); // likely an internal update
            }
            return 1;
        }
        return 0; // unknown message type
    }
};