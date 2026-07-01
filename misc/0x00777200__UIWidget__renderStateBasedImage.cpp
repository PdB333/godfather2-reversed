// FUNC_NAME: UIWidget::renderStateBasedImage
// Address: 0x00777200
// Role: Renders an image/icon based on current state (e.g., health/ammo/money icon variant)

void __fastcall UIWidget::renderStateBasedImage(int* this)
{
    int stateValue;          // iVar1 - value from offset 0x5C
    char isActive;           // cVar2
    int stateIndex;          // iVar5
    DWORD renderFlags;       // uVar6
    DWORD textureID;         // uVar3
    int localState;          // local_4
    int localUnk;            // local_8

    stateValue = this[0x17]; // +0x5C - likely something like "current state index" or "value to render"
    localState = 0;
    localUnk = 0;

    // Get pointer to "active" object from offset 0x1C (if non-null, subtract 0x48 to get base)
    int* activeObj;
    if (this[0x1C] == 0) {
        activeObj = 0;
    } else {
        activeObj = (int*)(this[0x1C] - 0x48); // +0x70, subtract 0x48 to get container object
    }

    // Call virtual method at offset 0x1F8 on activeObj's vtable to get some state info
    (*(code**)(*activeObj + 0x1F8))(stateValue, &localState); // likely fills localState and localUnk

    // Determine sub-state based on some condition checks
    char result1 = FUN_008754e0(&localState); // check something
    if (result1 == '\0') {
        stateIndex = 0;
    } else {
        char result2 = FUN_008754b0(&localState);
        stateIndex = 2 - (uint)(result2 != '\0');
    }

    // Choose default render flags global
    renderFlags = _DAT_00d5780c;

    // Override if specific state conditions met (localState 4,5,6 and bit10 of offset 0xAC)
    if ((((uint)this[0x2B] >> 10 & 1) != 0) &&
        ((localState == 4 || localState == 5 || localState == 6))) {
        renderFlags = DAT_00d681ac; // alternate render flags
    }

    // Select texture ID from array based on stateIndex and localState
    textureID = FUN_00875af0(stateValue, *(int*)(&DAT_00d681b0 + stateIndex * 4 + localState * 0xC));

    // Set render flags (global variable)
    FUN_00460300(renderFlags);

    // Call virtual render method (vtable offset 0x2C) to draw the texture
    // Parameters: textureID, unknown (1,1,0,0, scaleX=1.0, scaleY=1.0)
    (*(code**)(*this + 0x2C))(textureID, 1, 1, 0, 0, 0x3F800000, 0x3F800000);
}