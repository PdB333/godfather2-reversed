// FUNC_NAME: ScriptBinding::getPropertyAccessor

// Function at 0x005ac170: Lazy-initializes property accessor bindings.
// Compares input property name (in_EAX) against known property names and returns
// a cached handle/pointer (likely a function pointer table or descriptor).
// If the binding hasn't been created yet, it allocates 0x50 bytes via a global allocator
// (DAT_0119caf0), initializes it with a specific setter/getter function,
// then calls a post-init function (FUN_0059c690) – possibly for reference counting or GC.
int __cdecl getPropertyAccessor(const char* propertyName)
{
    int result;

    if (__stricmp(propertyName, "setRGB") == 0)
    {
        // DAT_012055ec = cached accessor for setRGB
        if (s_setRgbAccessor == 0)
        {
            result = (*g_allocFunc)(0x50, 0);   // allocate 80 bytes
            if (result == 0)
            {
                s_setRgbAccessor = 0;
            }
            else
            {
                s_setRgbAccessor = createPropertyAccessor(setRgbFunc);   // FUN_005a86f0 with FUN_005bb730
            }
            postInitCleanup();   // FUN_0059c690
        }
        return s_setRgbAccessor;
    }

    if (__stricmp(propertyName, "getRGB") == 0)
    {
        if (s_getRgbAccessor == 0)
        {
            result = (*g_allocFunc)(0x50, 0);
            if (result == 0)
            {
                s_getRgbAccessor = 0;
            }
            else
            {
                s_getRgbAccessor = createPropertyAccessor(getRgbFunc);   // LAB_005bb830
            }
            postInitCleanup();
        }
        return s_getRgbAccessor;
    }

    if (__stricmp(propertyName, "getTransform") == 0)
    {
        if (s_getTransformAccessor == 0)
        {
            result = (*g_allocFunc)(0x50, 0);
            if (result == 0)
            {
                s_getTransformAccessor = 0;
            }
            else
            {
                s_getTransformAccessor = createPropertyAccessor(getTransformFunc);   // LAB_005bb8d0
            }
            postInitCleanup();
        }
        return s_getTransformAccessor;
    }

    if (__stricmp(propertyName, "setTransform") == 0)
    {
        if (s_setTransformAccessor == 0)
        {
            result = (*g_allocFunc)(0x50, 0);
            if (result == 0)
            {
                s_setTransformAccessor = 0;
            }
            else
            {
                s_setTransformAccessor = createPropertyAccessor(setTransformFunc);   // LAB_005bbbb0
            }
            postInitCleanup();
        }
        return s_setTransformAccessor;
    }

    return 0;   // unknown property
}