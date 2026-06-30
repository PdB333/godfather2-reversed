// FUNC_NAME: CharacterController::updateState
struct CharacterController {
    // vtable at +0x00
    // +0x04: pointer to state manager
    int* stateMgr; // offset 0x4
    // +0x08: flags (byte)
    unsigned char flags; // +0x08
    // +0x09-0x11: padding
    // +0x118: float/int
    int someValue1; // +0x118 (param_1[0x46])
    // +0x11C: float/int
    int someValue2; // +0x11C (param_1[0x47])
    // +0x120: color (0xFFFFFF)
    int effectColor; // +0x120 (param_1[0x48])
    // +0x124: some int
    int effectColor2; // +0x124 (param_1[0x49])
    // +0x128: byte
    char effectByte; // +0x128 (param_1[0x4a])
    // +0x129: byte
    char unknownByte; // +0x129
    // +0x12C: pointer to internal data (16 bytes)
    int* internalData; // +0x12C (param_1[0x4b])
};

// External functions (likely engine-wide)
extern int g_maxStateIndex; // DAT_01205460
extern void* g_stateHandlerTable; // DAT_01163f68 (array of function pointers)
extern void (*g_scaleFunc)(float*); // DAT_0120545c
extern float g_someFactor; // DAT_00e2dd14

// Called functions
void spawnEffect1(CharacterController* obj, int param2, int stateIndex);
void spawnEffect2(int param2, int context);
void writeStateByteToContext(int context, char byteVal, int destOffset);
bool isKeyPressed(int keyIndex);   // FUN_00b93170
bool isMouseButton(int btnIndex);  // FUN_00b930b0
int getMouseMove(int axis);        // FUN_00b93230

void __thiscall CharacterController::updateState(CharacterController* this, int param2, int param3, int context) {
    char stateChar;
    unsigned int bitmask;
    long long stateResult; // from getStateAtIndex
    float floatVal;
    unsigned char byteVar1, byteVar2, byteVar3, byteVar4;
    int tempInt;
    
    // Local flags for bitmask
    unsigned char maskBytes[4] = {0,0,0,0}; // uStack_18..uStack_15
    
    // Virtual call to pre-update
    (*(void (__thiscall*)(CharacterController*, int))(this->vtable + 0x20))(this, context);
    
    // Query state manager for index 0x18 (24)
    stateResult = (*(long long (__thiscall*)(int*, int))(this->stateMgr[0] + 0xC))(0x18);
    floatVal = (float)(stateResult >> 32);
    int stateIndex = (unsigned char)((char)(stateResult >> 8) - 1);
    
    if (stateIndex < g_maxStateIndex) {
        ((void (__thiscall*)(CharacterController*, int, int, unsigned int))g_stateHandlerTable[stateIndex])(this, param2, context, (unsigned int)(stateResult >> 16));
    }
    
    // First loop: state indices 25 to 28 (0x19 to 0x1C)
    int loopIndex = 25;
    do {
        stateChar = (*(char (__thiscall*)(int*, int))(this->stateMgr[0] + 0xC))(loopIndex);
        if (stateChar == 1) {
            goto handle_state1;
        }
        else if (stateChar == 2) {
            spawnEffect2(param2, context);
        }
        else if (stateChar == 3) {
handle_state1:
            if ((this->flags & 1) != 0) {
                spawnEffect1(this, param2, loopIndex);
            }
        }
        loopIndex++;
    } while (loopIndex < 29);
    
    // Second loop: state indices 0 to 23
    loopIndex = 0;
    do {
        stateChar = (*(char (__thiscall*)(int*, int))(this->stateMgr[0] + 0xC))(loopIndex);
        if (stateChar == 1) {
            goto handle_state2;
        }
        else if (stateChar == 2) {
            spawnEffect2(param2, context);
        }
        else if (stateChar == 3) {
handle_state2:
            if ((this->flags & 1) != 0) {
                spawnEffect1(this, param2, loopIndex);
            }
        }
        // For first 3 states (indices 0,1,2), check keyboard input
        if ((loopIndex < 3) && (stateChar = isKeyPressed(loopIndex), stateChar != 0)) {
            bitmask = (unsigned int)(*(int*)maskBytes) | (1 << (loopIndex & 0x1F));
            *(int*)maskBytes = bitmask;
        }
        loopIndex++;
    } while (loopIndex < 24);
    
    // If internalData exists, write the bitmask to offset 0xC
    if (this->internalData != 0) {
        *(unsigned int*)(this->internalData + 3) = *(int*)maskBytes; // +0xC
    }
    
    // Check flag bit 2 (0x04)
    if ((this->flags >> 2) & 1) {
        // Reset mask
        maskBytes[0] = 0;
        maskBytes[1] = 0;
        maskBytes[2] = 1;
        maskBytes[3] = 0xFF; // Actually uStack_17 and uStack_16 are set, but combined later
        
        // Set default color to yellow
        this->effectColor = 0xFFFF00;
        this->effectColor2 = 0;
        
        // Check mouse buttons (0,1,2)
        int btnIdx = 0;
        do {
            if (isMouseButton(btnIdx)) {
                maskBytes[1] = (unsigned char)btnIdx;
                maskBytes[0] = 0;
                maskBytes[2] = 1;
                maskBytes[3] = 0xFF;
                this->effectColor = (unsigned int)((0xFF << 16) | (maskBytes[1] << 8) | 1);
                this->effectColor2 = 0;
                goto after_mouse_check;
            }
            btnIdx++;
        } while (btnIdx < 3);
        
        // If no mouse button, check mouse movement
        int moveVal = getMouseMove(2);
        if (moveVal < 1) {
            if (moveVal < 0) {
                // Negative movement => impact left? (string "Impact_LT_Std" + offset)
                maskBytes[0] = 0;
                maskBytes[1] = 0;
                maskBytes[2] = 1;
                maskBytes[3] = 4; // Actually uStack_17 = 4, uStack_16 = 0xFF
                this->effectColor = (int)("Impact_LT_Std" + 0xD); // pointer to string? Or literal?
                this->effectColor2 = 0;
            }
        }
        else {
            // Positive movement => impact? (color 0xFF0301)
            maskBytes[0] = 0;
            maskBytes[1] = 0;
            maskBytes[2] = 1;
            maskBytes[3] = 3;
            this->effectColor = 0xFF0301;
            this->effectColor2 = 0;
        }
    }
    
after_mouse_check:
    // Write state bytes to context
    writeStateByteToContext(context, this->unknownByte, 0);    // context+0
    writeStateByteToContext(context, this->effectColor2, 4);  // context+4? Actually (char)param_1[0x4a] at +4
    writeStateByteToContext(context, this->unknownByte, 8);   // context+8
    writeStateByteToContext(context, this->effectColor2, 12); // context+12
    
    // Final state query for index 29 (0x1D)
    stateResult = (*(long long (__thiscall*)(int*, int))(this->stateMgr[0] + 0xC))(0x1D);
    stateIndex = (unsigned char)((char)(stateResult >> 8) - 1);
    // Extract bytes for mask? Actually uStack_18..uStack_15 are assigned but never used later
    maskBytes[0] = (unsigned char)(stateResult >> 32);
    maskBytes[1] = (unsigned char)(stateResult >> 40);
    maskBytes[2] = (unsigned char)(stateResult >> 48);
    maskBytes[3] = (unsigned char)(stateResult >> 56);
    
    if (stateIndex < g_maxStateIndex) {
        ((void (__thiscall*)(CharacterController*, int, int, unsigned int))g_stateHandlerTable[stateIndex])(this, param2, context, (unsigned int)(stateResult >> 16));
    }
    
    // If internalData exists and scaleFunc is set, compute effects
    if ((this->internalData != 0) && (g_scaleFunc != 0)) {
        float fScale = 0.0f;
        // Reset mask? Actually maskBytes are zeroed here
        maskBytes[0] = 0;
        maskBytes[1] = 0;
        maskBytes[2] = 0;
        maskBytes[3] = 0;
        g_scaleFunc(&fScale);
        
        *(float*)(this->internalData + 0) = (float)this->someValue2 * fScale;
        *(float*)(this->internalData + 1) = (float)this->someValue2 * (float)*(int*)maskBytes; // mask as float? odd
        int moveVal2 = getMouseMove(2);
        *(float*)(this->internalData + 2) = (float)moveVal2 * (float)this->someValue1 * (float)this->someValue2 * g_someFactor;
    }
    
    return;
}