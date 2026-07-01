// FUNC_NAME: SimManager::activateModule
void SimManager::activateModule( bool bActivate )
{
    if ( !bActivate )
    {
        // Initialize or reset module
        this->initModule();

        // Get the state manager object
        StateData* pState = this->getStateData();
        if ( pState != nullptr )
        {
            // Only process if state is in range 1 or 2 (active states)
            if ( pState->eState == 1 || pState->eState == 2 )
            {
                // Retrieve global parameter (likely a timer or flag)
                float fParam = getGlobalFloat( 0 );
                // Transition state to 1 with the parameter and extra 0
                pState->setState( 1, fParam, 0 );
            }
        }
    }
    else
    {
        // Deactivate: check if state data exists
        StateData* pState = this->getStateData();
        if ( pState != nullptr )
        {
            // Call stop/deactivate function
            stopModule( 1 );
        }
    }
}