// FUNC_NAME: tickTimerAndCallCallback
void tickTimerAndCallCallback(void* callbackObj, float deltaTime)
{
    // 0x00e446f4 - some timer threshold, possibly a fixed timestep interval
    if (0.0333f < deltaTime) // 0x00e446f4 = ~33ms (30fps timestep)
    {
        do
        {
            deltaTime = deltaTime - 0.0333f;
            // 0x0052c190 - likely a callback function that processes a tick
            FUN_0052c190(callbackObj);
        } while (0.0333f < deltaTime);
    }
    // 0x00e2b05c - another threshold, maybe half a timestep or a minimum tick threshold
    if (0.0167f < deltaTime) // 0x00e2b05c = ~16ms (60fps half-timestep?)
    {
        FUN_0052c190(callbackObj);
    }
    return;
}