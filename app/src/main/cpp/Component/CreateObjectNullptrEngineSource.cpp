#include"CreateObjectNullptrEngineComponent.h"

VkImage CreateObjectNullptrEngine::CreateImage(VkDevice Device, VkImageType Type, VkFormat Format, VkExtent3D Size, uint32_t MipLevel, uint32_t ArrayLayers,
                                               VkSampleCountFlagBits Sample, VkImageTiling Tiling, VkImageUsageFlags Usage, VkSharingMode Mode,
                                               uint32_t QueueCount, uint32_t* QueueFamilyIndex)
{
    VkImageCreateInfo ImageInfo = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .imageType = Type,
            .format = Format,
            .extent = Size,
            .mipLevels = MipLevel,
            .arrayLayers = ArrayLayers,
            .samples = Sample,
            .tiling = Tiling,
            .usage = Usage,
            .sharingMode = Mode
    };

    if(ImageInfo.sharingMode == VK_SHARING_MODE_CONCURRENT)
    {
        ImageInfo.queueFamilyIndexCount = QueueCount;
        ImageInfo.pQueueFamilyIndices = QueueFamilyIndex;
    }

    VkImage Image = {};
    vkCreateImage(Device, &ImageInfo, nullptr, &Image);

    return Image;
}

VkBuffer CreateObjectNullptrEngine::CreateBuffer(VkDevice Device, VkDeviceSize Size, VkBufferUsageFlagBits Usage, VkSharingMode Mode, uint32_t QueueCount, uint32_t* QueueFamilyIndex)
{
    VkBufferCreateInfo BufferInfo = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .size = Size,
            .usage = Usage,
            .sharingMode = Mode,
            .queueFamilyIndexCount = QueueCount,
            .pQueueFamilyIndices = QueueFamilyIndex
    };

    VkBuffer Buffer = {};

    vkCreateBuffer(Device, &BufferInfo, nullptr, &Buffer);

    return Buffer;
}

