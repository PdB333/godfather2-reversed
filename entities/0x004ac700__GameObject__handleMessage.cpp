// FUNC_NAME: GameObject::handleMessage
// Function at 0x004AC700 - handles specific message types (7,8,9) for a game object,
// dispatching events to sub-objects or setting properties.
// The this pointer is at param_1, member at +0x48 is a pointer to a sub-object (behavior/script).
// param_5 = message type, param_6 = data buffer (structure with pointers/values).

int __thiscall GameObject::handleMessage(int param0, int param1, int param2, int msgType, void* msgData)
{
    // msgType 7: set some color/scale? Extracts 4 bytes and a float from msgData+4
    if (msgType == 7)
    {
        // msgData+4 points to a structure with fields at offsets 0, 1, 5, 6 (bytes) and offset 8 (int)
        uint32_t* src = *(uint32_t**)((char*)msgData + 4);
        // Virtual call at vtable+0x2c (assuming this is a method)
        (this->vtable[0x2c])(*src, *(uint8_t*)((char*)src + 1), *(uint8_t*)((char*)src + 5),
                             *(uint8_t*)((char*)src + 6), *(src + 2), 1.0f);
        // Typically sets RGBA and alpha=1.0f, or transform component.
    }
    // msgType 8: call virtual function on sub-object if it exists
    else if (msgType == 8)
    {
        void* subObj = *(void**)((char*)this + 0x48);  // +0x48: pointer to sub-object
        if (subObj != 0)
        {
            // subObj is actually an offset-embedded member; compute base by subtracting 0x48
            int base = (int)subObj - 0x48;
            // Call vtable function at +0x164 on the base object
            int (*func)() = *(int(**)(void))(*(int*)base + 0x164);
            func();
        }
        else
        {
            // Fallback call from null? Original code might have used a default vtable.
            // Note: decompiler shows iRam00000000, likely an error; we assume a null check.
            // In practice this path may not be reached.
            // Calling through null would crash, so we probably should not reach here.
        }
        return 1;
    }
    // msgType 9: store data into a sub-object's field if available
    else if (msgType == 9)
    {
        void* subObj = *(void**)((char*)this + 0x48);
        int base;
        if (subObj == 0)
            base = 0;
        else
            base = (int)subObj - 0x48;
        
        // If the sub-object has a non-zero pointer at +0x218, store msgData+4 at that pointer+0x130
        if (base != 0 && *(int*)(base + 0x218) != 0)
        {
            *(int*)(*(int*)(base + 0x218) + 0x130) = *(int*)((char*)msgData + 4);
        }
        return 1;
    }
    else
    {
        // Delegate to base handler for other message types
        return FUN_004abb80(param0, param1, param2, msgType, msgData);
    }
    // If msgType 7 handled, falls through to return 1 (the BL register value)
    return 1;
}