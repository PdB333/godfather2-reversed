// FUNC_NAME: ActionNode::execute
void __thiscall ActionNode::execute(int *this, int tableBase, int arg)
{
    int state = *this;           // +0x00: current node state (0=idle, 1=pending, 2=active)
    int index = this[1];         // +0x04: index into action table

    if (state == 0)
    {
        // idle state; no action
        return;
    }
    if (state == 1)
    {
        // pending state; check if action is ready (index non-zero)
        if (index == 0)
            return;
        return;
    }
    if (state == 2)
    {
        // active state: dispatch to virtual method
        // Each table entry is 0x14 (20) bytes, offset by (index + 0xC) entries from base
        int entryOffset = (index + 0xC) * 20;
        int *entryBase = (int *)((char *)tableBase + entryOffset);

        int *actionObj = (int *)entryBase[1];   // +0x04 inside entry: pointer to action object
        if (actionObj != NULL)
        {
            int result = 0;
            // Call vtable->+0x2c (11th method) on the action object, passing arg and &result
            (*(void (**)(int, int *))(*(int *)actionObj + 0x2c))(arg, &result);
        }
        return;
    }
    // unknown state: do nothing
}