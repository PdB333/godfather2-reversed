// FUNC_NAME: ConsoleCommandManager::dispatchConsoleCommand

void ConsoleCommandManager::dispatchConsoleCommand(void* context)
{
    // Get the console manager singleton
    ConsoleCommandManager* mgr = getConsoleCommandManager(); // FUN_005a19c0
    if (!mgr)
        return;

    // Check if cheats/debug mode enabled? (FUN_0059ca10)
    if (!isDebugMode()) 
        return;

    // Get the command registry object at offset +8 from manager
    CommandRegistry* registry = *(CommandRegistry**)((char*)mgr + 8);
    if (!registry)
        return;

    int numCommands = *(int*)((char*)registry + 0x28);
    if (numCommands < 1)
        return;

    // Iterate over command groups (each 16 bytes)
    for (int groupIdx = 0; groupIdx < numCommands; ++groupIdx)
    {
        int groupOffset = groupIdx * 0x10;

        // Dereference: registry->groups[groupIdx].commandNode
        // structure: base+0xc is a pointer to a node, then node+0x28 is a pointer to a subtype
        int groupPtr = *(int*)(*(int*)((char*)registry + 0x2c) + 0xc + groupOffset);
        int nodePtr = *(int*)(groupPtr + 0x28); // This is the command node with string pairs and action handlers

        int numStrings = *(int*)(nodePtr + 0x30); // Number of string pairs in this node
        if (numStrings <= 0)
            continue;

        // The string pairs: each pair is two pointers (string and some integer)
        char** stringPairs = *(char***)(nodePtr + 0x34);

        // The input string to match is at registry->groups[groupIdx].inputString
        char* inputString = *(char**)(*(int*)((char*)registry + 0x2c) + groupOffset + 4);

        // Search for matching string in this node
        for (int strIdx = 0; strIdx < numStrings; ++strIdx)
        {
            char* currentString = stringPairs[strIdx * 2]; // First element is string pointer
            if (strcmp(currentString, inputString) == 0) // We'll use strcmp equivalent
            {
                // Match found! Now look up the action handler by matching the second element (int) 
                int patternInt = *(int*)((char*)stringPairs + strIdx * 8 + 4); // The int part of the pair

                // Get the action list from the node: nodePtr + 0xc points to an array of (int type, int pattern, int handler)
                int actionListCount = **(int**)(nodePtr + 0xc);
                if (actionListCount <= 0)
                    break;

                int* actionArray = *(int**)(*(int**)(nodePtr + 0xc) + 4); // Second element is array

                for (int actionIdx = 0; actionIdx < actionListCount; ++actionIdx)
                {
                    int* action = &actionArray[actionIdx * 3]; // Each action has three ints
                    int actionType = action[0];
                    int actionPattern = action[1];
                    if (actionType == 8 && actionPattern == patternInt)
                    {
                        // Found matching action; call the handler
                        int handlerFunc = action[2]; // Actually offset 8 from the action base
                        // FUN_005af370 takes (handlerFunc, context, -1)
                        callCommandHandler(handlerFunc, context, -1); // FUN_005af370
                        break; // Exit inner loops after handling? The original code breaks only inner loop
                    }
                }
                break; // Exit string search loop after match
            }
        }
    }
}