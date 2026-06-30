// FUNC_NAME: EntityFactory::createEntityFromTemplate
int EntityFactory::createEntityFromTemplate(int templateId, int userData)
{
    // Retrieve the template data from the resource manager based on templateId
    void* templateData = getResourceManager(templateId);
    if (templateData != nullptr) {
        // Get the global game allocator / world context
        void* worldContext = getWorldAllocator();
        // Allocate the entity using the data pointer at offset +0x08 from the template
        void* entity = allocateEntity(worldContext, *(int*)((char*)templateData + 8), 0, 0, 0);
        if (entity != nullptr) {
            // Store the user-provided data at offset +0x18 (e.g., initialization parameter or callback)
            *(int*)((char*)entity + 0x18) = userData;
            // Return pointer to the sub-structure at offset +0x58 (e.g., the core component)
            return (int)((char*)entity + 0x58);
        }
    }
    return 0;
}