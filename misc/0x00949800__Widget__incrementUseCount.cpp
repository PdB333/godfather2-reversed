// FUNC_NAME: Widget::incrementUseCount
void __fastcall Widget::incrementUseCount(Widget* this)
{
    char buffer[256];
    // +0x190: use count
    int& useCount = *(int*)((char*)this + 0x190);
    useCount++;
    // +0x18: object name (e.g., "hud_marker1")
    char* name = (char*)this + 0x18;
    if (useCount == 1 && *name != '\0')
    {
        __snprintf(buffer, 0x100, "%s._visible", name);
        // Set the Lua/script property "_visible" to false (0)
        Presentation::setProperty(buffer, 0);
    }
}