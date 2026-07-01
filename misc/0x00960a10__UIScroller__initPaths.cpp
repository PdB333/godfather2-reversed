// FUNC_NAME: UIScroller::initPaths
void __thiscall UIScroller::initPaths(char *basePath)
{
    // Store base path pointer
    this->basePath = basePath;

    // Build paths for scroller UI elements
    // Buffer sizes are 0x200 (512) bytes each
    sprintf(this->arrUpPath, 0x200, "%s/scroller/arr_up/hspt", basePath);       // +0x04
    sprintf(this->arrDownPath, 0x200, "%s/scroller/arr_down/hspt", basePath);   // +0x204
    sprintf(this->sliderPath, 0x200, "%s/scroller/slider/hspt", basePath);      // +0x404
    sprintf(this->trackPath, 0x200, "%s/scroller/track/hspt", basePath);        // +0x604
    sprintf(this->itemPathTemplate, 0x200, "%s/items/item_%%d/hspt", basePath); // +0x804

    // Initialize item count (will be set later when items are populated)
    this->itemCount = 0; // +0xA04
}