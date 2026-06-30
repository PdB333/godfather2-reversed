// FUNC_NAME: CombatPerception::handleEvent

void __thiscall CombatPerception::handleEvent(int thisPtr, int* eventData)
{
    // +0x000: eventData is a pointer to some event structure
    FUN_0046c6a0(eventData); // probably Event::initialize or base processing
    int eventType = *eventData; // first field of event is type

    // Compare against stored event type constants (likely members holding specific IDs)
    if (eventType == DAT_012069c4) // global? or this->mSomeEventType
    {
        // If either mFlagA or mFlagB is set
        if (*(char*)(thisPtr + 0x205) != '\0' || *(char*)(thisPtr + 0x206) != '\0')
        {
            int count = *(int*)(thisPtr + 0x3a4); // number of active entities/slots
            for (int i = 0; i < count; i++)
            {
                int entity = thunk_FUN_004ab300(); // get some entity pointer
                if (entity != 0)
                {
                    if (*(char*)(thisPtr + 0x205) != '\0' &&
                        (*(char*)(thisPtr + 0x1e5 + i) != '\0' || *(char*)(thisPtr + 0x1f5 + i) != '\0'))
                    {
                        FUN_0070e140(entity, i); // perform action A on entity i
                    }
                    if (*(char*)(thisPtr + 0x206) != '\0')
                    {
                        FUN_0070efb0(entity, i); // perform action B on entity i
                    }
                }
            }
        }
    }
    else if (eventType == *(int*)(thisPtr + 0x344) || eventType == *(int*)(thisPtr + 0x34c) ||
             eventType == *(int*)(thisPtr + 0x354) || eventType == *(int*)(thisPtr + 0x35c))
    {
        // Event types related to "attack" or "hit" directions?
        int count = *(int*)(thisPtr + 0x3a4);
        for (int i = 0; i < count; i++)
        {
            int entity = thunk_FUN_004ab300();
            if (entity != 0 && *(char*)(thisPtr + 0x205) != '\0')
            {
                // Clear flags for this entity
                *(char*)(thisPtr + 0x1f5 + i) = 0;
                *(char*)(thisPtr + 0x1e5 + i) = 0;
                // Set a random float in array at +0x2a0
                float randVal = (float)FUN_004aabd0(); // random 0-1
                *(float*)(thisPtr + 0x2a0 + i * 4) = randVal;
                FUN_004aa8c0(randVal); // do something with that random value
            }
        }
    }
    else if (eventType == *(int*)(thisPtr + 0x324) || eventType == *(int*)(thisPtr + 0x32c) ||
             eventType == *(int*)(thisPtr + 0x334) || eventType == *(int*)(thisPtr + 0x33c))
    {
        // Another set of event types (maybe reaction?)
        int count = *(int*)(thisPtr + 0x3a4);
        for (int i = 0; i < count; i++)
        {
            int entity = thunk_FUN_004ab300();
            if (entity != 0 && *(char*)(thisPtr + 0x205) != '\0')
            {
                *(char*)(thisPtr + 0x1f5 + i) = 0;
                *(char*)(thisPtr + 0x1e5 + i) = 0;
                *(int*)(thisPtr + 0x2a0 + i * 4) = 0;
                FUN_004aa8c0(0.0f);
            }
        }
    }
    else if (eventType == *(int*)(thisPtr + 0x2e4) || eventType == *(int*)(thisPtr + 0x2ec) ||
             eventType == *(int*)(thisPtr + 0x2f4) || eventType == *(int*)(thisPtr + 0x2fc))
    {
        // Event types for "dodge" or "evade" (positive direction)
        int count = *(int*)(thisPtr + 0x3a4);
        for (int i = 0; i < count; i++)
        {
            FUN_004ab360(); // get random direction?
            char isDead = FUN_004209a0(); // check if entity is dead/disabled
            if (isDead == '\0')
            {
                // Set flags
                *(char*)(thisPtr + 0x1e5 + i) = 1;
                *(char*)(thisPtr + 0x1f5 + i) = 0;
                int entity = thunk_FUN_004ab300();
                if (entity != 0)
                {
                    float randAngle = (float)FUN_004aaa30(); // random angle
                    *(float*)(thisPtr + 0x25c + i * 4) = randAngle; // store angle
                    float randFactor = (float)FUN_004aabd0();
                    // store a deviation based on speed and angle
                    *(float*)(thisPtr + 0x24c + i * 4) = (randFactor * *(float*)(thisPtr + 0x210) - randAngle);
                }
                // set a timer or momentum
                *(float*)(thisPtr + 0x218) = *(float*)(thisPtr + 0x208) + DAT_01205228;
            }
        }
    }
    else if (eventType == *(int*)(thisPtr + 0x304) || eventType == *(int*)(thisPtr + 0x30c) ||
             eventType == *(int*)(thisPtr + 0x314) || eventType == *(int*)(thisPtr + 0x31c))
    {
        // Event types for "block" or "counter" (negative direction)
        int count = *(int*)(thisPtr + 0x3a4);
        for (int i = 0; i < count; i++)
        {
            FUN_004ab360();
            char isDead = FUN_004209a0();
            if (isDead == '\0')
            {
                *(char*)(thisPtr + 0x1f5 + i) = 1;
                *(char*)(thisPtr + 0x1e5 + i) = 0;
                int entity = thunk_FUN_004ab300();
                if (entity != 0)
                {
                    float randAngle = (float)FUN_004aaa30();
                    *(float*)(thisPtr + 0x25c + i * 4) = randAngle;
                    float randFactor = (float)FUN_004aabd0();
                    // opposite orientation
                    *(float*)(thisPtr + 0x24c + i * 4) = (randAngle - randFactor * *(float*)(thisPtr + 0x214));
                }
                *(float*)(thisPtr + 0x218) = *(float*)(thisPtr + 0x20c) + DAT_01205228;
            }
        }
    }
    else if (eventType == *(int*)(thisPtr + 0x38c)) // 0x38c = 908
    {
        // Event to disable action B
        *(char*)(thisPtr + 0x206) = 0;
        FUN_0070e270(); // some cleanup
    }
    else if (eventType == *(int*)(thisPtr + 900)) // 0x384 = 900? Wait, 0x384 is 900, but code says 900, offset 0x39c is 924. Check: param_1+0x39c used later.
    {
        // Event to enable action B
        *(char*)(thisPtr + 0x206) = 1;
        int managerPtr = *(int*)(thisPtr + 0x39c); // this is a pointer to some manager or system
        if (managerPtr != 0)
        {
            int count = *(int*)(thisPtr + 0x3a4);
            for (int i = 0; i < count; i++)
            {
                int entity = thunk_FUN_004ab300();
                if (entity != 0)
                {
                    FUN_0045c400(thisPtr + 0x39c, entity, 0); // add entity to manager? Or register?
                }
            }
        }
    }
    else if (eventType == *(int*)(thisPtr + 0x374)) // 0x374 = 884
    {
        // Event to enable action A
        *(char*)(thisPtr + 0x205) = 1;
    }
    else if (eventType == *(int*)(thisPtr + 0x37c)) // 0x37c = 892
    {
        // Event to disable action A
        *(char*)(thisPtr + 0x205) = 0;
    }
    // else: ignore unknown event type
}