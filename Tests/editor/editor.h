/**
 * 
 * For general confusion: 
 * https://vulkan-tutorial.com/en/Overview
*/


#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h> //includes vulkan.h 

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_resize.h"
#include "stb_image_write.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <chrono>
#include <vector>
#include <cstring>
#include <cstdlib> ///provides the EXIT_SUCCESS and EXIT_FAILURE macros.
#include <cstdint>
#include <limits>
#include <array>
#include <optional>
#include <set>
#include <map>

#include <stdio.h>
#include <stdlib.h>


const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}


/*
* Must be called before vulkan instance is destroyed
*/
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    //specifies the color channels and types
    std::vector<VkSurfaceFormatKHR> formats;
    //represents conditions for showing images to the screen, four possible modes
    std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};

struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};

const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4
}; 


class Editor {
private:
    GLFWwindow* window;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    //abstract surface to present images to
    VkSurfaceKHR surface;

    //graphics card, implicitly destroyed when VkInstance is destroyed
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    // logical device
    VkDevice device;

    //implicitly cleaned when device is destroyed
    VkQueue graphicsQueue;
    //implicitly cleaned when device is destroyed
    VkQueue presentQueue;

    //synchronize presentation of images with the refresh rate of the screen
    VkSwapchainKHR swapChain;
    //queue of image handles waiting to be presented to screen
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    //resolution of the swap chain images, almost always exactly equal to the resolution of the window in pixel
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    /*
    describe the type of images that are used during rendering
    operations, how they will be used, and how their contents 
    should be treated*/
    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;

    /*
    see graphics pipeline*/
    VkPipelineLayout pipelineLayout;

    /*
    describes the configurable state of the graphics card, 
    like the viewport size and depth buffer operation and 
    the programmable state using VkShaderModule objects.
    */
    VkPipeline graphicsPipeline;

    /*
    Command buffers are allocated from here*/
    VkCommandPool commandPool;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    /*
    */
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    uint32_t currentFrame = 0;

    bool framebufferResized = false;

public:
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        auto app = reinterpret_cast<Editor*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }
    
    
    void run();
    /*
     * initializes glfw library
    */
    void initWindow();
    /*
    Window loop
    */
    void mainLoop();
    void cleanup();
    /*
    */
    void drawFrame();
    void cleanupSwapChain();
    void recreateSwapChain();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();


    /*
    * create swap chain
    * 
    */
    void initVulkan();
    /*
    initialize vulkan library*/
    void createInstance();
    void setupDebugMessenger();
    /*
    * window: GLFW window pointer
    * vkDestroySurfaceKHR must be called on cleanup
    * 
    */
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createDescriptorSetLayout();
    /*
    almost all configuration of gp must be set in advance, 
    That means that if you want to switch to a different
     shader or slightly change your vertex layout, then you 
     need to entirely recreate the graphics pipeline.
    also means we need to create many of these for each combination
    * loads shaders
    * assigns shaders
    */
    void createGraphicsPipeline();
    void createCommandPool();
    void createDepthResources();
    void createFramebuffers();
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();
    void createVertexBuffer();
    void createIndexBuffer();
    void createUniformBuffers();
    void createDescriptorPool();
    void createDescriptorSets();
    void createCommandBuffers();
    void createSyncObjects();
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

    bool checkValidationLayerSupport();
    bool hasStencilComponent(VkFormat format);
    /*
    need an extension to interface with the window system, also 
    provides abstract surface extension (instance level)
    */
    std::vector<const char*> getRequiredExtensions();
    bool isDeviceSuitable(VkPhysicalDevice device);
    /*
    * find which queue families are supported by physical device
    * returns a struct that contains the queue families
    */
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    /*
    * check if swap chain is compatible with window surface
    * (basic compatibilities, surface formats, and available presentation modes)
    */
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void updateUniformBuffer(uint32_t currentImage);
    /*
    * code: buffer containing bytecode
    * 
    */
    VkShaderModule createShaderModule(const std::vector<char>& code);
    /*
    * VkSurfaceFormatKHR entry contains a format and colorSpace member
    * format specifies color channels and types
    * colorspace indicates if the SRGB color space is supported or not
    * 
    * if available format is not supported will choose the next found one
    */
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    /*
    * only FIFO mode is guaranteed, but looks for mailbox and returns FIFO
    * if not found
    */
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    /*
    * give each device a score, favouring dedicated graphcis card and higher
    * maximum possible texture size
    */
    int rateDeviceSuitability(VkPhysicalDevice device);

    /*
    * returns std::vector<char> buffer of bytecode
    */
    static std::vector<char> readFile(const std::string& filename) {
        //"ate" : start reading at end of file so that we can use the read position to determine the size of the file and allocate a buffer
        std::ifstream file(filename, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        //seek back to beginning and start read
        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        return buffer;
    }


    /*
    * messageSeverity: could be one of four flags (verbose, info, warning or error), see vulkan validation layer docs
    * messageType: can be one of 3 flags (general, validation, performance)
    * pCallbackData: refers to a VkDebugUtilsMessengerCallbackDataEXT struct containing details of the message
    * pUserData: allows for passing of data
    * 
    * Returns: bool indicating if the vulkan call that triggered the validation layer message should be aborted,
    * usually only used to test validation layers themselves
    */
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

};
