// FUNC_NAME: AptCharacter::render
// Function address: 0x005b5480
// Role: Renders an Apt character (text, shape, or button) with matrix push/pop and clipping.

#include <cstdint>

// Forward declarations of helper functions (from AptCharacter.cpp)
void pushMatrix(uint32_t* matrixStack); // FUN_005b4450
void popMatrix(); // FUN_005b4350
void drawShape(uint32_t* matrixStack, uint32_t param3, uint32_t param4); // FUN_005b4430
void drawButton(uint32_t param2, uint32_t param3, uint32_t param4); // FUN_005b36b0
void drawText(uint32_t param3, uint32_t param4); // FUN_005b47e0
bool isTextCharacter(); // FUN_0059c950
bool isShapeCharacter(); // FUN_005a83e0
uint32_t getTextInstance(); // FUN_0059c810
uint32_t getSpriteInstance(); // FUN_005a19c0
uint32_t getType(uint32_t spriteObject); // FUN_005bb150
uint32_t getRenderState(); // FUN_005a3a40
uint32_t getMember(uint32_t* thisPtr, uint32_t zero, const char* name, uint32_t one, uint32_t one2); // FUN_005aea60
void getTextBuffer(char** outBuffer); // FUN_005aa640
void textPreprocess(); // FUN_005a0af0
void textPostprocess(); // FUN_005a0b30
void drawCharacter(uint32_t* param1, uint32_t param2, uint32_t param3, uint32_t param4); // FUN_005a8340
void assertFailed(const char* condition, const char* file, int line, int level, const char* msg); // FUN_0059bf00
void releaseRefCount(); // FUN_0059cb90
void addRefCount(); // FUN_0059cc70

// Global variables (from decompiled references)
extern float DAT_00e2cd54; // current time?
extern char PTR_DAT_00f17650; // some flag
extern float DAT_0119d0bc;
extern float _DAT_0119d0cc; // note: overlapping symbol
extern uint32_t DAT_0103ae68; // sentinel value
extern uint32_t DAT_0112912c; // assertion message
extern uint32_t DAT_0112912d;
extern uint32_t DAT_01129129;
extern uint32_t DAT_0112912a;
extern uint32_t DAT_0112912b;
extern void (*DAT_0119cb40)(uint32_t textInst, uint32_t param3, uint32_t param4); // draw text function pointer
extern void (*DAT_0119cb7c)(uint32_t renderState, uint32_t* outFlags); // get flags
extern void (*DAT_0119cb74)(uint32_t renderState, uint32_t target, uint32_t something); // set something
extern void (*DAT_0119caf4)(uint32_t* ptr); // free

void AptCharacter::render(uint32_t param2, uint32_t param3, uint32_t param4)
{
    uint32_t* thisPtr = this;
    float* pfVar1;
    uint32_t uVar2;
    uint32_t* puVar3;
    char cVar4;
    uint32_t uVar5;
    int iVar6;
    int iVar7;
    uint32_t uVar8;
    uint32_t* local_40;
    char* local_3c;
    char* local_38;
    uint32_t local_34;
    uint32_t local_30;
    uint32_t* local_2c;
    uint32_t local_20;
    uint32_t local_1c;
    uint32_t* local_18;
    uint32_t local_14[5];

    puVar3 = thisPtr;
    addRefCount(thisPtr + 4); // increment reference count on something

    // Check if rendering is allowed based on timing and global flags
    if (((puVar3[0x14] == 0) || // +0x50: some pointer
         (pfVar1 = (float*)(puVar3[0x14] + 0x2c), DAT_00e2cd54 < *pfVar1 || DAT_00e2cd54 == *pfVar1)) &&
        (((char)PTR_DAT_00f17650 != '\0' || ((DAT_0119d0bc != 0.0f || (0.0f < _DAT_0119d0cc))))))
    {
        uVar5 = *puVar3 & 0x7fff; // lower 15 bits: character type ID
        if (((*puVar3 & 0x8000) == 0) || ((uVar5 != 0xd && (uVar5 != 0x12)))) // not a shape/button type
        {
            // Text character handling
            cVar4 = isTextCharacter();
            if (cVar4 == '\0')
            {
                cVar4 = isShapeCharacter();
                if (cVar4 == '\0')
                {
                    // Assertion: character is neither text nor shape
                    local_3c = "0";
                    local_38 = "..\\source\\Apt\\AptCharacter.cpp";
                    local_34 = 0x42a;
                    local_30 = 2;
                    local_2c = &DAT_0112912d;
                    assertFailed();
                    releaseRefCount();
                    return;
                }
                // Shape character (but not text)
                pushMatrix(puVar3 + 0xe); // +0x38: matrix stack?
                drawCharacter(puVar3, param3, param4); // draw shape
                drawText(param3, param4); // draw text overlay?
                popMatrix();
                releaseRefCount();
                return;
            }
            // Text character
            iVar6 = getTextInstance();
            // FUN_005b49f0 might be something like setTextColor? Not sure, skip for now
            // Actually the call is: FUN_005b49f0(puVar3[0x15]); // +0x54
            // We'll name it setTextProperties
            setTextProperties(puVar3[0x15]);
            if ((*(uint32_t**)(iVar6 + 0x14) != nullptr) &&
                (*(uint32_t**)(iVar6 + 0x14) != &DAT_0103ae68))
            {
                if (*(int*)(iVar6 + 0x10) == 0)
                {
                    local_3c = "pTextInst->pCurValue != 0";
                    local_38 = "..\\source\\Apt\\AptCharacter.cpp";
                    local_34 = 0x3d5;
                    local_30 = 2;
                    local_2c = &DAT_0112912c;
                    assertFailed();
                }
                pushMatrix(puVar3 + 0xe);
                (*DAT_0119cb40)(*(uint32_t*)(iVar6 + 0x14), param3, param4); // draw text
                popMatrix();
                releaseRefCount();
                return;
            }
        }
        else
        {
            // Shape/button character (type 0xd or 0x12)
            iVar6 = getSpriteInstance();
            iVar7 = 0;
            // param1 is being used as a byte flag later; here it's manipulated
            // The original code does: param_1 = (uint *)((uint)param_1 & 0xffffff00);
            // That's a bitwise AND on the this pointer? That seems odd. Probably a bug in decompilation.
            // Actually it's likely: param1 = (uint32_t*)((uint32_t)param1 & 0xffffff00); but param1 is this, so it's clearing low byte? Unlikely.
            // Let's assume it's a local variable, not the this pointer. The decompiler reused param_1.
            // We'll use a separate variable for the byte flag.
            uint32_t byteFlag = (uint32_t)thisPtr & 0xff; // low byte of this? That doesn't make sense.
            // Actually looking at the code: param_1 = (uint *)((uint)param_1 & 0xffffff00); then later (char)param_1 is used.
            // This is likely a bug; the original source probably had a local variable like "uint32_t flags = ..."
            // We'll ignore this and use a local variable for the byte flag.
            // Let's re-analyze: The code does:
            // param_1 = (uint *)((uint)param_1 & 0xffffff00);
            // ... later: if ((char)param_1 == '\0') ...
            // This is weird. Possibly the decompiler mixed up param_1 with a local variable.
            // We'll assume there's a local variable "byteFlag" that is set from somewhere.
            // For now, we'll keep it as is but with a local variable.
            uint32_t byteFlag = 0; // placeholder

            if ((*(uint32_t*)(iVar6 + 0x14) & 0x6000000) == 0) // check if type not yet determined
            {
                if (*(int*)(iVar6 + 0xc) == 0)
                {
                    iVar7 = 0;
                }
                else
                {
                    iVar7 = getType(*(int*)(iVar6 + 0xc));
                }
                byteFlag = 1; // set flag to indicate type determined
                if (iVar7 == 0)
                {
                    *(uint32_t*)(iVar6 + 0x14) = *(uint32_t*)(iVar6 + 0x14) & 0xfdffffff | 0x4000000; // set bit 26 (button?)
                }
                else
                {
                    *(uint32_t*)(iVar6 + 0x14) = *(uint32_t*)(iVar6 + 0x14) & 0xfbffffff | 0x2000000; // set bit 25 (shape?)
                }
            }
            uVar2 = param2;
            if ((*(uint32_t*)(iVar6 + 0x14) & 0x6000000) != 0x2000000) // not shape type
            {
                // Button type
                pushMatrix(puVar3 + 0xe);
                drawButton(uVar2, param3, param4);
                popMatrix();
                releaseRefCount();
                return;
            }
            // Shape type
            if (*(int*)(**(int**)(iVar6 + 0x1c) + 0x60) == 0) // check some condition
            {
                releaseRefCount();
                return;
            }
            cVar4 = isShapeCharacter();
            if (cVar4 == '\0')
            {
                local_3c = "pRectObject->isShapeInst()";
                local_38 = "..\\source\\Apt\\AptCharacter.cpp";
                local_34 = 0x375;
                local_30 = 2;
                local_2c = &DAT_01129129;
                assertFailed();
            }
            if (*(int*)(iVar6 + 0xc) == 0)
            {
                local_3c = "pSpriteInst->pObject";
                local_38 = "..\\source\\Apt\\AptCharacter.cpp";
                local_34 = 0x376;
                local_30 = 2;
                local_2c = &DAT_0112912a;
                assertFailed();
            }
            if (byteFlag == 0)
            {
                iVar7 = getType(*(uint32_t*)(iVar6 + 0xc));
            }
            if (iVar7 == 0)
            {
                local_3c = "pType";
                local_38 = "..\\source\\Apt\\AptCharacter.cpp";
                local_34 = 0x37b;
                local_30 = 2;
                local_2c = &DAT_0112912b;
                assertFailed();
            }
            iVar7 = getRenderState();
            uVar2 = *(uint32_t*)(iVar7 + 0xc);
            if (byteFlag != 0)
            {
                uint32_t* flagsPtr = nullptr;
                (*DAT_0119cb7c)(uVar2, &flagsPtr);
                // Update flags in sprite instance
                *(uint32_t*)(iVar6 + 0x14) =
                    (*(uint32_t*)(iVar6 + 0x14) & ~0x38000000) | ((uint32_t)flagsPtr << 0x1b & 0x38000000);
            }
            local_18 = local_14;
            uVar8 = 0;
            local_40 = nullptr;
            // param_1 reused as local pointer? We'll use a separate variable.
            uint32_t* localParam1 = nullptr;
            local_20 = 0;
            local_1c = 0;
            local_14[0] = 0;
            local_14[1] = 0;
            local_14[2] = 0;
            local_14[3] = 0;

            if ((*(uint32_t*)(iVar6 + 0x14) & 0x8000000) != 0) // target flag
            {
                if (*(int*)(iVar6 + 0x20) == 0)
                {
                    local_40 = (uint32_t*)getMember(puVar3, 0, "_target", 1, 1);
                    // FUN_0059c690 might be something like getMemberDone
                    getMemberDone();
                    iVar7 = getRenderState();
                    uVar8 = *(uint32_t*)(iVar7 + 0xc);
                }
                else
                {
                    *(uint32_t*)(iVar6 + 0x14) &= 0xf7ffffff; // clear target flag
                }
            }
            if ((*(uint32_t*)(iVar6 + 0x14) & 0x10000000) != 0) // text flag
            {
                if (*(int*)(iVar6 + 0x20) == 0)
                {
                    getTextBuffer(&local_3c);
                    textPreprocess();
                    textPostprocess();
                    localParam1 = local_18;
                }
                else
                {
                    *(uint32_t*)(iVar6 + 0x14) &= 0xefffffff; // clear text flag
                }
            }
            if ((*(uint32_t*)(iVar6 + 0x14) & 0x20000000) == 0) // no matrix push needed
            {
                iVar6 = drawCharacter(localParam1, iVar6 + 0x20, param3, param4);
                (*DAT_0119cb74)(uVar2, uVar8, *(uint32_t*)(*(int*)(iVar6 + 8) + 0x18));
            }
            else
            {
                pushMatrix(puVar3 + 0xe);
                drawShape(); // FUN_005b4430
                iVar6 = drawCharacter(localParam1, iVar6 + 0x20, param3, param4);
                (*DAT_0119cb74)(uVar2, uVar8, *(uint32_t*)(*(int*)(iVar6 + 8) + 0x18));
                popMatrix();
            }
            if (local_40 != nullptr)
            {
                // Release the member object
                (*(void (**)(uint32_t*))(&DAT_0103aee0 + (*local_40 & 0x7fff) * 4))(local_40);
            }
            if ((local_18 != local_14) && (local_18 != nullptr))
            {
                (*DAT_0119caf4)(local_18);
            }
        }
    }
    releaseRefCount();
    return;
}