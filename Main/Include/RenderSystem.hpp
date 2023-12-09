#pragma once

#include "Camera.hpp"
#include "LogicalDevice.hpp"
#include "GameObject.hpp"
#include "IciclePipeline.hpp"

// std
#include <memory>
#include <vector>

namespace Icicle {
    class RenderSystem {
    public:
        RenderSystem();
        ~RenderSystem();

        void startUp(LogicalDevice& device, VkRenderPass renderPass);

        RenderSystem(const RenderSystem&) = delete;
        RenderSystem& operator=(const RenderSystem&) = delete;

        void renderGameObjects(
            VkCommandBuffer commandBuffer,
            std::vector<GameObject>& gameObjects,
            const Camera& camera);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        LogicalDevice& logicalDevice;

        std::unique_ptr<IciclePipeline> pipeline;
        VkPipelineLayout pipelineLayout;
    };
}  // namespace Icicle