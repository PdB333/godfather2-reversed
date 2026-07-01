// FUNC_NAME: EARSFramework::EARSFrameworkObject::EARSFrameworkObject(bool)
EARSFrameworkObject* __thiscall EARSFrameworkObject::EARSFrameworkObject(EARSFrameworkObject* this, bool initialize)
{
    // Calls base initialization routine at 0x008eb7a0 (likely global helper or static init)
    baseInit();

    // If the constructor flag is set, perform additional post-construction setup at 0x009c8eb0
    if (initialize) {
        postConstructInit(this);
    }

    return this;
}