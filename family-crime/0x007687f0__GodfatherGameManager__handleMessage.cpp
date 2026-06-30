// FUNC_NAME: GodfatherGameManager::handleMessage

undefined4 __thiscall GodfatherGameManager::handleMessage(int *this, undefined4 param_2, float floatParam, undefined4 param_4, int messageId, undefined4 param_6)
{
    if (messageId == 0x23) {
        // Message 0x23: Load/play sound effect
        floatParam = g_loadSoundEffectFloat;  // DAT_00d5780c
        int result = PreloadResource(&floatParam);  // FUN_00715f80
        *(byte *)(this + 0x1c) = 0;
        if (result != 0) {
            byte loadedByte = (**(code **)(*this + 0x2c))(result, 1, 1, 0, floatParam, 1.0f);
            *(byte *)(this + 0x1c) = loadedByte;
        }
        if ((char)this[0x1c] == '\0') {
            int vtable = *this;
            undefined4 soundHandle = CreateSoundEffect(1, 0, 0, 1.0f, 1.0f);  // FUN_007347e0
            (**(code **)(vtable + 0x2c))(soundHandle);
        }
        int ready = IsSoundReady();  // FUN_00800a90
        if (ready != 0) {
            PlaySound();  // FUN_00701f40
        }
    }
    else {
        if (messageId != 0x24) {
            undefined4 defaultResult = DefaultMessageHandler(param_2, floatParam, param_4, messageId, param_6);  // FUN_0073e610
            return defaultResult;
        }
        // Message 0x24: Move object
        if ((*(int *)(this[0x17] + 0x24cc) != 0) && 
            (int objPtr = *(int *)(this[0x17] + 0x24cc) - 0x48; objPtr != 0)) {
            MoveObject(objPtr, floatParam * g_moveScaleFactor, 0);  // FUN_00470230, DAT_00d636b8
            return 1;
        }
    }
    return 1;
}