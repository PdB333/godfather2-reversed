// FUNC_NAME: ClassWithProperties::registerReflectionProperties
void __fastcall ClassWithProperties::registerReflectionProperties(int thisPtr)
{
    // Register property at offset +0x1c with callback at 0x0092a150
    registerPropertyWithCallback(&typeDescriptorA, thisPtr + 0x1c, &onProperty0x1cChanged, 0, 0);

    // Register property at offset +0x20 (no callback, flags 0,0,1,1)
    registerPropertyWithFlags(&typeDescriptorB, thisPtr + 0x20, 0, 0, 1, 1);

    // Register property at offset +0x24 (no callback, flag 1)
    registerPropertyWithCallback(&typeDescriptorC, thisPtr + 0x24, 0, 0, 1);

    // Register property at offset +0x28 (no callback, flags 0,0,1,1)
    registerPropertyWithFlags(&typeDescriptorD, thisPtr + 0x28, 0, 0, 1, 1);

    // Register property at offset +0x2c (no callback, flag 1)
    registerPropertyWithCallback(&typeDescriptorE, thisPtr + 0x2c, 0, 0, 1);

    // Register property at offset +0x30 with callback at 0x00929e80
    registerPropertyWithCallback(&typeDescriptorF, thisPtr + 0x30, &onProperty0x30Changed, 0, 0);

    // Register property at offset +0x34 (no callback, flag 1)
    registerPropertyWithCallback(&typeDescriptorG, thisPtr + 0x34, 0, 0, 1);

    // Register property at address 0x011304f4 (not offset) with callback at 0x0092a160
    registerPropertyWithCallback(&typeDescriptorH, &externalDataRef, &onExternalProperty, 0, 0);

    // Register property at offset +0x44 (no callback, flag 1)
    registerPropertyWithCallback(&typeDescriptorI, thisPtr + 0x44, 0, 0, 1);

    // Register property at offset +0x48 (no callback, flag 1)
    registerPropertyWithCallback(&typeDescriptorJ, thisPtr + 0x48, 0, 0, 1);

    // Finalize reflection registration
    finalizeRegistration();
}