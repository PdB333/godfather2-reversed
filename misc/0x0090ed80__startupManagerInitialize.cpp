// FUNC_NAME: startupManagerInitialize

void startupManagerInitialize(void)
{
    // Perform global engine initialization
    FUN_004df600();

    // Prepare startup task data from global configuration
    struct StartupTaskData {
        int type;      // +0x00 - from global DAT_011303b8 (e.g., manager type or pointer)
        int param;     // +0x04 - always 0
        char flags;    // +0x08 - always 0
    };
    StartupTaskData taskData;
    taskData.type = DAT_011303b8;
    taskData.param = 0;
    taskData.flags = 0;

    // Register the startup task (index 0)
    FUN_00408a00(&taskData, 0);
}