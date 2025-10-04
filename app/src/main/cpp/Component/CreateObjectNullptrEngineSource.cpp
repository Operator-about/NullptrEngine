#include"CreateObjectNullptrEngineComponent.h"

//Запись изображения
void CreateObjectNullptrEngine::WriteImage(VkCommandBuffer Buffer, VkCommandBufferUsageFlags Flag, VkBuffer ResourceBuffer, VkImage TargetImage,
                                           VkImageLayout TargetLayerImage,
                                           uint32_t Regions, VkDeviceSize BufferOffset, uint32_t BufferRowLength, uint32_t BufferImageHeight, VkImageSubresourceLayers Subresource, VkOffset3D ImageOffset,
                                           VkExtent3D ImageSize)
{
    //Создание информации для начала записи в буфер
    VkCommandBufferBeginInfo Info = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .flags = Flag, //Флаг о том, сколько раз будет использован буфер
    };

    //Начало записи...
    vkBeginCommandBuffer(Buffer, &Info);

    //Границы региона записи
    VkBufferImageCopy Copy = {
        .bufferOffset = BufferOffset, //Точка в CommandBuffer
        .bufferRowLength = BufferRowLength, //Длина рядов в CommandBuffer
        .bufferImageHeight = BufferImageHeight, //Высота изображения в CommandBuffer
        .imageSubresource = Subresource, //Под-ресурсы изображения
        .imageOffset = ImageOffset, //Начало изображения
        .imageExtent = ImageSize //Размер изображения
    };
    //Запись
    vkCmdCopyBufferToImage(Buffer, ResourceBuffer, TargetImage, TargetLayerImage, Regions, &Copy);

    //Конец ззаписи
    vkEndCommandBuffer(Buffer);
}

//Запись команд в командный буфер
void CreateObjectNullptrEngine::WriteCommandBuffer(VkCommandBuffer Buffer, VkCommandBufferUsageFlags Flag, VkBuffer ResourceBuffer, VkBuffer TargetBuffer, uint32_t Regions,
                                                   VkDeviceSize ResourceOffset, VkDeviceSize TargetOffset, VkDeviceSize Size)
{
    //Создание информации для начала записи в буфер
    VkCommandBufferBeginInfo Info = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
            .flags = Flag, //Флаг о том, сколько раз будет использован буфер
    };

    //Начало записи...
    vkBeginCommandBuffer(Buffer, &Info);

    //Границы региона копирования
    VkBufferCopy Copy = {
            .srcOffset = ResourceOffset, //Точка начала копирования из ResourceBuffer
            .dstOffset = TargetOffset, //Точка начала вставления в TargetBuffer
            .size = Size //Размер данных для копирования
    };
    //Запись...
    vkCmdCopyBuffer(Buffer, ResourceBuffer, TargetBuffer, Regions, &Copy);

    //Завершение записи
    vkEndCommandBuffer(Buffer);
}

//Выделение комадного буфера из Pool
void CreateObjectNullptrEngine::AllocationCommandBuffer(VkDevice Device, VkCommandBuffer& Buffer, VkCommandPool Pool, VkCommandBufferLevel Level, uint32_t Count)
{

    //Создание информации о выделение
    VkCommandBufferAllocateInfo Info = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .commandPool = Pool, //Указание Pool
            .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY, //Указание уровня командного буфера
            .commandBufferCount = Count //Кол-во
    };

    //Выделение
    vkAllocateCommandBuffers(Device, &Info, &Buffer);
}


//Создание CommandPool
void CreateObjectNullptrEngine::CreateCommandPool(VkDevice Device, uint32_t QueueFamily, VkCommandPoolCreateFlags Flag, VkCommandPool& Pool)
{
    //Создание информации о CommandPool
    VkCommandPoolCreateInfo Info = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags = Flag, //Флаг
            .queueFamilyIndex = QueueFamily //Потоки
    };

    //Создание
    vkCreateCommandPool(Device, &Info, nullptr, &Pool);
}


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

