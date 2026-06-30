// FUN_006be8a0: NetObject::validateObjectTypes (validates type pairing for network operations)
// Address: 0x006be8a0
// Checks if either 'this' or 'other' object has a specific type hash (0x637b907).
// If neither matches, it logs an error with source location and aborts.
// If a match is found but validation fails, a different error is logged.

void __thiscall NetObject::validateObjectTypes(NetObject* thisObj, NetObject* otherObj, uint32_t context)
{
    char errorBuffer[4112]; // stack buffer for error message formatting (local_1014)

    // Check if this object's type ID matches the target type
    if (thisObj->mTypeHash == 0x637b907) // +0x54: class type hash
    {
        if (!isObjectValidForValidation())
        {
            logErrorMessage(0xff92ca40, context, 0); // Error: validation of this object failed
            return;
        }
    }
    else
    {
        // Check if the other object's type matches
        if (otherObj->mTypeHash == 0x637b907) // +0x54: class type hash
        {
            logErrorMessage(0xf5f69f67, context, 0); // Error: other object is of target type but this is not
            return;
        }

        // Neither object matches the target type; attempt general validation
        if (!isObjectValidForValidation())
        {
            enterCriticalSection();
            void** contextPtr = getErrorContextString();
            char* sourceString = (char*)*contextPtr;
            if (sourceString == nullptr)
            {
                sourceString = "(unknown source)"; // Fallback string (DAT_0120546e)
            }
            logSourceLine(100, sourceString);
            logErrorMessage(0x9518e280, context, errorBuffer);
            leaveCriticalSection();
        }
    }
}