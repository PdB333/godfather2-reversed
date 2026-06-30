// FUNC_NAME: EffectManager::registerEffect
void EffectManager::registerEffect(int eventType, int eventSubType, void* targetObj, int flags1, void* sourceObj, uint optionalEntity, int flags2, void* extraData)
{
    // Manager structure offsets:
    // +0x04: m_triggerListHead (pointer)
    // +0x0C: m_triggerListTail (pointer) - sentinel node? 
    // +0x10: m_freeTriggerHead (pointer)

    EffectTrigger* current = reinterpret_cast<EffectTrigger*>(this->m_triggerListHead);
    EffectTrigger* tail = reinterpret_cast<EffectTrigger*>(this->m_triggerListTail);

    // Search for existing trigger with same key
    while (current != tail)
    {
        if (current->eventType == eventType && 
            current->eventSubType == eventSubType && 
            current->targetObj == targetObj)
        {
            goto found_or_create;
        }
        current = current->m_next; // +0x2C
    }

    // Not found, allocate from free list
    EffectTrigger* freeNode = reinterpret_cast<EffectTrigger*>(this->m_freeTriggerHead);
    if (freeNode == nullptr)
    {
        return;
    }
    this->m_freeTriggerHead = reinterpret_cast<void*>(freeNode->m_next);

    // Insert into the main list
    int prevTailPrev = tail->m_prev; // Actually tail is sentinel? The insertion code is odd.
    freeNode->m_next = tail;
    freeNode->m_prev = prevTailPrev;
    tail->m_prev = reinterpret_cast<int>(freeNode);
    *(reinterpret_cast<int*>(prevTailPrev + 0x2C)) = reinterpret_cast<int>(freeNode); // Update previous tail's next

    // Initialize node fields
    freeNode->eventType = eventType;
    freeNode->m_flags = 0; // +0x34
    freeNode->sourceObj = sourceObj;
    freeNode->eventSubType = eventSubType;
    freeNode->targetObj = targetObj;
    freeNode->owner = owner;    // in_EAX - context object
    freeNode->m_flags = *(uint*)(owner + 0x14) & 2; // bit 1 of owner's flags

found_or_create:
    // current is the matched node (or newly inserted)
    EffectTrigger* node = current;
    byte sourceFlags = *(byte*)(sourceObj + 0x44) >> 6;
    bool sourceBit = (sourceFlags & 1) != 0;

    if (optionalEntity == 0)
    {
        if (!sourceBit)
        {
            return;
        }
    }
    else
    {
        // Check optional entity state
        float entityFloat = *(float*)(optionalEntity + 0xA0);
        int entityInt = *(int*)(optionalEntity + 0x84);
        if (entityFloat != FLOAT_ZERO || entityInt != 0)
        {
            // Allocate and initialize an effect instance
            EffectInstance* effect = allocateEffectInstance(); // FUN_0051f9f0
            if (effect != nullptr)
            {
                initializeEffectInstance(effect, sourceObj, extraData); // FUN_00524b40

                // Insert effect into node's effect list
                EffectInstance* listHead = reinterpret_cast<EffectInstance*>(node->m_effectListHead); // +0x28
                EffectInstance* listTail = reinterpret_cast<EffectInstance*>(*(int*)(listHead + 0x44)); // ??? Actually offset 0x44 is next pointer? The code is confusing: it uses iVar3 = node->m_effectListHead, iVar4 = *(int*)(iVar3 + 0x44), then inserts effect between iVar3 and iVar4. So m_effectListHead is a sentinel with +0x40 (prev) and +0x44 (next). 
                effect->m_prev = listHead;
                effect->m_next = listTail;
                listHead->m_next = effect;
                listTail->m_prev = effect;
            }
            hasEntityCondition = true;
        }
        else
        {
            hasEntityCondition = false;
        }
    }

    // Second allocation path (if source bit set or no entity condition)
    if (sourceBit || !hasEntityCondition)
    {
        AnotherEffectObject* another = allocateAnotherEffect(); // FUN_0051f960
        if (another != nullptr)
        {
            another->field_0x451 = static_cast<byte>(node->eventSubType); // or something? param_2 was modified earlier: param_2._0_1_ = sourceBit, that might be used.
            setupAnotherEffect(sourceObj, flags1, hasEntityCondition ? optionalEntity : 0, extraData); // FUN_005232a0

            // Insert into node's another list at +0x1C
            AnotherEffectObject* listHead2 = reinterpret_cast<AnotherEffectObject*>(node->m_anotherListHead); // +0x1C
            AnotherEffectObject* listTail2 = reinterpret_cast<AnotherEffectObject*>(*(int*)(listHead2 + 0x44));
            another->m_prev = listHead2;
            another->m_next = listTail2;
            listHead2->m_next = another;
            listTail2->m_prev = another;
        }
    }
}