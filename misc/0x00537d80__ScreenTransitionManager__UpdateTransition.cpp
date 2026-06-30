// FUNC_NAME: ScreenTransitionManager::UpdateTransition
void ScreenTransitionManager::UpdateTransition(bool enable, float targetValue, bool isRightSide, float blendWeight)
{
    // Global pointers identified from Ghidra
    // g_pSystemManager (DAT_012234c4) - system manager singleton
    // g_pScreenData (DAT_0121b0ac) - main screen data
    // g_pLeftPanelData (DAT_0121b638) - panel data for left/primary side
    // g_pRightPanelData (DAT_0121b63c) - panel data for right/secondary side
    // g_pAnimBlender1 (DAT_0121a394) - animation blender for blend values
    // g_pAnimBlender2 (DAT_0121a390) - animation blender for position/scale

    // Check if transition is enabled and we have valid data
    if (enable && 
        (*(int*)(g_pSystemManager + 0x24) != 0) && 
        ( (*(code**)(**(int**)(g_pSystemManager + 0x24) ))[1])(this + 0x30) != 0 &&
        (g_pScreenData != 0))
    {
        // Select panel data based on side
        int panelData;
        if (isRightSide)
            panelData = g_pRightPanelData;
        else
            panelData = g_pLeftPanelData;

        if (panelData != 0)
        {
            // Animate blend weight (param_4)
            int animHandle1 = GetAnimHandle(); // FUN_00414aa0
            float tempVar1 = blendWeight;
            SetAnimationFloat(g_pAnimBlender1, *(int*)(g_pScreenData + 0x18), animHandle1);

            // Animate target value (param_2)
            animHandle1 = GetAnimHandle();
            tempVar1 = targetValue;
            SetAnimationFloat(g_pAnimBlender1, *(int*)(g_pScreenData + 0x1c), animHandle1);

            // Choose panel-specific property offsets
            int propOffset;
            if (isRightSide)
                propOffset = *(int*)(g_pRightPanelData + 0x24);
            else
                propOffset = *(int*)(g_pLeftPanelData + 0x20);

            SetAnimationFloat(g_pAnimBlender2, propOffset, this);

            if (isRightSide)
                propOffset = *(int*)(g_pRightPanelData + 0x28);
            else
                propOffset = *(int*)(g_pLeftPanelData + 0x24);

            // Another animation target: uses FS segment data (likely thread-local or debug variable)
            int fsData = *(int*)(**(int**)(FS_SEGMENT_BASE + 0x2c) + 0x24) + 0x70;
            SetAnimationFloat(g_pAnimBlender2, propOffset, fsData);

            CommitAnimations(); // FUN_00537af0
            return;
        }
    }

    // Fallback: reset animations to zero
    if (*(int*)(g_pScreenData + 0x18) != 0)
    {
        Vector4 zero = {0, 0, 0, 0};
        zero.w = blendWeight;
        SetAnimationFloat(g_pAnimBlender1, *(int*)(g_pScreenData + 0x18), &zero);
    }

    int propOffset2;
    if (isRightSide)
    {
        if (g_pRightPanelData == 0)
            return;
        propOffset2 = *(int*)(g_pRightPanelData + 0x24);
    }
    else
    {
        if (g_pLeftPanelData == 0)
            return;
        propOffset2 = *(int*)(g_pLeftPanelData + 0x20);
    }

    if (propOffset2 != 0)
    {
        Vector4 zero = {0, 0, 0, 0};
        zero.w = 0.0f;
        SetAnimationFloat(g_pAnimBlender2, propOffset2, &zero);
    }
}

// Helper functions (assumed from Ghidra callees)
int GetAnimHandle(); // FUN_00414aa0 - returns some handle
void SetAnimationFloat(void* blender, int property, int handle); // FUN_0060add0
void SetAnimationFloat(void* blender, int property, void* vector); // overload for struct
void CommitAnimations(); // FUN_00537af0