#include"CreateObjectNullptrEngineComponent.h"


//Создание изображения Image
VkImage CreateObjectNullptrEngine::CreateImage(VkDevice Device, VkImageType Type, VkFormat Format, VkExtent3D Size, uint32_t MipLevel, uint32_t ArrayLayers,
                                               VkSampleCountFlagBits Sample, VkImageTiling Tiling, VkImageUsageFlags Usage, VkSharingMode Mode,
                                               uint32_t QueueCount, uint32_t* QueueFamilyIndex)
{
    VkImageCreateInfo ImageInfo = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
            .imageType = Type, //Тип изображения
            .format = Format, //Формат
            .extent = Size, //Размер
            .mipLevels = MipLevel, //Уровень в пирамиде
            .arrayLayers = ArrayLayers, //Слой
            .samples = Sample, //Сглаживание изображения
            .tiling = Tiling, //Метод размещения
            .usage = Usage, //Сценарий использоввания
            .sharingMode = Mode //Режим взаимодействия
    };

    /*
     * Вслучаи если sharingMode равняется VK_SHARING_MODE_CONCURRENT,
     * то нужно обязательно указать: кол-во потоков и сами потоки
     */
    if(ImageInfo.sharingMode == VK_SHARING_MODE_CONCURRENT)
    {
        ImageInfo.queueFamilyIndexCount = QueueCount; //Назначение кол-во потоков
        ImageInfo.pQueueFamilyIndices = QueueFamilyIndex; //Назначение потоков
    }

    VkImage Image = {};
    vkCreateImage(Device, &ImageInfo, nullptr, &Image);

    return Image;
}

//Создание буфера Buffer
VkBuffer CreateObjectNullptrEngine::CreateBuffer(VkDevice Device, VkDeviceSize Size, VkBufferUsageFlagBits Usage, VkSharingMode Mode, uint32_t QueueCount, uint32_t* QueueFamilyIndex)
{
    VkBufferCreateInfo BufferInfo = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
            .size = Size, //Размер
            .usage = Usage, //Сценарий использования
            .sharingMode = Mode, //Режим взаимодействия
    };

    /*
     * Вслучаи если sharingMode равняется VK_SHARING_MODE_CONCURRENT,
     * то нужно обязательно указать: кол-во потоков и сами потоки
     */
    if(BufferInfo.sharingMode == VK_SHARING_MODE_CONCURRENT)
    {
        BufferInfo.queueFamilyIndexCount = QueueCount; //Назначение кол-во потоков
        BufferInfo.pQueueFamilyIndices = QueueFamilyIndex; //Назначение потоков
    }

    VkBuffer Buffer = {};

    vkCreateBuffer(Device, &BufferInfo, nullptr, &Buffer);

    return Buffer;
}

//Создание абстракции для взаимодействия с изображением(Image) ImageView
VkImageView CreateObjectNullptrEngine::CreateImageView(VkDevice Device, VkImage Image, VkImageViewType Type, VkFormat Format, VkComponentMapping Component, VkImageSubresourceRange Subresource)
{
    VkImageViewCreateInfo ViewInfo = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = Image, //Родительское изображение
            .viewType = Type, //Тип взаимодействия
            .format = Format, //Формат
            .components = Component, //Цветовые компоненты
            .subresourceRange = Subresource //Под-ресурсы
    };

    VkImageView ImageView = {};

    vkCreateImageView(Device, &ViewInfo, nullptr, &ImageView);

    return ImageView;
}

VkBufferView CreateObjectNullptrEngine::CreateBufferView(VkDevice Device, VkBuffer Buffer, VkFormat Format, VkDeviceSize Offset, VkDeviceSize Range)
{
    VkBufferViewCreateInfo BufferViewInfo = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO,
            .buffer = Buffer,
            .format = Format,
            .offset = Offset,
            .range = Range
    };

    VkBufferView BufferView = {};

    vkCreateBufferView(Device, &BufferViewInfo, nullptr, &BufferView);

    return BufferView;
}

