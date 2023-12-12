#pragma once

#include "LogicalDevice.hpp"
#include "SwapChain.hpp"
#include "IcicleWindow.hpp"

// std
#include <cassert>
#include <memory>
#include <vector>

namespace Icicle {
    /*
    * Double buffering is used, see SwapChain::MAX_FRAMES_IN_FLIGHT
    */
    class Renderer {
    public:
        static Renderer* getInstance() {
            if (instancePtr == nullptr) {
                instancePtr = new Renderer();
            }
            return instancePtr;
        }
        void startUp();
        void cleanUp();

        Renderer(const Renderer&) = delete;
        Renderer& operator=(const Renderer&) = delete;

        VkRenderPass getSwapChainRenderPass() const { 
            if (swapChain)
            return swapChain->getRenderPass(); 
            else throw std::runtime_error("swap chain is null in getSwapChainRenderPass");
        }
        float getAspectRatio() const { 
            if (swapChain)
            return swapChain->extentAspectRatio(); 
            else throw std::runtime_error("swap chain is null in getAspectRatio");
        }
        bool isFrameInProgress() const { return isFrameStarted; }

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
            return commandBuffers[currentFrameIndex];
        }

        int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame not in progress");
            return currentFrameIndex;
        }

        VkCommandBuffer beginFrame();
        void endFrame();
        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

    private:
        static Renderer* instancePtr;
        Renderer();
        ~Renderer();
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapChain();

        IcicleWindow* window;
        LogicalDevice* device;
        std::unique_ptr<SwapChain> swapChain;
        std::vector<VkCommandBuffer> commandBuffers;

        uint32_t currentImageIndex;
        int currentFrameIndex{ 0 };
        bool isFrameStarted{ false };
    };
}  // namespace Icicle