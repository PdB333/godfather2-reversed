// FUNC_NAME: updateTick
void SomeClass::updateTick(float arg) {
    // Get a value from a math function (possibly easing or random)
    float result = someMathFunc(arg);
    
    // Check bit 0 of flags at offset +0x04
    if ((flags & 1) != 0) {
        result = someMathFunc(result);
        someMathFunc(result);  // call again, ignore return
    }
    
    // Initialize a 48-byte buffer (likely a transform or animation struct)
    // FUN_0059bde0: probably sets default values
    char data48[48];
    initializeBuffer(data48);
    
    // Call virtual functions at vtable offsets 0x10 and 0x1c
    // These likely update internal state based on the buffer
    typedef void (__thiscall *VFunc)(void*, void*);
    char data28[28];
    char data4[4];
    ((VFunc)(vtbl[4]))(this, data28);   // vtable[0x10/4]
    ((VFunc)(vtbl[7]))(this, data4);    // vtable[0x1c/4]
}