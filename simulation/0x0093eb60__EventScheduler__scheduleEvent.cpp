// FUNC_NAME: EventScheduler::scheduleEvent

void __thiscall EventScheduler::scheduleEvent(int thisPtr, const char** ppText)
{
    struct EventNode {
        EventNode* next;           // +0x00
        int field_4;               // +0x04
        int type;                  // +0x08  (set to 2)
        int fireTime;              // +0x0C
        short field_10;            // +0x10
        short field_12;            // +0x12
        short delay;               // +0x14
        int field_18;              // +0x18
        int field_1C;              // +0x1C
        char* text;                // +0x20
    };

    // Max active events allowed (20)
    if (*(uint*)(thisPtr + 0x50) >= 20) {
        return;
    }

    // Check if free list head is empty and pool state requires initialization
    if (*(int*)(thisPtr + 0x44) == 0 &&
        (*(int*)(thisPtr + 0x40) == 0 || (*(byte*)(thisPtr + 0x34) & 1) == 0))
    {
        FUN_004de190();  // Probably pool initialization
    }

    EventNode* node = *(EventNode**)(thisPtr + 0x44);
    if (node == nullptr) {
        return;
    }

    // Remove node from free list
    *(EventNode**)(thisPtr + 0x44) = node->next;
    *(int*)(thisPtr + 0x1C) -= 1;   // Free count
    *(int*)(thisPtr + 0x20) += 1;   // Active count

    // Initialize node fields
    node->next = nullptr;
    node->field_4 = 0;
    node->type = 2;
    node->fireTime = DAT_01205224 + 12000;  // Base time + 12 seconds
    node->field_10 = 1;
    node->field_12 = 0;
    node->delay = 15000;                     // 15 seconds in game time units
    node->field_18 = 0;
    node->field_1C = 0;

    // Copy the text to a newly allocated buffer
    const char* src = (ppText != nullptr) ? *ppText : nullptr;
    if (src == nullptr) {
        src = &DAT_0120546e;  // Default string resource
    }
    size_t len = strlen(src) + 1;
    char* dst = (char*)FUN_009c8e80(len);   // Allocate memory
    if (dst != nullptr) {
        memcpy(dst, src, len);
    }
    node->text = dst;

    // Insert the event into the active queue
    FUN_0093e4c0((int)node);
}