// FUNC_NAME: Manager::updateAll
void Manager::updateAll(void)
{
    int* node;

    beginUpdate(); // FUN_005dbc10
    for (node = g_head; node != 0; node = (int*)(node[1])) // +0x4 next pointer
    {
        processNode(node); // FUN_005f1ef0
    }
    endUpdate(); // FUN_005dbc10
    return;
}