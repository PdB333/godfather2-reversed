//FUNC_NAME: WindowManager::collectWindows
void __fastcall WindowManager::collectWindows(WindowManager* this)
{
    // Get the global UI manager (singleton) that holds all UI objects
    UIManager* uiMgr = getUIManager(); // FUN_0054a4d0
    int numObjects = *(int*)(uiMgr + 0xC); // count of UI objects
    if (numObjects > 0)
    {
        int* objectArray = *(int**)(uiMgr + 8); // array of UI object pointers
        for (int i = 0; i < numObjects; i++)
        {
            int obj = objectArray[i];
            char* name = *(char**)(obj + 0x70); // object name string
            if (strstr(name, "window") != NULL)
            {
                int index = getWindowIndex(obj); // FUN_00858dd0 – returns a slot index for this window
                // Store the window object in the local list at offset +0x128
                *(int*)(this + 0x128 + index * 4) = obj;
                // Increment the count of collected windows at offset +0x124
                (*(int*)(this + 0x124))++;
            }
        }
    }
}