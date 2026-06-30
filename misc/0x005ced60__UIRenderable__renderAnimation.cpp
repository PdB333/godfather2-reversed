// FUNC_NAME: UIRenderable::renderAnimation

#include <cstdint>

// Global constants used for scaling and bounds
extern float DAT_01222214;  // Scale factor X
extern float DAT_01222218;  // Scale factor Y
extern float DAT_00e2b1a4;  // Some base offset or zero
extern float DAT_012056b4;  // Screen width or max X
extern float DAT_00e2cd54;  // Some adjustment constant
extern int32_t DAT_00e2fc48; // Some value (maybe a handle)
extern int32_t DAT_01205668; // Some global pointer +0xc is used

// External functions (likely rendering primitives)
extern void FUN_005ce5a0(RectState* state, int param7);
extern void FUN_005d8320(int32_t* subObj, int param5, float* uv1, float* uv2, float x, float y, int param6);
extern void FUN_005d0d20();
extern void FUN_005cdd30();
extern void FUN_005cd5f0(uint32_t textureHandle);
extern void FUN_00670550(uint32_t context, uint32_t color, int depth, float* rectX, float* rectY, float something, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4, float in_xmm0, uint32_t textureHandle);
extern bool FUN_005ce990(RectState* state);
extern void FUN_005db6c0();
extern void FUN_005d8680(int left, int top, int right, int bottom);
extern void FUN_005cd5a0();
extern void FUN_005cdba0(float* param);
extern void FUN_005db700();

// Global state flags
extern uint8_t DAT_01205655;  // Some boolean, maybe "enableRender"

// Structure for param_2: rectangle with state and position
struct RectState {
    int32_t* ptr;       // +0x00 : pointer (maybe to render target)
    int32_t state;      // +0x04 : state machine phase
    int32_t x;          // +0x08 : left
    int32_t y;          // +0x0C : top
    int32_t width;      // +0x10 : width
    int32_t height;     // +0x14 : height
};

// Assumed class for this (param_1)
class UIRenderable {
public:
    int32_t field_0x2c;   // +0x2c : some flag/count
    int32_t animCounter;  // +0x34 : animation frame counter (max 13)
    // ... other fields, and an embedded sub-object at offset 0x08
    // The sub-object is used as a pointer in FUN_005d8320
    int32_t subObject[2]; // +0x08 : placeholder for actual sub-struct
};

// Returns 0 on completion, 1 on continue
int __thiscall UIRenderable::renderAnimation(RectState* rectState, float uv1[4], float uv2[4],
                                             int param5, int param6, int param7, int param8, int param9, int param10)
{
    int32_t* basePtr = rectState->ptr;
    
    // Force state to 8 if dimensions are too small and not yet started
    if ((3 < rectState->state) && (rectState->width == 0 || rectState->height == 0)) {
        rectState->state = 8;
    }
    
    switch (rectState->state) {
    case 1:
    case 8:
        // Idle/ready – fall through to main render block
        break;
        
    case 2:
    case 3:
        // Transition to init state 4
        rectState->state = 4;
        // Fall through
    case 4:
    case 5:
    case 6: {
        // Initialization pass: scale coordinates and issue first draw call
        if (param10 == 0) {
            float scaledX = (float)rectState->x * DAT_01222214;
            float scaledY = (float)rectState->y * DAT_01222218;
            float scaledW = ((float)(rectState->width + rectState->x) - DAT_00e2b1a4) * DAT_01222214;
            float scaledH = ((float)(rectState->height + rectState->y) - DAT_00e2b1a4) * DAT_01222218;
            
            // Copy UV arrays
            float localUV1[4] = { uv1[0], uv1[1], uv1[2], uv1[3] };
            float localUV2[4] = { uv2[0], uv2[1], uv2[2], uv2[3] };
            
            // Set state to busy (6)
            rectState->state = 6;
            
            // Prepare some context value (probably a handle)
            int32_t contextHandle = DAT_00e2fc48;
            
            // Call helper to set up texture or state
            FUN_005ce5a0(rectState, param7);
            
            // Draw the textured quad: subObject at offset 8
            FUN_005d8320(this->subObject, param5, localUV1, localUV2, scaledX, scaledH, param6);
        }
        
        // After first draw, synchronize something (maybe flush)
        FUN_005d0d20();
        // fall through to default
    }
    default:
        return 1; // Indicate more passes needed?
    }
    
    // Main rendering path (states 1,8 reach here)
    // Check if rendering is allowed
    if (((*(int32_t*)((int)this + 0x2c) == 0) && (this->animCounter < 0xd)) || (DAT_01205655 != 1)) {
        // Get render context from global
        int32_t renderContext = *(int32_t*)(DAT_01205668 + 0xc);
        float localUV[1]; // re-used later
        
        // Handle some special case based on basePtr+0x2c
        if (*(int32_t*)(basePtr + 0x2c) == 0) {
            DAT_0119dac0 = 0; // global flag reset
        } else {
            FUN_005cdd30();   // Unknown helper
        }
        
        // Prepare rectangle for FUN_00670550
        float rectX = *(float*)(basePtr + 0x10); // width stored as float?
        float rectY = *(float*)(basePtr + 0x0c); // height as float?
        float screenWidth = DAT_012056b4;
        
        // Bind texture
        uint32_t textureHandle = *(uint32_t*)(basePtr + 0x0c);
        FUN_005cd5f0(textureHandle);
        
        // Draw the textured quad with many parameters (likely color, depth, etc.)
        FUN_00670550(renderContext,
                     *(uint32_t*)(basePtr + 4) & 0xf0ffffff,
                     (int)*(float*)(basePtr + 8),
                     &screenWidth,
                     &rectX,
                     0,
                     *(uint32_t*)(basePtr + 0x1c),
                     *(uint32_t*)(basePtr + 0x14),
                     *(uint32_t*)(basePtr + 0x18),
                     *(uint32_t*)(basePtr + 0x20),
                     in_XMM0_Da,
                     textureHandle);
        
        // Update rectangle dimensions from drawn result
        rectState->width  = (int)screenWidth;
        rectState->height = (int)rectX;
        
        // Apply offset based on flags at basePtr+0x28
        uint32_t flags = *(uint32_t*)(basePtr + 0x28);
        int adjustX, adjustY;
        if ((flags & 0x180006) == 0) {
            // Use bit fields to compute adjustment
            uint32_t bits = flags >> 0xd;
            float sum = (float)(bits & 1) + (float)(bits & 2) + (float)(bits & 4);
            int adj = (int)(sum * DAT_00e2cd54 + sum);
            adjustX = (int)screenWidth + adj;
            adjustY = (int)rectX + adj;
        } else {
            adjustX = (int)screenWidth + 3;
            adjustY = (int)rectX + 3;
        }
        rectState->width  = adjustX;
        rectState->height = adjustY;
        
        // Animation frame processing (only if animCounter < 13)
        if (this->animCounter < 0xd) {
            bool canContinue = FUN_005ce990(rectState);
            if (!canContinue) {
                return 0;
            }
            
            // Link rectState to the pointer chain (if ptr is non-null)
            if (rectState->ptr != nullptr) {
                *(int32_t**)(rectState->ptr + 0x30) = (int32_t*)rectState;
            }
            
            // Prepare second drawing pass
            uint32_t x = rectState->x;
            float yf = (float)rectState->y;
            float basePtrFloat = (float)((int)this + 8); // address of subObject as float?
            
            FUN_005db6c0(); // probably begin rendering pass
            
            // Clamp draw region to screen bounds
            int drawLeft   = (int)basePtrFloat; // hmm, but basePtrFloat is a pointer address, used as float? This looks suspicious. Possibly local_60 is actually a float but reinterpreted.
            // Let's re-evaluate: local_60 = (float)(param_1 + 8); That's converting an int to float. This might be a hack to pass a pointer as float? Unlikely. More likely local_60 is used as a float later, but the cast to int is wrong. Since we cannot be sure, we'll treat it as float of subObj address? Actually later it's used as fVar6 = local_60; then fVar6 is used as float in multiplication? This is unclear. Given the decompiler's choices, it's probably a float representing some coordinate or offset. We'll keep the intent: local_60 is probably a coordinate value, not a pointer. But the code uses (param_1+8) as an int and casts to float. That could be a mistake; perhaps param_1+8 is a float value already? More likely, the decompiler misinterpreted the register allocation. Given the context, param_1+8 is likely a member that holds a float offset. So we rename local_60 to "offsetX" or something.
            // However, for reconstruction, we trust the decompiler's typing. We'll call it "someFloat".
            float someFloat = (float)((int)this + 8); // This is odd, but keep as is.
            
            int drawRight  = rectState->width;
            int drawBottom = rectState->height;
            
            if ((int)DAT_012056b4 < rectState->x + rectState->width) {
                drawRight = rectState->width - 1;
            }
            if (DAT_012056b8 < rectState->y + rectState->height) {
                drawBottom = rectState->height - 1;
            }
            
            // Draw rectangle (likely clearing or clipping)
            FUN_005d8680(rectState->x - 1, rectState->y - 1, drawRight + 1, drawBottom + 1);
            
            // Second textured draw with computed offsets
            uint32_t textureHandle2 = *(uint32_t*)(basePtr + 0x0c);
            float fVal = (float)(*(int32_t*)((int)someFloat + 4) * (int)rectState->y + *(int32_t*)((int)someFloat + 12) + rectState->x);
            float screenWidth2 = DAT_012056b4;
            uint32_t rectHeightU = *(uint32_t*)(basePtr + 0x10);
            
            FUN_005cd5f0(textureHandle2);
            FUN_00670550(renderContext,
                         *(uint32_t*)(basePtr + 4) & 0xf0ffffff,
                         (int)*(float*)(basePtr + 8),
                         &screenWidth2,
                         (float*)&rectHeightU,
                         fVal,
                         *(uint32_t*)(basePtr + 0x1c),
                         *(uint32_t*)(basePtr + 0x14),
                         *(uint32_t*)(basePtr + 0x18),
                         *(uint32_t*)(basePtr + 0x20),
                         in_XMM0_Da,
                         textureHandle2);
            
            this->animCounter++;
            
            // If special flags, draw additional overlay
            if ((*(uint32_t*)(basePtr + 0x28) & 0xe000) != 0) {
                float overlayX = (float)rectState->width;
                int overlayY   = rectState->height;
                float screenW2 = DAT_012056b4;
                float fVal2    = fVal;
                FUN_005cd5a0();
                FUN_005cdba0(&fVal2);
            }
            
            FUN_005db700(); // Finish render pass
            
            // Jump back to case 2/3 block (state 4 handling)
            goto switch_state_4;
        }
    }
    
    // After all frames done
    rectState->state = 8;
    return 0;
}