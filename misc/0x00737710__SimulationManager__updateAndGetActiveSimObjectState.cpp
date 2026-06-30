// FUNC_NAME: SimulationManager::updateAndGetActiveSimObjectState
int __fastcall SimulationManager::updateAndGetActiveSimObjectState(void)
{
    // Offset 0x2134: pointer to active SimObject handle (likely a handle or ID)
    int iSimObjectHandle = *(int *)((char *)this + 0x2134);
    
    // Validate the handle through a dedicated check (006b0ee0)
    if (isSimObjectValid(iSimObjectHandle) != 0)
    {
        // Perform a per-frame update on the sim object (007352b0)
        doSimObjectUpdate();
        
        // Retrieve the current state after update (00b9a1c0)
        int iState = getSimObjectState();
        return iState;
    }
    
    return 0;
}