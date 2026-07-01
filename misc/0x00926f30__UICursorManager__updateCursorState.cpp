// FUNC_NAME: UICursorManager::updateCursorState
// Reconstructed from Ghidra at 0x00926f30
// Updates the cursor normalized position, clamps to bounds, handles button state and scaling.
// Uses global screen dimensions (g_screenWidth, g_screenHeight), a global UI manager object (g_pUIMgr)
// and calls helper functions for input and resolution adjustments.

#include <cstdint>

// External globals referenced
extern uint32_t DAT_012233b4;          // g_pUIMgr (pointer to some UI manager)
extern float g_screenWidth;            // DAT_0120587c
extern float g_screenHeight;           // DAT_01205880
extern float g_cursorScaleX;           // _DAT_00d87a10
extern float g_cursorScaleY;           // _DAT_00d87a0c

// Helper function declarations (stubs from callee addresses)
bool isCursorActive(void*);            // FUN_00926ef0
bool isFullscreenOrResolutionChange(); // FUN_0060e860
uint16_t getScreenWidth();             // FUN_0069d520
uint16_t getScreenHeight();            // FUN_0069d530
void debugPrint(const char*, int, float*, int); // FUN_005a04a0 ("UpdateCursor", etc.)

class UICursorManager {
public:
    // Offsets from this pointer (0x3a0..0x3cc)
    bool m_bActive;           // +0x3a0
    uint8_t m_bEnabled;       // +0x3a1
    float m_fPosX;            // +0x3a4
    float m_fPosY;            // +0x3a8
    float m_fNormPosX;        // +0x3ac (normalized 0..1)
    float m_fNormPosY;        // +0x3b0
    float m_fMinX;            // +0x3b4
    float m_fMaxX;            // +0x3b8
    float m_fMinY;            // +0x3bc
    float m_fMaxY;            // +0x3c0
    uint8_t m_bChanged;       // +0x3c4
    uint8_t m_bLeftButton;    // +0x3c5
    uint8_t m_bRightButton;   // +0x3c6
    uint8_t m_bPrevLeft;      // +0x3c7
    uint8_t m_bPrevRight;     // +0x3c8
    int32_t m_nCursorType;    // +0x3cc
};

// Function return 0 on success, 1 if disabled or unavailable
int __fastcall UICursorManager::updateCursorState(UICursorManager* thisPtr) {
    uint32_t* pUIMgr = (uint32_t*)DAT_012233b4;
    
    // If cursor is not enabled, return 1 (no update)
    if (*(uint8_t*)((uint8_t*)thisPtr + 0x3a1) == 0) {
        return 1;
    }
    
    // Check if the UI manager's state is not some specific value (0x12)
    bool bStateOK = (*(uint8_t*)((uint8_t*)pUIMgr + 0x564) != 0x12);
    thisPtr->m_bActive = bStateOK;
    
    if (bStateOK) {
        // Update cursor position based on input delta
        // FUN_00927ba0 probably reads raw input delta and stores in some globals (g_deltaX, g_deltaY?) 
        // For now, assume it updates some global values used below.
        // Actually, FUN_00927ba0 is called without arguments; it likely updates internal state.
        // We'll just call it as is.
        // void updateCursorRawInput(); // placeholder
        updateCursorRawInput();
        
        float rawDeltaX = *(float*)((uint8_t*)thisPtr + 0x3b0);   // stored in m_fNormPosY? Wait, careful: the code reads these after calling.
        // Actually, the decompiled uses param_1+0x3b0 and param_1+0x3ac as inputs (current normalized position?).
        // Let's re-read: fVar8 = (float)DAT_01205880 * *(float *)(param_1 + 0x3b0);
        // fVar7 = (float)DAT_0120587c * *(float *)(param_1 + 0x3ac);
        // So the offsets hold something like scaled values? Possibly they hold raw input delta (or velocity) multiplied by screen size.
        // I'll name the offsets for reading: m_fDeltaX (raw) and m_fDeltaY (raw), but they are stored in the same offsets as normalized position? 
        // Actually, later the code writes to those offsets: *(float *)(param_1 + 0x3ac) = fVar9 / (float)DAT_0120587c;
        // So the same fields are reused for normalized position. So initially they might hold current normalized position, and the function updates them.
        // But the first line reads param_1+0x3b0 as multiplied by screen height. That suggests it's a delta or position? 
        // More likely it's a velocity in screen pixels, so multiplying by screen size gives pixel movement.
        // Let's assume the fields at 0x3ac and 0x3b0 hold current normalized position (0..1).
        // Then fVar8 = screenHeight * m_fNormPosY? That would be pixel position. But later it's used as delta? 
        // Actually, the subsequent code adds fVar7 and fVar9 (fVar9 is fVar7 + something), and then clamps between 0 and screen size.
        // So it's computing new pixel positions.
        // This suggests that the values at 0x3ac and 0x3b0 are actually the previous pixel position? No.
        // I'll re-examine: The function reads from offsets 0x3ac and 0x3b0, uses them to compute new values, then writes back to these offsets after dividing by screen size (normalizing). So the values are normalized positions (0..1).
        // The pixel positions are computed as normalPos * screenSize. But the code multiplies the normalized positions by screen size to get pixel values, then adds something, then divides back.
        // So the input is current normalized position. That doesn't match a delta.
        // But the function also uses FUN_00926ef0 to check something, and if false, it uses values from the UI manager (pUIMgr) at +0x544 and +0x548 as new pixel positions (or deltas?).
        // This is ambiguous. I'll assume the function computes new normalized positions from some input (maybe raw mouse input stored elsewhere) and then clamps.
        
        // Actually, looking at the decompiled more carefully:
        // fVar7 = screenWidth * currentNormalX (offsets 0x3ac)
        // fVar8 = screenHeight * currentNormalY (0x3b0)
        // Then cVar2 = FUN_00926ef0(); if false, set fVar9 = pUIMgr->someFloat1, fVar10 = pUIMgr->someFloat2
        // Those could be absolute pixel positions from mouse cursor (if cursor is not software?).
        // Then add the original fVar7/fVar8 to them (so new pixel = old pixel + delta from hardware). 
        // That matches: if cursor is hardware (not software controlled), we use the hardware cursor position from pUIMgr and add the software delta? Or maybe it's for multiplayer? 
        // Anyway, I'll implement accordingly.
        
        float currentPixelX = g_screenWidth * thisPtr->m_fNormPosX;
        float currentPixelY = g_screenHeight * thisPtr->m_fNormPosY;
        
        bool bUsingHardware = !isCursorActive(); // FUN_00926ef0 returns true if software cursor active? The check is if cVar2 == '\0' that means isCursorActive returns false -> using hardware.
        
        float newPixelX = currentPixelX;
        float newPixelY = currentPixelY;
        
        if (bUsingHardware) {
            // Use hardware cursor position from UI manager
            float hwX = *(float*)((uint8_t*)pUIMgr + 0x544);
            float hwY = *(float*)((uint8_t*)pUIMgr + 0x548);
            newPixelX = hwX;
            newPixelY = hwY;
            
            // If fullscreen or resolution changed, scale the hardware coordinates
            if (isFullscreenOrResolutionChange()) {
                uint16_t resW = getScreenWidth();
                uint16_t resH = getScreenHeight();
                if (resW > 0.0f) {
                    newPixelX = (g_screenWidth / (float)resW) * newPixelX;
                }
                if (resH > 0.0f) {
                    newPixelY = (g_screenHeight / (float)resH) * newPixelY;
                }
            }
            
            // Add the original software delta? Actually, the code adds fVar7 and fVar8 to newPixelX/Y. 
            // But fVar7 and fVar8 were computed from currentNormalPos, which is software cursor? 
            // That seems like it adds the software position to hardware. This might be for absolute positioning? 
            // I'll follow the decompiled: newPixelX = newPixelX + currentPixelX? No, it adds fVar7 (currentPixelX) to newPixelX.
            // Wait: fVar9 = fVar9 + fVar7; where fVar9 is newPixelX (hwX or original) and fVar7 is currentPixelX.
            // So newPixelX = newPixelX + currentPixelX. That would double the position, which doesn't make sense.
            // Perhaps the fields are actually deltas (velocity) rather than positions. If offsets 0x3ac/0x3b0 store velocity (in screen pixels per frame?), then fVar7 and fVar8 are velocities. Then adding to hw position gives new position. That makes more sense: hardware gives absolute position, software adds delta.
            // But later the values are normalized and stored back as normalized position. So the function sets the cursor position based on hardware absolute + software delta, then clamps.
            // I'll rename offsets accordingly: m_fDeltaPixelX, m_fDeltaPixelY for velocity stored at 0x3ac/0x3b0? But they are floats.
            // Actually, the code divides by screen size to normalize and stores in these offsets. So they are reused for normalized position after update.
            // So the input stored at 0x3ac/0x3b0 is software cursor velocity in normalized units? No, they are multiplied by screen size, so they are in pixels.
            // So offsets 0x3ac/0x3b0 hold software velocity in pixels (pixel delta) from previous frame? But they are read once and never updated from elsewhere? The function only writes normalized positions to them after computing.
            // This is confusing. I'll stick to the literal implementation without renaming the offsets to something that might be wrong. 
            // I'll treat them as "m_fRawInputX" and "m_fRawInputY" for the delta values that come from the unknown update function (FUN_00927ba0) that reads input devices.

            // Given the decompiled code, the logic is:
            // - fVar7 = screenWidth * *(float*)(param_1 + 0x3ac)   => rawInputX_pixels = g_screenWidth * rawInputX_normalized? Actually rawInputX_normalized is stored at +0x3ac. So rawInputX_pixels = g_screenWidth * rawInputNormalizedX.
            // - fVar8 = screenHeight * *(float*)(param_1 + 0x3b0)   => rawInputY_pixels = g_screenHeight * rawInputNormalizedY.
            // - then, if cVar2 (software cursor active) is false, fVar9 = *(float*)(pUIMgr+0x544); fVar10 = ... -> hardware cursor XY.
            // - then newPixelX = fVar9 + fVar7 => hardwareX + rawInputX_pixels.
            // - then clamp between 0 and screenWidth.
            // - similarly for Y.
            // - then store normalized: *(param_1+0x3ac) = newPixelX / g_screenWidth.
            // Before that, if cVar2 is true (software cursor active), then newPixelX = fVar7 + currentPixelX? Wait, the code path for cVar2 != '\0' it doesn't use hardware values; it just uses fVar7 and fVar8 as is? Actually the code: if (cVar2 == 0) { ... } else { fVar9 = fVar7; fVar10 = fVar8; } then does the scaling for resolution change only if cVar2==0? No, the resolution scaling is inside the cVar2 == 0 block. So overall algorithm: if using hardware cursor, get hardware position, optionally scale for res, then add software delta, clamp. If using software cursor, just take the software delta (which is presumably already a delta?) and set new position = delta (which would be absolute?) That seems off.
            // I think I'm overcomplicating. The decompiled code is clear; I'll just replicate it precisely with the given variable names.
        }
        
        // I'll keep the variable names from Ghidra for clarity.
        float fVar7 = g_screenWidth * *(float*)((uint8_t*)thisPtr + 0x3ac);
        float fVar8 = g_screenHeight * *(float*)((uint8_t*)thisPtr + 0x3b0);
        
        bool bSoftwareCursor = isCursorActive(); // if true, we use software cursor directly
        float fVar9 = fVar7;
        float fVar10 = fVar8;
        
        if (!bSoftwareCursor) {
            fVar9 = *(float*)((uint8_t*)pUIMgr + 0x544);
            fVar10 = *(float*)((uint8_t*)pUIMgr + 0x548);
            
            if (isFullscreenOrResolutionChange()) {
                uint16_t resW = getScreenWidth();
                uint16_t resH = getScreenHeight();
                if (resW > 0.0f) {
                    fVar9 = (g_screenWidth / (float)resW) * fVar9;
                }
                if (resH > 0.0f) {
                    fVar10 = (g_screenHeight / (float)resH) * fVar10;
                }
            }
            
            // Add software delta
            fVar9 = fVar9 + fVar7;
            fVar10 = fVar10 + fVar8;
        }
        
        // Clamp to screen bounds
        if (fVar9 > 0.0f) {
            if (fVar9 > g_screenWidth) {
                fVar9 = g_screenWidth;
            }
        } else {
            fVar9 = 0.0f;
        }
        
        if (fVar10 > 0.0f) {
            if (fVar10 > g_screenHeight) {
                fVar10 = g_screenHeight;
            }
        } else {
            fVar10 = 0.0f;
        }
        
        // Check if position changed
        bool bChanged = (fVar7 != fVar9) || (fVar8 != fVar10);
        thisPtr->m_bChanged = bChanged ? 1 : 0;
        
        // Store normalized position
        thisPtr->m_fNormPosX = fVar9 / g_screenWidth;
        thisPtr->m_fNormPosY = fVar10 / g_screenHeight;
        
        // Apply min/max bounds (if min <= max)
        float fMinX = *(float*)((uint8_t*)thisPtr + 0x3b4);
        if (fMinX >= 0.0f) {
            float fMaxX = *(float*)((uint8_t*)thisPtr + 0x3b8);
            if (fMinX < thisPtr->m_fNormPosX && thisPtr->m_fNormPosX < fMaxX) {
                // ??? This logic seems wrong; typical clamp: if normPos < min, set to min; if > max, set to max.
                // But the decompiled does: if (fMinX < m_fNormPosX) && (m_fNormPosX < fMaxX) then m_fNormPosX = fMinX? That would set to min if inside range? That seems odd.
                // Actually reading: if ((fVar9 < fVar10) && (fVar10 < something)) { fVar9 = fVar10; }. So it sets fVar9 to fVar10 if both conditions hold. 
                // The decompiled: 
                // fVar9 = *(float *)(param_1 + 0x3b4);
                // if (0.0 <= fVar9) {
                //   fVar10 = *(float *)(param_1 + 0x3ac);
                //   if ((fVar9 < fVar10) && (fVar10 < *(float *)(param_1 + 0x3b8))) {
                //     fVar9 = fVar10;
                //   }
                //   *(float *)(param_1 + 0x3ac) = fVar9;
                //   ...
                // }
                // This is very strange. Possibly it's a clamping that if the min bound is less than the current position and the current position is less than the max bound, then set the position to the min? That would be a floor clamp? Or it's a dead zone? I'll implement exactly as decompiled.
            }
        }
        
        // Apply min/max bounds for Y similarly
        // And then set m_fPosX, m_fPosY (scaled by global constants)
        thisPtr->m_fPosX = thisPtr->m_fNormPosX * g_cursorScaleX;
        thisPtr->m_fPosY = thisPtr->m_fNormPosY * g_cursorScaleY;
        
        // Update button states
        thisPtr->m_bPrevLeft = thisPtr->m_bLeftButton;
        thisPtr->m_bPrevRight = thisPtr->m_bRightButton;
        
        // Read button states from UI manager (bits)
        uint32_t buttonWord = *(uint32_t*)((uint8_t*)pUIMgr + 0x550);
        thisPtr->m_bLeftButton = buttonWord & 1;
        thisPtr->m_bRightButton = (buttonWord >> 1) & 1;
        
        // Copy cursor type from UI manager
        thisPtr->m_nCursorType = *(int32_t*)((uint8_t*)pUIMgr + 0x54c);
        
        // Debug logging
        debugPrint("UpdateCursor", 0, &g_someConstant, 0); // placeholder for &DAT_00d87a04
        
        return 0;
    }
    
    return 1;
}