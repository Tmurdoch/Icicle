#include "RenderSystem.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include <iostream>
// std
#include <array>
#include <cassert>
#include <stdexcept>

namespace Icicle {
    RenderSystem::RenderSystem() {};
    RenderSystem* RenderSystem::instancePtr = nullptr;

    struct SimplePushConstantData {
        glm::mat4 transform{ 1.f };
        glm::mat4 modelMatrix{ 1.f };
    };

    void RenderSystem::startUp(VkRenderPass renderPass) {
        this->logicalDevice = LogicalDevice::getInstance(); //singleton
        createPipelineLayout();
        createPipeline(renderPass);
    }

    void RenderSystem::cleanUp() {
        vkDestroyPipelineLayout(logicalDevice->device(), pipelineLayout, nullptr);
    }

    void RenderSystem::createPipelineLayout() {
        VkPushConstantRange pushConstantRange{};
        pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
        pushConstantRange.offset = 0;
        pushConstantRange.size = sizeof(SimplePushConstantData);

        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 1;
        pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;
        if (vkCreatePipelineLayout(logicalDevice->device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) !=
            VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }

    void RenderSystem::createPipeline(VkRenderPass renderPass) {
        assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

        PipelineConfigInfo pipelineConfig{};
        IciclePipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = pipelineLayout;

        pipeline = std::make_unique<IciclePipeline>(
            logicalDevice,
            "../Resources/Shaders/nodescvert.spv",
            "../Resources/Shaders/nodescfrag.spv",
            pipelineConfig);
    }

    void RenderSystem::renderGameObjects(
        VkCommandBuffer commandBuffer,
        std::vector<GameObject>& gameObjects,
        const Camera& camera) {
        pipeline->bind(commandBuffer);

        auto projectionView = camera.getProjection() * camera.getView();

        for (auto& obj : gameObjects) {
            SimplePushConstantData push{};
            auto modelMatrix = obj.transform.mat4();
            push.transform = projectionView * modelMatrix;
            push.modelMatrix = modelMatrix;

            vkCmdPushConstants(
                commandBuffer,
                pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
                0,
                sizeof(SimplePushConstantData),
                &push);

            obj.model->bind(commandBuffer);
            obj.model->draw(commandBuffer);
        }
        gameObjects[0].transform.translation.x += .0001f;
    }

    void RenderSystem::renderTextures(
        VkCommandBuffer commandBuffer,
        std::vector<IcicleTexture>& textures,
        const Camera& camera) {

        

    }

}  // namespace Icicle