//FUNC_NAME: SimManager::validateAndCleanupObject
void __fastcall SimManager::validateAndCleanupObject(uint unusedParam, SimObject* object, uint* inputPtr)
{
    int someFlag = 0;
    uint* foundObject = nullptr;

    // Look up an object by key: *inputPtr is the key, object+0x30 is some identifier
    findObjectByKey(*inputPtr, *(uint*)((uint)object + 0x30), 0, &someFlag, &foundObject);

    if (foundObject != nullptr)
    {
        // Check if object size > 0x3FFF and bit 15 of first word is set
        if ((foundObject[0x0C] > 0x3FFF) && ((foundObject[0] >> 0x0F) & 1))
        {
            if (foundObject[0x15] != 0)
            {
                uint managerHandle = getManager(); // e.g., getObjectManager()
                if (foundObject[0x0D] != 0)
                {
                    uint* currentObject = (uint*)getCurrentObject(managerHandle);
                    if (currentObject == foundObject)
                    {
                        removeObject(managerHandle); // e.g., remove from active list
                    }
                }
            }
            updateManager(); // e.g., process pending removals
        }
    }
}