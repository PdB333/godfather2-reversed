// FUNC_NAME: shutdownEngine

void shutdownEngine(void)
{
    // Release global engine objects (order may matter)
    releaseObject(&g_engineObject1);   // DAT_01206970
    releaseObject(&g_engineObject2);   // DAT_01206968
    releaseObject(&g_engineObject3);   // DAT_01206978
    releaseObject(&g_engineObject4);   // DAT_012069d4
    releaseObject(&g_engineObject5);   // DAT_012069ec
    releaseObject(&g_engineObject6);   // DAT_01206980
    releaseObject(&g_engineObject7);   // DAT_01206960

    // Run three update ticks to drain pending work
    int iterationCount = 3;
    do {
        processOneUpdateTick(); // FUN_004e3dc0
        iterationCount = iterationCount - 1;
    } while (iterationCount != 0);

    // Final termination of subsystems
    finalTermination(); // FUN_004e3f30

    // Destroy singleton manager via its virtual destructor
    if (g_singletonManagerPtr != (void**)0x0) {
        (**(code**)*g_singletonManagerPtr)(1); // call vtable[0] (destroy) with arg 1
        g_singletonManagerPtr = (void**)0x0;
    }
}