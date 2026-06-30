// FUNC_NAME: Gettable::resolve
void Gettable::resolve(void* this, int* nodeType, int* subNodeType, int depth)
{
    // Prevent infinite recursion due to cycles in the gettable graph
    if (depth > 100)
    {
        FUN_00633920(this, "loop in gettable");
    }

    if (*nodeType != 5)
    {
        // Not the expected node type; delegate to specialized handler
        FUN_00633c30(nodeType, subNodeType, depth + 1);
        return;
    }

    int* valuePtr = nullptr;
    if (*subNodeType == 3)
    {
        // Check if the stored float is an integer (whole number)
        if ((float)(int)(float)subNodeType[1] == (float)subNodeType[1])
        {
            valuePtr = (int*)FUN_00637f10(); // probably allocate or retrieve an integer gettable
        }
        // else fall through to default
    }
    else if (*subNodeType == 4)
    {
        valuePtr = (int*)FUN_00637f90(); // handle type 4
    }
    else
    {
        valuePtr = (int*)FUN_00637ea0(); // default handler for unknown sub-types
    }

    if (valuePtr != nullptr && *valuePtr == 0)
    {
        // The retrieved gettable is empty; continue traversal with next level
        FUN_00633bc0(this, nodeType, subNodeType, depth + 1);
    }
}