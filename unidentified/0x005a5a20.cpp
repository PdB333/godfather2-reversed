// FUN_NAME: AptAnimation::postLoad
// Address: 0x005a5a20
// Description: Finalizes loading of imported characters and resolves references between them.
// Class: AptAnimation (from AptAnimation.cpp file path in assert)
// Uses EARS engine's Apt (Adobe Presentation Toolkit) for UI.

void AptAnimation::postLoad(void* context) // param_1 is some context/handle, used for type 7 callback
{
    // --- First pass: ensure all imported characters are loaded ---
    int importCount = *(int*)(this + 0x20); // m_importCount
    if (importCount > 0)
    {
        void** characters = *(void***)(this + 0x10);   // m_characters (array of AaptCharacter*)
        int* imports = *(int**)(this + 0x24);          // m_imports (array of ImportStruct, 0x10 bytes each)
        for (int i = 0; i < importCount; ++i)
        {
            // Each import struct is 0x10 bytes
            int* importEntry = (int*)((char*)imports + i * 0x10);
            int nID = importEntry[2]; // +0x08: nID (index into m_characters)
            if (characters[nID] != 0)
            {
                // Assertion: apCharacters[aImports[i].nID] == 0
                // File: ..\source\Apt\AptAnimation.cpp line 0x183 (387)
                // This should never happen: character slot should be null before loading.
                // The assertion mechanism uses global flag DAT_01128f8e and possibly a debug break.
                // Simplified as an unconditional break in debug builds.
                #ifdef _DEBUG
                    __debugbreak(); // or custom assert
                #endif
            }

            // Load/create the character using the data at offset 0x0C of the import struct
            int creationArg = importEntry[3]; // +0x0C: some identifier (e.g., name/ID)
            characters[nID] = (void*)FUN_005a4650(creationArg); // FUN_005a4650 likely loads or creates a character
        }
    }

    // --- Second pass: resolve references between characters ---
    int characterCount = *(int*)(this + 0x0C); // m_characterCount
    if (characterCount > 0)
    {
        void** characters = *(void***)(this + 0x10); // m_characters
        for (int i = 0; i < characterCount; ++i)
        {
            if (characters[i] != 0)
            {
                int* charHeader = (int*)characters[i];
                int type = charHeader[0]; // +0x0: type field
                if (type == 3)
                {
                    // Type 3: remap an index array to direct pointers
                    int count = charHeader[3]; // +0x0C: number of entries
                    int* indexArray = (int*)charHeader[4]; // +0x10: array of indices into m_characters
                    for (int j = 0; j < count; ++j)
                    {
                        int index = indexArray[j];
                        indexArray[j] = (int)characters[index]; // replace index with actual pointer
                    }
                }
                else if (type == 7)
                {
                    // Type 7: call a global callback/handler
                    int someData = charHeader[2]; // +0x08: additional data for callback
                    // DAT_0119cb5c is a global function pointer (likely registered handler)
                    ((void(*)(void*, int, int))DAT_0119cb5c)(context, i, someData);
                }
            }
        }
    }
}