// FUNC_NAME: GodfatherGameManager::processAIList
void __thiscall GodfatherGameManager::processAIList(char enableParam)
{
    int *objectList;
    int *listManager;
    int objectCount;
    int objectIndex;
    int currentObject;
    void (**vtableFunc)(int);

    // Check two state fields: likely pointers or flags that must be valid and not 0x48
    if (*(int *)(this + 0x2178) != 0 && *(int *)(this + 0x2178) != 0x48 &&
        (objectList = *(int *)(this + 0x1ed8), objectList != 0 && objectList != 0x48))
    {
        // Retrieve singleton manager (e.g., AI Behavior Manager)
        listManager = (int *)FUN_0043b870(DAT_01131010);
        objectIndex = 0;
        // Loop through array of object IDs stored in objectList + 0xdc, count at +0xe0
        if (*(int *)(objectList + 0xe0) != 0)
        {
            do
            {
                // Resolve each ID to an object pointer
                currentObject = FUN_009b9c00(*(int *)(*(int *)(objectList + 0xdc) + objectIndex * 4));
                if (currentObject != 0)
                {
                    // Select vtable method: offset 0x20 for non‑zero param, 0x24 for zero
                    if (enableParam == '\0')
                        vtableFunc = *(void (***)(int))(*listManager + 0x24);
                    else
                        vtableFunc = *(void (***)(int))(*listManager + 0x20);
                    (*vtableFunc)(currentObject);
                }
                objectIndex++;
            } while (objectIndex < *(unsigned int *)(objectList + 0xe0));
        }
    }
}