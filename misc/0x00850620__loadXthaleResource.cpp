// FUNC_NAME: loadXthaleResource
int __cdecl loadXthaleResource(int param_1)
{
    int object;
    int component;

    logMessage("XTHALE1387_C90A01A_DA2FB58_v3");
    object = findObjectByHash(0xfe16702f);
    if (object != 0) {
        setObjectData(object, 0x40, param_1);
        component = getComponent(object);
        if (component != 0) {
            setComponentEnabled(component, 0);
        }
    }
    return object;
}