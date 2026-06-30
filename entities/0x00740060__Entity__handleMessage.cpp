// FUNC_NAME: Entity::handleMessage
// Address: 0x00740060
// Role: Process two specific message types (0x1b2d5c51 and 0x6862a74c) for an entity.
// This function is a message dispatch handler, likely part of the EARS event system.
// It sets up callbacks, timers, and state transitions based on the entity's state
// and the incoming message.

void __thiscall Entity::handleMessage(void* this, EventMessage* msg) {
    int* ptr;
    uint state;
    int basePtr;
    double tmpDouble;
    float tmpFloat;
    __int64 transform;
    float fVar1;

    // Call the virtual function on the message object to get the message type.
    // The message pointer itself is treated as an object with a vtable at offset 0.
    int msgType = (**(code**)(*msg))();

    if (msgType == 0x1b2d5c51) {
        // Obtain a pointer to the entity's sub-object (e.g., a component) at +0x70.
        // Subtract 0x48 to get the containing base object.
        if (*(int*)((char*)this + 0x70) == 0) {
            basePtr = 0;
        } else {
            basePtr = *(int*)((char*)this + 0x70) - 0x48; // +0x70 -> component pointer; base at -0x48
        }

        state = *(uint*)((char*)this + 0xC); // State/type field at +0xC

        if ((state == 4) || ((8 < state) && (state < 0xB))) { // state 4, 9, 10
            // Access global data (DAT_012233a0) for some manager.
            int* globalPtr = *(int**)(DAT_012233a0 + 4);
            if (globalPtr == 0) {
                ptr = 0;
            } else {
                ptr = (int*)((char*)globalPtr - 0x1f30); // Subtract offset to get containing object
            }

            int* listSlot = &msg->field_0x19; // Offset 0x19 in message (likely a linked list node)

            if (*listSlot != (int)ptr) {
                if (*listSlot != 0) {
                    removeFromList(listSlot); // FUN_004daf90 - unlink from any previous list
                }
                *listSlot = (int)ptr;
                if (ptr != 0) {
                    msg->field_0x1A = *(int*)((char*)ptr + 4); // Store previous next pointer
                    *(int**)((char*)ptr + 4) = listSlot; // Insert into linked list
                }
            }
        } else {
            // Check flags at +0x110 in the base object
            uint flags = *(uint*)((char*)basePtr + 0x110);
            if (((flags >> 4) & 1) != 0 || ((flags >> 1) & 1) != 0) {
                // Bit 4 (0x10) or bit 1 (0x2) set, handle a movement/transform-related action.
                __int64 posQuat;
                getTransform(&posQuat); // FUN_007266b0 - possibly get a position/quaternion from somewhere
                double* timePtr = (double*)getGameTime(); // FUN_00471610 returns a pointer to game time struct
                double gameTime = *timePtr;
                // Interpret the 64-bit value as two floats (low 32 bits and high 32 bits)
                float low = (float)(gameTime & 0xFFFFFFFF);
                float high = (float)((unsigned long long)gameTime >> 32);
                posQuat = __PAIR__(posQuat.high + high, posQuat.low + low);
                fVar1 = fVar1 + *(float*)((char*)timePtr + 8); // Probably time delta added to another float
                setTimer(&posQuat); // FUN_00755a10 - schedule a timer or set a transform
                msg->field_0x1F = 1;
                return;
            }

            if ((flags & 1) != 0) {
                // Bit 0 set: handle another specific action (e.g., using a different timer)
                if (*(int*)((char*)this + 0x70) != 0) {
                    setTimer(*(int*)((char*)this + 0x70) + 0xE8); // +0xE8 offset within component
                    msg->field_0x1F = 1;
                    return;
                }
                setTimer(0x130); // Default timer handle
                msg->field_0x1F = 1;
                return;
            }
        }
        msg->field_0x1F = 1;
    } else if (msgType == 0x6862a74c) {
        // Second message type: construct a callback/closure in the message.
        uint uVar2 = *(uint*)((char*)this + 0x5C); // Some value at +0x5C

        if (*(int*)((char*)this + 0x70) == 0) {
            basePtr = 0;
        } else {
            basePtr = *(int*)((char*)this + 0x70) - 0x48;
        }

        // Extract transform from base object at +0x130 (probably a quaternion + scalar)
        __int64 quat = *(__int64*)((char*)basePtr + 0x130);
        float w = *(float*)((char*)basePtr + 0x138);
        normalizeQuat(&quat); // FUN_0075cd50

        // Set message fields: the transform (quat and w) at offset 0x32 and 0x34
        msg->field_0x35 |= 1; // Set flag byte
        *(__int64*)((char*)msg + 0x32) = quat;
        *(float*)((char*)msg + 0x34) = w;

        // Set up callback function pointers in the message (offsets 0x24, 0x26, 0x28, etc.)
        // These are likely function addresses from code sections (LAB_..., FUN_...)
        msg->field_0x24 = reinterpret_cast<__int64>(&LAB_0073faa0, this); // pair of function ptr and this
        msg->field_0x26 = __PAIR__(uStack_18, fStack_1c); // unclear
        msg->field_0x28 = __PAIR__(&LAB_0073faf0, uStack_14);
        msg->field_0x1E = reinterpret_cast<__int64>(&FUN_007347e0, uVar2); // another callback
        msg->field_0x20 = (unsigned long long)uStack_18 << 32;
        msg->field_0x22 = __PAIR__(&LAB_0073b090, uStack_14);

        // Check flags again; if bit 1 set, add flag to message
        if (*(int*)((char*)this + 0x70) == 0) {
            basePtr = 0;
        } else {
            basePtr = *(int*)((char*)this + 0x70) - 0x48;
        }
        if ((*(uint*)((char*)basePtr + 0x110) >> 1) & 1) {
            msg->field_0x2A |= 0x200;
        }

        // Set some state based on value at +0x80 (movement mode?)
        int mode = *(int*)((char*)this + 0x80);
        if (mode == 0) {
            msg->field_0x3C = 2;
            return;
        }
        if ((mode == 1) || (mode == 4)) {
            msg->field_0x3C = 3;
            return;
        }
    } else {
        // Unknown message: call default handler
        defaultMessageHandler(msg); // FUN_0073e4d0
        return;
    }
    return;
}