#pragma once

#include "VulkanUtils.hpp"

namespace Icicle {

    class RenderManager {
    private:
        GLFWwindow* window;
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface; //abstract surface to present images to
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; //graphics card, implicitly destroyed when VkInstance is destroyed
        VkDevice device;//logical device, interfaces with physical device, exposes queue families
        VkQueue graphicsQueue; //implicitly cleaned when device is destroyed
        VkQueue presentQueue; //implicitly cleaned when device is destroyed
        /*
        * series of images (buffers) used for rendering
        * associated with the surface
        * holds queue family indices to be able to synchronize images to the screen and
        * between graphics queue and presentation queue families
        * 
        */
        VkSwapchainKHR swapChain; //synchronize presentation of images with the refresh rate of the screen
        std::vector<VkImage> swapChainImages; //queue of image handles waiting to be presented to screen
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent; //resolution of the swap chain images, almost always exactly equal to the resolution of the window in pixel
        std::vector<VkImageView> swapChainImageViews;
        std::vector<VkFramebuffer> swapChainFramebuffers; //references all VkImageView objects that represent the attachments

        /*
        * render pass stage produces a set of framebuffers, encapsulates both graphics and compute
        * operations. While the graphics pipeline handles low-level operations, render pass defines
        * overall structure of the rendering process, including dependencies and framebuffers. 
        * render pass specifices the pipelines that will be used in each subpass.
        * 
        */
        VkRenderPass renderPass;
        VkDescriptorSetLayout descriptorSetLayout;

        /*
        used to specify uniform values in shaders, globals similar to dynamic state variables,
        can be changes at drawing time
        contains a list of descriptor set layouts*/
        VkPipelineLayout pipelineLayout;

        /*
        describes the configurable state of the graphics card,
        like the viewport size and depth buffer operation and
        the programmable state using VkShaderModule objects.
        */
        VkPipeline graphicsPipeline;

        /*
        Command buffers are allocated from here, manages the memory that
        is used to store the buffers*/
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
        //sets can refer to an array of homogenous resources that can be described with the same layout binding
        //e.g - a set could refer to a texture, making it available to the shader
        std::vector<VkDescriptorSet> descriptorSets; 

        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        /*
        used to synchronize execution, if host needs to know when the GPU has finished something, we use a fence
        e.g - to make sure only one frame is rendering at a time
        signalled when a frame has finished rendering*/
        std::vector<VkFence> inFlightFences;
        uint32_t currentFrame = 0;

        bool framebufferResized = false;

    public:
        static RenderManager& getInstance();
        static RenderManager* instancePtr;
        RenderManager() {}
        ~RenderManager() {}
        
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
            auto app = reinterpret_cast<RenderManager*>(glfwGetWindowUserPointer(window));
            app->framebufferResized = true;
        }

        /*
        * note: used to be main function
        */
        int startUp();

        void run();

        /*
        initializes glfw library
        */
        void initWindow();
        /*
        Window loop
        */
        void mainLoop();
        void cleanup();
        void drawFrame();
        void cleanupSwapChain();
        void recreateSwapChain();
        void initVulkan();
        /**
        initialize vulkan library
        */
        void createInstance();
        /**
        * window: GLFW window pointer
        * vkDestroySurfaceKHR must be called on cleanup
        */
        void createSurface();
        void pickPhysicalDevice();
        void createLogicalDevice();
        /*
        * 
        */
        void createSwapChain();
        void createImageViews();
        /*
        see renderPass member

        create color and depth attachments,
        create subpasses
        specify dependencies
        */
        void createRenderPass();
        void createDescriptorSetLayout();
        /*
        - almost all configuration of gp must be set in advance,
        That means that if you want to switch to a different
        shader or slightly change your vertex layout, then you
        need to entirely recreate the graphics pipeline.
        also means we need to create many of these for each combination
        - loads shaders
        - assigns shaders
        */
        void createGraphicsPipeline();
        /*
        * submits commandPool member on the graphics queue family
        */
        void createCommandPool();
        void createDepthResources();
        /*
        * populates swapChainFramebuffers
        */
        void createFramebuffers();
        void createTextureImage();
        void createTextureImageView();
        void createTextureSampler();
        void createVertexBuffer();
        /*
        * allocates a single command buffer from the command pool
        * these objects are automatically freed when their command pool is destroyed
        */
        void createIndexBuffer();
        void createUniformBuffers();
        void createDescriptorPool();
        void createDescriptorSets();
        void createCommandBuffers();
        /*
        Create GPU semaphores and Fences
        fences created in signalled state so as not to block when calling
        drawFrame
        */
        void createSyncObjects();
        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
        void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
        /*
        * writes commands to be executed on commandBuffer
        * imageIndex: index of the current swapchain image to write to
        */
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        
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
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);


    };

}
