#include"CreateObjectNullptrEngineComponent.h"


//Создание изображения Image
void CreateObjectNullptrEngine::CreateImage(VkDevice Device, VkImage& Image, VkImageType Type, VkFormat Format, VkExtent3D Size, uint32_t MipLevel, uint32_t ArrayLayers,
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

    vkCreateImage(Device, &ImageInfo, nullptr, &Image);
}

//Создание буфера Buffer
void CreateObjectNullptrEngine::CreateBuffer(VkDevice Device, VkBuffer& Buffer, VkDeviceSize Size, VkBufferUsageFlagBits Usage, VkSharingMode Mode, uint32_t QueueCount, uint32_t* QueueFamilyIndex)
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

    vkCreateBuffer(Device, &BufferInfo, nullptr, &Buffer);
}

//Создание абстракции для взаимодействия с изображением(Image) ImageView
void CreateObjectNullptrEngine::CreateImageView(VkDevice Device, VkImageView& ImageView, VkImage Image, VkImageViewType Type, VkFormat Format, VkComponentMapping Component, VkImageSubresourceRange Subresource)
{
    VkImageViewCreateInfo ViewInfo = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = Image, //Родительское изображение
            .viewType = Type, //Тип взаимодействия
            .format = Format, //Формат
            .components = Component, //Цветовые компоненты
            .subresourceRange = Subresource //Под-ресурсы
    };

    vkCreateImageView(Device, &ViewInfo, nullptr, &ImageView);
}

void CreateObjectNullptrEngine::CreateBufferView(VkDevice Device, VkBufferView& BufferView, VkBuffer Buffer, VkFormat Format, VkDeviceSize Offset, VkDeviceSize Range)
{
    VkBufferViewCreateInfo BufferViewInfo = {
            .sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO,
            .buffer = Buffer,
            .format = Format,
            .offset = Offset,
            .range = Range
    };

    vkCreateBufferView(Device, &BufferViewInfo, nullptr, &BufferView);
}

