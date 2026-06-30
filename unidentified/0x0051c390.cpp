// FUN_NAME: SimManager::enumerateEntitiesByID
void SimManager::enumerateEntitiesByID(int id) { // id passed in EDI register
    Node* node = s_entityList; // DAT_01205514
    if (node != nullptr) {
        do {
            bool match = false;
            if (node->object == nullptr) {
                match = (id == -1);
            } else {
                match = (node->object->getID() == id); // vtable+0xc
            }
            if (match) {
                this->processNode(); // FUN_0051bf80
            }
            node = node->next; // +0x14
        } while (node != nullptr);
    }
}