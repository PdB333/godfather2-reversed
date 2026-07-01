// FUNC_NAME: initScroll
// Address: 0x00919980 - Initializes a scroll object and logs "InitScroll"
void initScroll(int *outScrollHandle)
{
    // Create the scroll object; FUN_009185a0 likely returns a handle or pointer
    int handle = createScrollObject();
    *outScrollHandle = handle;

    // Log initialization step; FUN_005a04a0 is likely a debug/log function
    // String "InitScroll", zero, pointer to static data, zero
    debugLogInit("InitScroll", 0, &DAT_00d8510c, 0);
}