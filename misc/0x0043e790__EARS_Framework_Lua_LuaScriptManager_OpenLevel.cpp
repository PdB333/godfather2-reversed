// Xbox PDB: EARS::Framework::Lua::LuaScriptManager::OpenLevel
// FUNC_NAME: cEARSManager::initLoggingAndProcessModules

void __fastcall cEARSManager::initLoggingAndProcessModules(cEARSManager* thisPtr)
{
    // Get the core engine system object
    int* pSystem = reinterpret_cast<int*>(FUN_00627840());
    thisPtr->m_pSystem = pSystem;

    // Initialize logging system with name "EclipseLog"
    FUN_00625ca0(pSystem, "EclipseLog");

    // Check if the system's buffer capacity is exceeded; if so, flush/dump
    int* bufferMgr = reinterpret_cast<int*>(pSystem[0x10 / 4]); // +0x10
    if (bufferMgr[0x20 / 4] <= bufferMgr[0x24 / 4]) {
        FUN_00627360(); // Likely flushes the log buffer
    }

    // Allocate a temporary log node with vtable at 0x0043e5c0
    int* pNode = reinterpret_cast<int*>(FUN_00638110(0));
    pNode[0x0C / 4] = 0x0043e5c0; // Set vtable pointer

    // Push the node onto the system's active list (type 6)
    int* listPtr = reinterpret_cast<int*>(pSystem[0x08 / 4]); // +0x08 (buffer cursor)
    listPtr[1] = reinterpret_cast<int>(pNode);
    *listPtr = 6; // type code
    pSystem[0x08 / 4] = reinterpret_cast<int>(listPtr) + 8; // advance buffer cursor

    // Immediately pop the node (calling its destructor via FUN_00633d60)
    int* bufferBase = reinterpret_cast<int*>(pSystem[0x08 / 4]);
    FUN_00633d60(reinterpret_cast<int>(&pSystem[0x40 / 4]), reinterpret_cast<int>(bufferBase - 0x10), reinterpret_cast<int>(bufferBase - 0x08));
    pSystem[0x08 / 4] = reinterpret_cast<int>(bufferBase) - 0x10; // restore cursor

    // Iterate over all registered modules in the list (linked list at +0x38)
    int* currentModule = reinterpret_cast<int*>(thisPtr->m_moduleList); // +0x38
    while (true) {
        int* listHead = reinterpret_cast<int*>(thisPtr->m_moduleList);
        if (currentModule == listHead) break;

        // Call the module's virtual function at index 1 (offset +4 from vtable)
        // The module's vtable is at *(int*)currentModule[2] (offset 8 from node)
        int* moduleVTable = reinterpret_cast<int*>(currentModule[2]); // +0x08
        (*(void(__thiscall**)(int))(moduleVTable[1]))(reinterpret_cast<int>(pSystem));

        currentModule = reinterpret_cast<int*>(currentModule[0]); // next node
    }
}