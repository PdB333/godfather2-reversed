//FUNC_NAME: PopupRoot::handleClick
bool __thiscall PopupRoot::handleClick(const char* path)
{
    bool handled = false;
    char formattedPath[96];

    // Check if the clicked path matches button_0
    if (strcmp(path, "/text/popup_root/popup/button_0/button") == 0)
    {
        void* button0 = getButton0();
        processButton(button0);
        handled = true;
    }
    // Check if the clicked path matches button_1
    else if (strcmp(path, "/text/popup_root/popup/button_1/button") == 0)
    {
        void* button1 = getButton1();
        processButton(button1);
        handled = true;
    }

    // Iterate over content placeholder items (from m_itemStart to m_itemStart + m_itemCount - 1)
    unsigned int index = this->m_itemStart; // +0x74
    int count = this->m_itemCount;          // +0x80
    unsigned int end = index + count;
    for (; index < end; ++index)
    {
        // Format the hotspot path for this item
        formatString(formattedPath, sizeof(formattedPath),
                     "/text/popup_root/popup/contentPlaceholderMc/item%d/instance3/hotspot", index);

        if (strcmp(formattedPath, path) == 0)
        {
            void* button = getButton0(); // Same function as for button_0? Possibly a generic getButton
            processButton(button);
            handled = true;
        }
    }

    return handled;
}