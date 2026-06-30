// FUNC_NAME: Renderer::setClearColor

// Address: 0x00537b40
// Sets the clear color for the renderer based on fullscreen state.

void Renderer::setClearColor(bool isFullscreen)
{
    // Global renderer instance pointer
    Renderer* renderer = *reinterpret_cast<Renderer**>(0x0121a390);
    // Global display configuration structure pointer
    DisplayConfig* config = *reinterpret_cast<DisplayConfig**>(0x0121b638);
    // Constants for clear color in fullscreen and windowed modes
    // DAT_011280d0 and DAT_00e2e770 are likely static color values (e.g., RGBA)
    const uint* clearColor = reinterpret_cast<const uint*>(0x011280d0);
    if (!isFullscreen)
    {
        clearColor = reinterpret_cast<const uint*>(0x00e2e770);
    }

    // Set the display width (offset +0x14) – likely sets the backbuffer width
    renderer->setWidth(config->width); // FUN_0060b020

    // Set the clear color and display height (offset +0x28) – likely sets backbuffer height
    renderer->setClearColorAndHeight(config->height, clearColor); // FUN_0060add0
}