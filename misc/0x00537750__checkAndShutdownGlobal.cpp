// FUNC_NAME: checkAndShutdownGlobal

extern int g_subsystemInitialized;

void shutdownSubsystem(void);

void checkAndShutdownGlobal() {
    if (g_subsystemInitialized != 0) {
        shutdownSubsystem();
    }
}