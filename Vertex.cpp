#include "Vertex.h"

/**
    A vertex binding describes how to load data from memory, such as bytes between data, rate, how to move to the next entry, etc.
    This is basically how to read a vertex from memory.
*/
VkVertexInputBindingDescription Vertex::getBindingDescription()
{
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;   //Idex of the binding in the array of bindings
    bindingDescription.stride = sizeof(Vertex); //Number of bytes between entries
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; //Move to next entry after each vertex.

    return bindingDescription;
}

/*
    The attribute description describes how to extract the data of each attribute from a vertex.
    This is basically how to read the properties of a vertex (color, pos).
*/
std::array<VkVertexInputAttributeDescription, 2> Vertex::getAttributeDescriptions()
{
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
    
    attributeDescriptions[0].binding = 0;  //from which bindind the data comes. Since it comes from the same binding/buffer, it is 0
    attributeDescriptions[0].location = 0; //Which input of the shader to use
    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT; //Format of the data. Basically means a vec2 (of floats)
    attributeDescriptions[0].offset = offsetof(Vertex, pos); //Byte offset

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(Vertex, color); 

    return attributeDescriptions;
}
