// FUNC_NAME: AptCharacter::setProperty
// Address: 0x005b6cf0
// Sets a named property on an AptCharacter object.
// Handles properties: _x, _y, _rotation, _alpha, _xscale, _yscale, _visible, this, _width, _height
// Also processes ActionScript-style property assignments (via action stack) when character is ready.

#include <cstring>  // for __stricmp

// Forward declarations of internal engine functions
extern int getCurrentCharacter();                 // FUN_0059c3b0
extern int isCharacterReady();                   // FUN_0059c950
extern int getActionFromStack();                 // FUN_005b4780
extern int getActionData();                       // FUN_0059c810
extern int readStackKey();                        // FUN_005b1c30
extern int readStackValue();                      // FUN_005a8fe0
extern int allocateCharacterObject(int size);     // FUN_0059cae0
extern void initializeCharacterObject(int obj);   // FUN_0059c690
extern int loadCharacterFont();                   // FUN_005a7d30
extern int loadCharacterImage();                  // FUN_005a7df0
extern int setCharacterText(int obj);             // FUN_005abf00
extern void getCharacterString(char* buf, int len); // FUN_005a90a0
extern int loadCharacterFromString(int obj);       // FUN_005b8920
extern int getCharacterChild();                   // FUN_005a1a60
extern int loadCharacterAsset(int somePtr, int zero, int assetId, int one1, int one2); // FUN_005aea60
extern void startActionState();                   // FUN_005a0950
extern void pushActionKeyStack(int buf);          // FUN_005a92b0
extern int allocateActionList(int size, int zero); // FUN_005abfb0
extern void commitAction();                       // FUN_005a0b30
extern void registerCharacterAsset(int somePtr, int zero, int assetId, int someGlobal, int one1, int one2); // FUN_005ad5b0
extern void getTransform();                       // FUN_005a9040
extern void recalcScale(int value);               // FUN_005b6030
extern void setDirtyFlag();                       // FUN_005b5d20
extern float getFontWidth();                      // FUN_005b5a40
extern void sinCos(float angle, double* sout, double* cout); // FUN_00b99fcb / FUN_00b99e20 (approximate)

// Global constants from .data section (float constants)
extern float DEG_TO_RAD;                         // DAT_00e2e780
extern float PI;                                  // DAT_00e445c8
extern float MIN_SCALE;                           // DAT_00e44560
extern float ONE_MINUS;                           // DAT_00e44564
extern float DISPLAY_SCALE;                       // DAT_00e2b050
extern int gAllocatorPtr;                         // DAT_0119caf0
extern int gFreeFunc;                             // DAT_0119cb3c

int AptCharacter::setProperty(int thisPtr, const char* propertyName, uint* flags, float value)
{
    // Validate context (debug assertion)
    if (!validateContext()) {
        // Assertion: "pContext->isCIH()"
        // ... debug break code (omitted for clarity)
        return 0;
    }

    int charObj = getCurrentCharacter();
    int charReady = isCharacterReady();

    if (charReady == 0) {
        // Process property via action stack
        propertyName = skipWhitespace(propertyName);  // inline loop: while(*pcVar8) pcVar8++
        int actionItem = getActionFromStack();
        if (actionItem == 0) {
            goto DIRECT_PROPERTY_SET;
        }
        int charObj = getCurrentCharacter();
        int actionData = getActionData();

        switch (*(int*)(actionItem + 4)) {
            case 1: { // Create character
                startActionState();
                pushActionKeyStack(someBuffer);
                int key1 = readStackKey();   // Check multiple keys for alignment type
                if (!key1) key1 = readStackKey();
                if (!key1) key1 = readStackKey();
                if (!key1) key1 = readStackKey();
                if (!key1) key1 = readStackKey();
                if (!key1) key1 = readStackKey();
                if (key1) {
                    *(int*)(actionData + 0x40) = 3; // Top alignment
                } else {
                    if (readStackKey()) {
                        *(int*)(actionData + 0x40) = 1; // Left alignment
                    } else if (readStackKey()) {
                        *(int*)(actionData + 0x40) = 2; // Right alignment
                    } else {
                        *(int*)(actionData + 0x40) = 0; // Center alignment
                    }
                }
                goto ACTION_FINISH;
            }
            case 2: { // Set text color
                int color = readStackValue();
                *(int*)(actionData + 0x34) = color;
                break;
            }
            case 3: { // Set text background color
                int color = readStackValue();
                *(uint*)(actionData + 0x38) = color | 0xFF000000;
                break;
            }
            case 4: { // Set border color
                int color = readStackValue();
                *(int*)(actionData + 0x30) = color;
                break;
            }
            case 5: { // Set border background color
                int color = readStackValue();
                *(uint*)(actionData + 0x3C) = color | 0xFF000000;
                break;
            }
            case 6:
            case 8:
            case 16: // These cases handled together, fall to switch end
                goto CASE_6_8_16_COMMON;
            case 10: { // Set width
                int w = readStackValue();
                *(int*)(*(int*)(actionData + 8) + 0x2C) = w;
                break;
            }
            case 11: { // Set max characters
                int newMax = readStackValue();
                if (newMax == *(int*)(actionData + 0x2C)) goto DIRECT_PROPERTY_SET;
                int oldMax = *(int*)(actionData + 0x28) - 1;
                *(int*)(actionData + 0x2C) = newMax;
                if (oldMax < newMax) {
                    *(int*)(actionData + 0x2C) = oldMax;
                }
                if (*(int*)(actionData + 0x2C) < 0) {
                    *(int*)(actionData + 0x2C) = 0;
                }
                break;
            }
            case 12: { // Create new character from resource
                // Release old character (if exists)
                int* oldChar = *(int**)(actionData + 0x18);
                if (oldChar) {
                    (*(void(**)(int*))(gVTable + (*oldChar & 0x7FFF) * 4))(oldChar);
                }
                int newChar = allocateCharacterObject(0x24);
                *(int*)(actionData + 0x18) = newChar;
                initializeCharacterObject(newChar);
                // Try to load font or image
                if (!loadCharacterFont() && !loadCharacterImage()) {
                    setCharacterText(newChar);
                } else {
                    char buf[256];
                    getCharacterString(buf, 256);
                    loadCharacterFromString(newChar);
                }
                int parent = getCurrentCharacter();
                while (parent && !getCharacterChild()) {
                    parent = *(int*)(parent + 0x54);
                }
                // Check if character has assetId
                if (*(int*)(actionData + 0x1C) != 0) {
                    int assetResult = loadCharacterAsset(parent, 0, *(int*)(*(int*)(actionData + 0x1C) + 0xC), 1, 1);
                    if ((assetResult & 0x8000) != 0) {
                        startActionState();
                        pushActionKeyStack(someBuffer);
                        int* textObj = *(int**)(actionData + 0x20);
                        if (textObj == nullptr) {
                            // Allocate new action list
                            int newList = allocateActionList(0x24, 0);
                            *(int*)(actionData + 0x20) = newList;
                            initializeCharacterObject(newList);
                        } else {
                            // Check if text already matches (string comparison)
                            // ... (omitted for clarity)
                            if (stringsDiffer) {
                                // Release old and allocate new
                                (*(void(**)(int*))(gVTable + (*textObj & 0x7FFF) * 4))(textObj);
                                int newList = allocateActionList(0x24, 0);
                                *(int*)(actionData + 0x20) = newList;
                                initializeCharacterObject(newList);
                            }
                        }
                    }
                }
                commitAction();
                getCurrentCharacter(); // Re-fetch
                recalcCharacter(parent);
CASE_6_8_16_COMMON:
                return 1;
            }
            case 13: { // Set text shadow color
                int color = readStackValue();
                *(uint*)(actionData + 0x24) = color | 0xFF000000;
                break;
            }
            case 17: { // Create text from resource (similar to case 12)
                startActionState();
                pushActionKeyStack(someBuffer);
                int* oldText = *(int**)(actionData + 0x1C);
                if (oldText) {
                    (*(void(**)(int*))(gVTable + (*oldText & 0x7FFF) * 4))(oldText);
                }
                int newText = allocateCharacterObject(0x24);
                *(int*)(actionData + 0x1C) = newText;
                initializeCharacterObject(newText);
                setCharacterText(newText);
                int assetResult = loadCharacterAsset(*(int*)(thisPtr + 0x54), 0, *(int*)(*(int*)(actionData + 0x1C) + 0xC), 1, 1);
                if ((assetResult & 0x8000) == 0) {
                    registerCharacterAsset(*(int*)(thisPtr + 0x54), 0, *(int*)(*(int*)(actionData + 0x1C) + 0xC), gGlobalAssetManager, 1, 1);
                }
            }
ACTION_FINISH:
                commitAction();
                break;
            case 18: { // Set height
                int h = readStackValue();
                *(int*)(*(int*)(actionData + 8) + 0x30) = h;
                break;
            }
            case 19: { // Set x position
                getTransform();
                *(float*)(actionData + 0x50) = value;  // Won't be used?
                break;
            }
            case 20: { // Set y position
                getTransform();
                *(float*)(actionData + 0x4C) = value;
                break;
            }
            default: {
                // Assertion: "0" with source line
                return 0;
            }
        }
        // Free any allocated string data if present
        int* strData = *(int**)(actionData + 0x14);
        if (strData && strData != &gEmptyString) {
            gFreeFunc(strData);
            *(int*)(actionData + 0x14) = 0;
        }
        return 1;
    }

    // Direct property setting on character object
DIRECT_PROPERTY_SET:
    int charData = getCurrentCharacter();
    uint flagCheck = *flags & 0x7FFF;
    if (((*flags & 0x8000) != 0) && (flagCheck != 0xD && flagCheck != 0x12)) {
        getCurrentCharacter();
        int charReadyCheck = isCharacterReady();
        if (charReadyCheck == 0) {
            return 0;
        }
    }
    int charState = getCurrentCharacter();

    if (__stricmp(propertyName, "_x") == 0) {
        if ((*flags & 0x8000) != 0) {
            getTransform();
            setDirtyFlag();
            *(char*)(charState + 100) = 1;  // Dirty flag
            **(float**)(charState + 0x50) = value;  // Set matrix[0][0] (scaleX?)
            *(float*)(charState + 0x48) = value;    // Set x position (translation)
            return 1;
        }
    } else if (__stricmp(propertyName, "_y") == 0) {
        if ((*flags & 0x8000) != 0) {
            getTransform();
            setDirtyFlag();
            *(char*)(charState + 100) = 1;
            *(float*)(*(int*)(charState + 0x50) + 4) = value; // matrix[0][1] (shear?)
            *(float*)(charState + 0x4C) = value;   // Set y position
            return 1;
        }
    } else if (__stricmp(propertyName, "_rotation") == 0) {
        getTransform();
        setDirtyFlag();
        *(char*)(charState + 100) = 1;
        *(float*)(*(int*)(charState + 0x50) + 0x18) = value; // Set rotation (in matrix[3]? Actually offset 0x18 within matrix)
        int matrixPtr = *(int*)(charState + 0x50);
        float scaleX = *(float*)(matrixPtr + 8) * DEG_TO_RAD;  // +8 = maybe scaleX?
        float scaleY = *(float*)(matrixPtr + 0xC) * DEG_TO_RAD; // +0xC = scaleY?
        if (*(float*)(matrixPtr + 0x18) != 0.0f) {
            float angle = *(float*)(matrixPtr + 0x18) * PI;
            double sinRes, cosRes;
            sinCos(angle, &sinRes, &cosRes);
            // Build 2D rotation matrix from scale and angle
            *(float*)(charState + 0x38) = (float)cosRes * scaleX;  // m00
            *(float*)(charState + 0x3C) = (float)sinRes * scaleX;  // m01
            *(float*)(charState + 0x44) = (float)cosRes * scaleY;  // m10
            *(float*)(charState + 0x40) = ONE_MINUS - (float)sinRes * scaleY; // m11
            return 1;
        }
        // Fall through to set identity if no rotation
    } else if (__stricmp(propertyName, "_alpha") == 0) {
        getTransform();
        setDirtyFlag();
        *(char*)(charState + 100) = 1;
        *(float*)(*(int*)(charState + 0x50) + 0x1C) = value;  // Set alpha in matrix (color transform?)
        *(float*)(charState + 0x10) = value * DEG_TO_RAD;      // Alternatively store as scaled
        return 1;
    } else if (__stricmp(propertyName, "_xscale") == 0) {
        getTransform();
        recalcScale(value, 1);  // Set scale only in X direction
        return 1;
    } else if (__stricmp(propertyName, "_yscale") == 0) {
        getTransform();
        setDirtyFlag();
        *(char*)(charState + 100) = 1;
        *(float*)(*(int*)(charState + 0x50) + 0xC) = value;  // Set scaleY in matrix
        // Note: fall through to update rotation matrix below
    } else if (__stricmp(propertyName, "_visible") == 0) {
        getTransform();
        setDirtyFlag();
        *(char*)(charState + 100) = 0;  // Clear dirty? Actually setting visibility
        *(float*)(*(int*)(charState + 0x50) + 0x2C) = value; // Set visibility (1.0 = visible)
        return 1;
    } else if (__stricmp(propertyName, "this") == 0) {
        // "this" reference - assertion
        // (debug info omitted)
        return 1;
    } else if (__stricmp(propertyName, "_width") == 0) {
        getTransform();
        float fontWidth = getFontWidth(charState);
        float widthScale = value / (fontWidth - (float)someOther);  // Some calculation
        if (widthScale < MIN_SCALE) widthScale = MIN_SCALE;
        recalcScale(*(float*)(charState + 0x38) * widthScale * DISPLAY_SCALE, 1);
        return 1;
    } else if (__stricmp(propertyName, "_height") == 0) {
        getTransform();
        float fontHeight = getFontWidth(charState);
        float heightScale = value / (fontHeight - (float)someOther);
        if (heightScale < MIN_SCALE) heightScale = MIN_SCALE;
        float scaledHeight = *(float*)(charState + 0x44) * heightScale * DISPLAY_SCALE;
        setDirtyFlag();
        *(char*)(charState + 100) = 1;
        *(float*)(*(int*)(charState + 0x50) + 0xC) = scaledHeight; // Set scaleY
        // Note: fall through to update rotation matrix
    } else {
        return 0; // Unknown property
    }

    // Common code for _rotation, _yscale, _height (if no early return)
    int matrixPtr = *(int*)(charState + 0x50);
    float scaleX = *(float*)(matrixPtr + 8) * DEG_TO_RAD;
    float scaleY = *(float*)(matrixPtr + 0xC) * DEG_TO_RAD;
    if (*(float*)(matrixPtr + 0x18) != 0.0f) {
        float angle = *(float*)(matrixPtr + 0x18) * PI;
        double sinRes, cosRes;
        sinCos(angle, &sinRes, &cosRes);
        *(float*)(charState + 0x38) = (float)cosRes * scaleX;
        *(float*)(charState + 0x3C) = (float)sinRes * scaleX;
        *(float*)(charState + 0x44) = (float)cosRes * scaleY;
        *(float*)(charState + 0x40) = ONE_MINUS - (float)sinRes * scaleY;
        return 1;
    }
    // No rotation: set identity matrix
    *(float*)(charState + 0x38) = scaleX;
    *(int*)(charState + 0x3C) = 0;
    *(float*)(charState + 0x44) = scaleY;
    *(int*)(charState + 0x40) = 0;
    return 1;
}