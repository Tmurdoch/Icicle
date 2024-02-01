#pragma once

#include "Camera.hpp"
#include "LogicalDevice.hpp"
#include "GameObject.hpp"
#include "IciclePipeline.hpp"
#include "IcicleTexture.hpp"

// std
#include <memory>
#include <vector>

namespace Icicle {
    class RenderSystem {
    public:
        
        static RenderSystem* getInstance() {
            if (instancePtr == nullptr) {
                instancePtr = new RenderSystem();
            }
            return instancePtr;
        }

        //devicePtr is pointer to singleton class
        void startUp(VkRenderPass renderPass);
        void cleanUp();
        RenderSystem(const RenderSystem&) = delete;
        RenderSystem& operator=(const RenderSystem&) = delete;

        void renderGameObjects(
            VkCommandBuffer commandBuffer,
            std::vector<GameObject>& gameObjects,
            const Camera& camera);

        void renderTextures(
            VkCommandBuffer commandBuffer, 
            std::vector<IcicleTexture>& textures, 
            const Camera& camera);


    private:
        static RenderSystem* instancePtr;
        RenderSystem();
        ~RenderSystem();
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        LogicalDevice* logicalDevice;

        std::unique_ptr<IciclePipeline> pipeline;
        VkPipelineLayout pipelineLayout;
    };
}  // namespace Icicle