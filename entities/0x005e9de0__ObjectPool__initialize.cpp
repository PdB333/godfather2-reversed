// FUNC_NAME: ObjectPool::initialize
// Function address: 0x005e9de0
// Role: Constructor for an object pool containing 5 slots, each with a dynamic buffer (initial capacity 16).

// Note: The exact class and field names are inferred based on usage.
// Structure layout assumed:
//   class PoolSlot { // size 0x30 (48 bytes)
//       uint32_t m_field0;    // +0x00
//       uint32_t m_field1;    // +0x04
//       uint32_t* m_buffer;   // +0x08 (index 7)
//       uint32_t m_count;     // +0x0C (index 8)
//       uint32_t m_capacity;  // +0x10 (index 9)
//       // ... remaining fields ...
//   };
// The outer class contains 5 PoolSlot objects plus some header fields.

// __thiscall
void ObjectPool::initialize()
{
    // Header fields at +0x00 to +0x10 (5 dwords) set to 0
    this->m_headerField0 = 0;  // +0x00
    this->m_headerField1 = 0;  // +0x04
    this->m_headerField2 = 0;  // +0x08
    this->m_headerField3 = 0;  // +0x0C
    this->m_headerField4 = 0;  // +0x10

    PoolSlot* slot = &this->m_slots[0];  // +0x14 (start of first PoolSlot)

    uint32_t* ptrToCapacity = &this->m_slots[0].m_capacity;  // Actually points to offset +0x24 (index 9)
    uint32_t* ptrToBuffer = &slot->m_buffer;               // also deduced

    int slotIndex = 4;  // Loop will run 5 times

    do
    {
        // Zero all fields of the current PoolSlot
        slot->m_field0 = 0;
        slot->m_field1 = 0;
        slot->m_buffer = NULL;
        slot->m_count = 0;
        slot->m_capacity = 0;
        // Additional fields (offsets +0x14, +0x18, etc.) also set to 0
        slot->m_field5 = 0;
        slot->m_field6 = 0;
        slot->m_field7 = 0;
        slot->m_field8 = 0;
        slot->m_field9 = 0;
        slot->m_field11 = 0;  // note: m_field10 at +0x28 is not explicitly zeroed here

        FUN_005ef9a0();  // Probably additional per-slot initialization (e.g., resetting state)

        // If current capacity < 16, allocate a new buffer of 0x40 bytes (16 uint32_t)
        if (slot->m_capacity < 16)
        {
            uint32_t* newBuffer = (uint32_t*)FUN_009c8e80(0x40);  // allocate(64 bytes)
            if (slot->m_buffer != NULL)
            {
                uint32_t count = slot->m_count;
                if (count != 0)
                {
                    uint32_t i = 0;
                    uint32_t* dst = newBuffer;
                    do
                    {
                        if (dst != NULL)
                        {
                            *dst = slot->m_buffer[i];
                        }
                        i++;
                        dst++;
                    } while (i < count);
                }
                FUN_009c8f10(slot->m_buffer);  // free old buffer
            }
            slot->m_buffer = newBuffer;
            slot->m_capacity = 16;
        }

        slot++;
        ptrToCapacity = &slot->m_capacity;
        slotIndex--;
    } while (slotIndex >= 0);
}