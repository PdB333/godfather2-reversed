// FUNC_NAME: SystemNode::registerNode
void SystemNode::registerNode(void)
{
    int result;
    
    // Call the initialization function pointer at offset +0x04
    result = (*(int (*)())(this->initFunc))();
    
    // Store the result of FUN_0060d740 (likely a handle or ID) at offset +0x08
    this->handle = FUN_0060d740(result);
    
    // Call the virtual function at offset +0x10 (e.g., onRegister)
    (*(void (*)())(this->onRegisterFunc))();
    
    // Link this node into the global list: set next to previous head
    this->next = g_headNode;
    
    // Increment global counter and assign unique ID
    g_nodeCounter++;
    g_headNode = this;
    this->nodeId = g_nodeCounter;
}