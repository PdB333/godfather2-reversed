// FUNC_NAME: AptDisplayList::renderDisplayObject
// Function address: 0x005AE530
// Purpose: Processes a display list entry, rendering or updating a sprite/display object.
//          Handles sprite instantiation, color/transform copies, child iteration, and debug assertions.
// Source file: AptDisplayList.cpp

#include <cstdint>

// Forward declarations of called functions (implementations elsewhere)
static void beginRender();
static void pushTransformStack(void *stack);  // local_20
static uint32_t* getCurrentDisplayObject();   // returns pointer to display object flags
static uint32_t* getRendererContext();        // returns context with offsets 0x8, 0x18
static uint32_t renderSprite(void *renderer, uint32_t depth, uint32_t *spriteData,
                             void *transform, uint32_t flags, int bool1, int zOrder,
                             uint32_t **outEntry, int *outSuccess);
static bool isSpriteInstBase(uint32_t *item);
static uint32_t* getDisplayList();           // from FUN_005a3f20, returns display list stage
static void destroyDisplayObject(uint32_t *obj);
static uint32_t beginChildEnumeration();
static uint32_t* getFirstChild(uint32_t enumHandle);
static uint32_t* getNextChild(uint32_t enumHandle);
static void renderChild(uint32_t *obj, int zero, uint32_t childData, uint32_t param, int one1, int one2);
static void endRender(uint32_t *globalDisplayList);

// Global data
extern uint32_t *g_displayList;           // DAT_0119a9cc
extern void (*g_free)(void *ptr);         // DAT_0119caf4, function pointer for memory deallocation

void AptDisplayList::renderDisplayObject(uint32_t **outObject, int mode, uint32_t depth, uint32_t *extraObject)
{
    int success = 0;
    beginRender();

    // Local transform stack
    struct TransformStack {
        uint64_t data[2];  // placeholder for matrix/color data
    };
    TransformStack stack;
    TransformStack *stackPtr = &stack;
    uint64_t stackInit[2] = {0}; // local_14 and local_c
    uint32_t *transformStack;   // local_20, actually used as pointer to a buffer

    pushTransformStack(&transformStack);

    if (success != 0) {
        // success possibly set by beginRender or pushTransformStack (misleading decompiler)
        uint32_t *displayObject = getCurrentDisplayObject();
        uint32_t typeAndFlags = *displayObject;

        uint32_t baseType = typeAndFlags & 0x7FFF;
        bool isSprite = (typeAndFlags & 0x8000) != 0;

        if (!isSprite || (baseType != 0xD && baseType != 0x12)) { // 0xD=13, 0x12=18 (sprite types)
            mode = 0;
        } else {
            uint32_t *context = getRendererContext();
            mode = *(int *)(context + 0x18); // +0x18: mode/state from context
        }

        void *transformStackCopy = stackPtr; // local_18, originally &local_14
        uint32_t colorTransformFlags = displayObject[0x15]; // +0x54: color transform flags
        uint32_t *colorTransform = displayObject + 0x0E;    // +0x38: color transform data
        uint32_t *transformData = displayObject + 4;        // +0x10: transform matrix

        uint32_t *context2 = getRendererContext();
        uint32_t *spriteData = *(uint32_t **)(context2 + 8); // +0x08: current sprite/item data
        *outObject = nullptr;
        uint32_t *renderer = getRendererContext();
        success = 0;

        if (spriteData == nullptr) {
            // Assertion: "pCharacter || pItem"
            AptAssert(false, "pCharacter || pItem", "..\\source\\Apt\\AptDisplayList.cpp", 0x1A2);
        }

        // Call to add/render the sprite into the display list
        renderSprite(renderer + 0x1C, depth, spriteData,
                     transformStackCopy, colorTransformFlags, 1, -1,
                     outObject, &success);

        uint32_t *outEntry = *outObject;
        if (outEntry != nullptr) {
            if (outEntry[0x14] == 0) { // +0x50: flag indicating data is not populated
                // Copy transform matrix (16 bytes? actually 4 uint32s)
                if (transformData != nullptr) {
                    outEntry[4] = transformData[0];
                    outEntry[5] = transformData[1];
                    outEntry[6] = transformData[2];
                    outEntry[7] = transformData[3];
                    outEntry[8] = transformData[4];
                    outEntry[9] = transformData[5];
                    outEntry[10] = transformData[6];
                    outEntry[11] = transformData[7]; // actually 8 uint32? decompiler shows up to +10
                }
                // Copy color transform (6 uint32)
                if (colorTransform != nullptr) {
                    outEntry[0x0E] = colorTransform[0];
                    outEntry[0x0F] = colorTransform[1];
                    outEntry[0x10] = colorTransform[2];
                    outEntry[0x11] = colorTransform[3];
                    outEntry[0x12] = colorTransform[4];
                    outEntry[0x13] = colorTransform[5];
                }
            }

            if (mode != 0) {
                if (!isSpriteInstBase(outEntry)) {
                    // Assertion: "pItem->isSpriteInstBase()"
                    AptAssert(false, "pItem->isSpriteInstBase()", "..\\source\\Apt\\AptDisplayList.cpp", 0x1B3);
                }
                uint32_t *context3 = getRendererContext();
                *(int *)(context3 + 0x18) = mode; // +0x18: restore/update mode
            }

            if (success != 0) {
                uint32_t *displayList = getDisplayList();
                if (*(int *)(*(uint32_t **)(displayList + 8)) == 5) { // check display list state
                    int i = 0;
                    uint32_t **listBase = (uint32_t **)((uint32_t)g_displayList + 0x1D14); // global array of display entries
                    for (; i < 0x200; i++) {
                        if (listBase[i] == outEntry) {
                            break;
                        }
                    }
                    if (i == 0x200) {
                        // Not found in allocated list, destroy it
                        destroyDisplayObject(outEntry);
                    }
                }
            }

            // Check extraObject and type for child rendering
            uint32_t entryType = *outEntry & 0x7FFF;
            bool entryIsSprite = (*outEntry & 0x8000) != 0;
            if (entryIsSprite && (entryType == 0xD || entryType == 0x12) &&
                extraObject != nullptr && (*extraObject & 0x8000) != 0) {

                uint32_t childEnum = beginChildEnumeration();
                uint32_t *child = getFirstChild(childEnum);
                while (child != nullptr) {
                    // Render child with specific parameters
                    renderChild(outEntry, 0, *(uint32_t *)(*(uint32_t *)(child) + 0xC), child[1], 1, 1);
                    child = getNextChild(childEnum);
                }
            }
        }

        endRender(g_displayList);
    }

    if (stackPtr != &stack && stackPtr != nullptr) {
        g_free(stackPtr);
    }
}