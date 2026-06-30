// FUNC_NAME: SlotManager::processSlot

// This function handles slot activation in a fixed-size object manager.
// Given a context with current index, bitmask, and object pointer,
// it either initializes a new slot (if bit not set) or processes all
// active slots up to the current index using one of two handler sets
// based on the object's type (low byte at +0x04 determines vtable offset).

struct SlotInfo {
    int* slotMemory;       // +0x00  // pointer to slot memory for initialization
    int field_4;           // +0x04
    int objectPtr;         // +0x08
    int* bitmaskArray;     // +0x0C
    int processParam;      // +0x10
    int currentIndex;      // +0x14
    int field_18;          // +0x18
    int defaultObject;     // +0x1C  // constant from DAT_00e2b1a4
};

extern int g_defaultObject;  // DAT_00e2b1a4

int __thiscall SlotManager::processSlot(SlotInfo* context)
{
    int index = context->currentIndex;
    int* bitmask = context->bitmaskArray;

    // Check if bit for this index is set
    if ((bitmask[index >> 5] & (1 << (index & 0x1f))) == 0)
    {
        // Bit not set: initialize the slot memory
        SlotInfo* slot = (SlotInfo*)context->slotMemory;
        slot->slotMemory = 0;
        slot->field_4 = 0;
        slot->objectPtr = 0;
        slot->bitmaskArray = (int*)g_defaultObject;  // uses global default
        slot->field_18 = 0;
        slot->currentIndex = 0;
        slot->processParam = 0;
        slot->defaultObject = g_defaultObject;
        return 1;
    }

    int objPtr = context->objectPtr;
    int typeByte = *(int*)(objPtr + 4) & 0xFF;
    int* vtable;
    if (typeByte < 10)
        vtable = *(int**)(objPtr + 0x24);
    else
        vtable = *(int**)(objPtr + 0x2C);

    if (*vtable == 0)
    {
        // First vtable entry null – branch A
        if ((short)vtable[3] != 0)
        {
            FUN_00581080(context->processParam);
            for (int i = 0; i < index; i++)
            {
                if ((bitmask[i >> 5] & (1 << (i & 0x1f))) != 0)
                    FUN_00581370();
            }
            FUN_00581220(context->slotMemory);
            return 1;
        }
    }
    else
    {
        // First vtable entry non-null – branch B
        int objPtr2;
        if (typeByte < 10)
            objPtr2 = *(int*)(objPtr + 0x24);
        else
            objPtr2 = *(int*)(objPtr + 0x2C);

        if (*(short*)(objPtr2 + 0x24) != 0)
        {
            FUN_0057f8a0(context->processParam);
            for (int i = 0; i < index; i++)
            {
                if ((bitmask[i >> 5] & (1 << (i & 0x1f))) != 0)
                    FUN_005800a0();
            }
            FUN_0057f9d0(context->slotMemory);
            return 1;
        }
    }
    return 0;
}