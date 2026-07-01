// FUNC_NAME: UIElement::render
// Address: 0x007d9ad0
// Role: Renders a UI element with clipping, material, and transform state.
// Uses a canvas object (this+0x58) to obtain clip rectangle, material pointer, and flags.
// Visibility state at this+0x88: 0 = visible, 0x48 = hidden (or disabled).

void __fastcall UIElement::render(UIElement* this)
{
    UICanvas* pCanvas = *(UICanvas**)((int)this + 0x58); // +0x58: pointer to canvas
    int visibilityState = *(int*)((int)this + 0x88);     // +0x88: visibility state (0 or 0x48)

    if (visibilityState == 0 || visibilityState == 0x48)
    {
        // Read clip rectangle from canvas (offsets 0x2b84..0x2b90)
        int clipLeft   = *(int*)((int)pCanvas + 0x2b84);
        int clipTop    = *(int*)((int)pCanvas + 0x2b88);
        int clipRight  = *(int*)((int)pCanvas + 0x2b8c);
        int clipBottom = *(int*)((int)pCanvas + 0x2b90);

        // If all zero, allocate a default clip rect
        if (clipLeft == 0 && clipTop == 0 && clipRight == 0 && clipBottom == 0)
        {
            // Allocation parameters: type=2, size=0x10, flags=0
            int allocParams[3] = { 2, 0x10, 0 };
            int* pAlloc = (int*)FUN_009c8ed0(0x1b0, allocParams); // allocate 0x1b0 bytes
            if (pAlloc != 0)
            {
                uVar2 = FUN_006c2840(); // create default clip rect object
            }
            else
            {
                uVar2 = 0;
            }
        }
        else
        {
            uVar2 = FUN_00446130(&clipLeft, 0); // convert int rect to clip object
        }

        FUN_007d3ad0(uVar2); // set clip rect on render device
        FUN_006c1360();      // update transform stack

        // Compute state index: if visibilityState == 0, index=0; else index=0x68 (since 0x48-0x48=0, then +0x68)
        int stateIndex;
        if (visibilityState == 0)
            stateIndex = 0;
        else
            stateIndex = visibilityState - 0x48; // becomes 0
        stateIndex += 0x68; // base offset for render state

        FUN_006c16d0(stateIndex); // push render state (matrix? blend?)

        // Save current transform from global render device
        int* pRenderDevice = DAT_01129944; // global render device pointer
        *(undefined8*)(pRenderDevice + 0x108) = local_10; // save transform
        *(undefined4*)(pRenderDevice + 0x110) = local_8;

        // Extract flip flag from canvas flags (bit 2 of field at +0x249c)
        bool flipX = (*(int*)((int)pCanvas + 0x249c) >> 2) & 1;

        // Manage material pointer (reference counting)
        int* pNewMaterial = (int*)((int)pCanvas + 0x48); // +0x48: material pointer
        if (local_120 != pNewMaterial)
        {
            if (local_120 != 0)
            {
                FUN_004daf90(&local_120); // release old material
            }
            local_120 = pNewMaterial;
            if (pNewMaterial != 0)
            {
                local_11c = *(undefined4*)((int)pCanvas + 0x4c); // +0x4c: material reference count?
                *(int**)((int)pCanvas + 0x4c) = &local_120;      // store pointer to local
            }
        }

        // Push another render state (maybe for material)
        FUN_006c16d0(local_148); // buffer for state

        // Compute state index again (same as before)
        if (visibilityState == 0)
            stateIndex = 0;
        else
            stateIndex = visibilityState - 0x48;
        stateIndex += 0x68;

        // Draw the element: uses texture/color from canvas+0x2494, state index, and flags
        FUN_00424dc0(*(undefined4*)((int)pCanvas + 0x2494), stateIndex, 0, 0, 1);

        // Release material if we took ownership
        if (local_120 != 0)
        {
            FUN_004daf90(&local_120);
        }
    }
}