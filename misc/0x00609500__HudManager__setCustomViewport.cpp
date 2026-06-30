// FUNC_NAME: HudManager::setCustomViewport
void __thiscall HudManager::setCustomViewport(int left, int width, undefined4 extra)
{
    // Register-provided parameters (set by caller in EAX, EDI, XMM0):
    int top = in_EAX;          // Y position
    int height = unaff_EDI;    // Height
    float rotation = in_XMM0_Da; // Angle or alpha

    // Store full region data into global rectangle buffer (+0x00..0x14)
    RectData* rectBuffer = (RectData*)0x011d91c0;
    rectBuffer->x1 = left;
    rectBuffer->y1 = top;
    rectBuffer->x2 = unaff_EDI; // Actually width? See calculation later.
    rectBuffer->y2 = width;     // Actually height? Yes, used as divisor.
    rectBuffer->angle = rotation;
    rectBuffer->extra = extra;

    // Width and height are in EDI and param2 (width) respectively
    // Left and top are param1 (left) and EAX (top)

    // Call virtual function 0xBC on global render device (offset 0xBC = setViewport)
    IRenderDevice* renderDevice = (IRenderDevice*)DAT_01205750;
    (renderDevice->vtable->setViewport)(renderDevice, &rectBuffer[0]); // See note

    // Compute aspect ratio adjustments using base resolution DAT_00e2b1a4 (likely 640 or 800)
    float scaleX = DAT_00e2b1a4 / (float)height;   // unaff_EDI = height? Actually used as width divisor. Let's assume width = EDI.
    float scaleY = DAT_00e2b1a4 / (float)width;     // param_2 = width? Actually used as height divisor.
    // Multiply by a global scale factor (maybe 1.0f or 4/3 ratio)
    float scaledX = scaleX * DAT_00e2cd54;
    float scaledY = scaleY * DAT_00e2cd54;

    // Save scaled rect for later use
    struct {
        float sx, sy, ssx, ssy; // scale factors and scaled
    } scaledRect;
    scaledRect.sx = scaleX;
    scaledRect.sy = scaleY;
    scaledRect.ssx = scaledX;
    scaledRect.ssy = scaledY;

    // Store scaled data to global area
    _DAT_011f6680 = scaleX;
    fRam011f6684 = scaleY;
    fRam011f6688 = scaledX;
    fRam011f668c = scaledY;

    // Apply aspect ratio to child widgets (if they exist)
    // DAT_012058e8 points to a HUD element object
    if (DAT_012058e8 != 0)
    {
        // Child widget at +0x60 (96) – possibly a minimap or stat display
        if (*(int*)(DAT_012058e8 + 0x60) != 0)
        {
            FUN_0060add0(*(int*)(DAT_012058e8 + 0x14),   // child ID or texture
                         *(int*)(DAT_012058e8 + 0x60),   // child object
                         &scaledRect);
        }
        // Another child at +100 (0x64) – maybe separate layer
        if (*(int*)(DAT_012058e8 + 100) != 0)
        {
            FUN_0060add0(*(int*)(DAT_012058e8 + 0x10),   // other resource
                         *(int*)(DAT_012058e8 + 100),    // other child
                         &scaledRect);
        }
    }

    // Call virtual function 0x12C (300) on render device (maybe reset scissor or pop frame)
    (renderDevice->vtable->resetRect)(renderDevice, &rectBuffer[2]); // rectBuffer+0x18 (0x11d91d8)

    // Enforce minimum viewport width (0xAE = 174)
    if (DAT_012058d4 < 0xAE)
        DAT_012058d4 = 0xAE;

    // Clear a global flag
    _DAT_011f3c90 = 0;

    // Also enforce minimum on another global height (maybe screen height)
    if (0xAE < DAT_00f1598c)
        DAT_00f1598c = 0xAE;
}