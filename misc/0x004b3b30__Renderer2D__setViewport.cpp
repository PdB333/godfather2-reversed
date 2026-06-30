// FUNC_NAME: Renderer2D::setViewport
// Address: 0x004b3b30
// This function sets a rectangular viewport region via a virtual call on the global renderer singleton.

struct ViewportParams {
    int left;   // +0x00 = 2
    int top;    // +0x04 = 16
    int flags;  // +0x08 = 0
};

void __cdecl Renderer2D::setViewport(void)
{
    Renderer2D* renderer = (Renderer2D*)FUN_009c8f80(); // get global renderer singleton

    ViewportParams params;
    params.left   = 2;
    params.top    = 16;
    params.flags  = 0;

    // Call first virtual method (likely setViewport) with command ID 0x870 and params.
    (**(code**)*renderer)(0x870, &params);
    return;
}