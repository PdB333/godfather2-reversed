// FUNC_NAME: Map::findNode
int* Map::findNode(void)
{
    int keyType = this->field0; // +0x00: key type tag
    int keyValue = this->field1; // +0x04: key value (int or float)

    MapNode* node = (MapNode*)FUN_00637490(); // get head of linked list
    while (node != nullptr)
    {
        if (node->keyType == keyType)
        {
            switch (node->keyType)
            {
            case 0: // integer key
            default:
                if (node->keyValue == keyValue)
                    goto found;
                break;
            case 3: // float key
                if (*(float*)&node->keyValue == *(float*)&keyValue)
                    goto found;
                break;
            }
        }
        node = node->next; // +0x10
    }
    return &DAT_00e2a93c; // sentinel (likely null or special value)

found:
    return &node->data; // +0x08: pointer to stored data
}