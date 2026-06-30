// FUNC_NAME: ResourceManager::loadResourceFromDescriptor
unsigned int __fastcall loadResourceFromDescriptor(
    unsigned int unusedParam,           // ecx - possibly 'this' but not used
    unsigned int descriptor,            // edx - the resource descriptor
    unsigned int context,               // first stack param - context or parent
    unsigned int extraParam             // second stack param - additional flags
)
{
    int iResult;        // result from parse
    char descriptorFlags; // single byte flag from parse
    int resourceHandle; // resource handle or size

    resourceHandle = 0;
    // Parse the descriptor to extract flags and handle
    iResult = FUN_005f0560(descriptor, &descriptorFlags, &resourceHandle);
    if ((iResult != 0) && (resourceHandle != 0))
    {
        // Load the actual resource using the handle and context
        return FUN_005e4a80(context, resourceHandle, extraParam);
    }
    return 0;
}