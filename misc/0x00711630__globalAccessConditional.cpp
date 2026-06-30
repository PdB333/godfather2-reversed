// FUNC_NAME: globalAccessConditional
int globalAccessConditional(int condition)
{
    // if condition is non-zero, call helper with a known global pointer
    if (condition != 0)
    {
        return sub_43b870(g_SomeGlobal);
    }
    return 0;
}