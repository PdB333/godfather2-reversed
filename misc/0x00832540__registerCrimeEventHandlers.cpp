// FUNC_NAME: registerCrimeEventHandlers
void registerCrimeEventHandlers(void)
{
    int objectPtr;
    
    objectPtr = createObject(0xdc); // Allocate 220 bytes for some object
    if (objectPtr != 0) {
        initObjectType1(); // Initialize first object type
    }
    objectPtr = createObject(0x10); // Allocate 16 bytes for another object
    if (objectPtr != 0) {
        initObjectType2(); // Initialize second object type
    }
    
    // Register default event handlers for various crime/event hashes
    registerEventHandler(0xe0cfae4b, &defaultEventHandler); // Hash: e0cfae4b
    registerEventHandler(0xd0f12e8, &defaultEventHandler);  // Hash: 0d0f12e8
    registerEventHandler(0x84f8c155, &defaultEventHandler); // Hash: 84f8c155
    registerEventHandler(0x82222d2e, &defaultEventHandler); // Hash: 82222d2e
    registerEventHandler(0xda70156a, &defaultEventHandler); // Hash: da70156a
    registerEventHandler(0xab1b850, &specialEventHandler);  // Hash: ab1b850 (special handler)
    registerEventHandler(0x679dc961, &defaultEventHandler); // Hash: 679dc961
    registerEventHandler(0xe4599969, &defaultEventHandler); // Hash: e4599969
    registerEventHandler(0xe113a0f7, &defaultEventHandler); // Hash: e113a0f7
    registerEventHandler(0xf979ebb6, &defaultEventHandler); // Hash: f979ebb6
    registerEventHandler(0xd904c420, &defaultEventHandler); // Hash: d904c420
    registerEventHandler(0x6fba74fa, &defaultEventHandler); // Hash: 6fba74fa
    registerEventHandler(0xee204f17, &defaultEventHandler); // Hash: ee204f17
    registerEventHandler(0x990e4555, &defaultEventHandler); // Hash: 990e4555
    
    // Register specific event callbacks (override defaults)
    registerEventCallback(0xe0cfae4b, &eventHandler_0xe0cfae4b); // Specific handler for hash e0cfae4b
    registerEventCallback(0xd0f12e8, &eventHandler_0xd0f12e8);   // Specific handler for hash 0d0f12e8
    registerEventCallback(0x84f8c155, &eventHandler_0x84f8c155); // Specific handler for hash 84f8c155
    registerEventCallback(0x82222d2e, &eventHandler_0x82222d2e); // Specific handler for hash 82222d2e
    registerEventCallback(0xda70156a, &eventHandler_0xda70156a); // Specific handler for hash da70156a
    registerEventCallback(0x679dc961, &eventHandler_0x679dc961); // Specific handler for hash 679dc961
    registerEventCallback(0xe4599969, &eventHandler_0xe4599969); // Specific handler for hash e4599969
    registerEventCallback(0xe113a0f7, &eventHandler_0xe113a0f7); // Specific handler for hash e113a0f7
    registerEventCallback(0xf979ebb6, &eventHandler_0xf979ebb6); // Specific handler for hash f979ebb6
    registerEventCallback(0xd904c420, &eventHandler_0xd904c420); // Specific handler for hash d904c420
    registerEventCallback(0x6fba74fa, &eventHandler_0x6fba74fa); // Specific handler for hash 6fba74fa
    registerEventCallback(0xee204f17, &eventHandler_0xee204f17); // Specific handler for hash ee204f17
    registerEventCallback(0x990e4555, &eventHandler_0x990e4555); // Specific handler for hash 990e4555
    
    return;
}