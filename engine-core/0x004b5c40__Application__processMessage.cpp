// FUNC_NAME: Application::processMessage

void Application::processMessage(int param1, int param2)
{
    // Initialize or update some global state (FUN_0043b490)
    someGlobalInitFunction();
    // Log a debug message with type 0x2001 and the provided parameter
    outputDebugString(0x2001, param2, 0);
    return;
}