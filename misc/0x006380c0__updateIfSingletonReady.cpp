// FUNC_NAME: updateIfSingletonReady
void updateIfSingletonReady( void* pObject )
{
    // Get the singleton instance pointer from the internal getter
    void* pSingleton = getSingletonPointer();

    // Compare with the known global singleton address
    // DAT_00e2a93c likely holds the address of the initialized singleton instance
    if ( pSingleton == &g_initializedSingletonInstance )
    {
        // If the singleton is ready, perform the target operation
        processIfSingletonReady( pObject );
    }
}