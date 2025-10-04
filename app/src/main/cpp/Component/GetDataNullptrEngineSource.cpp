#include "GetDataNullptrEngineComponent.h"

//Отправка команд из CommandBuffer на выполнение
void GetDataNullptrEngine::CommandSubmit(VkCommandBuffer Buffer, VkQueue Queue, VkFence Fence, VkSemaphore Semaphore, VkSemaphore WaitSemaphore, VkPipelineStageFlags WaitDstStageMask,
                                         uint32_t CommandSubmitCount, uint32_t CommandBufferCount,
                                         uint32_t SemaphoreCount, uint32_t WaitSemaphoreCount)
{
    //Создание информации о отправке
    VkSubmitInfo Info = {
            .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
            .waitSemaphoreCount = WaitSemaphoreCount, //Кол-во ожидающих светофоров
            .pWaitSemaphores = &WaitSemaphore, //Ожидающие светофоры
            .pWaitDstStageMask = &WaitDstStageMask,
            .commandBufferCount = CommandBufferCount, //Кол-во CommandBuffer
            .pCommandBuffers = &Buffer, //Сам CommandBuffer
            .signalSemaphoreCount = SemaphoreCount, //Кол-во светофоров
            .pSignalSemaphores = &Semaphore //Сам светофор
    };
    //Отправка
    vkQueueSubmit(Queue, CommandSubmitCount, &Info, Fence);
}

//Получение экземпляра потока
void GetDataNullptrEngine::GetQueue(VkDevice Device, VkQueue &Queue, uint32_t QueueFamily, uint32_t QueueIndex)
{
    vkGetDeviceQueue(Device, QueueFamily, QueueIndex, &Queue);
}

//Получение формата по параметрам
void GetDataNullptrEngine::GetFormat(VkPhysicalDevice PhysicalDevice, VkSurfaceKHR Surface, VkColorSpaceKHR Color, VkFormat LFormat)
{
    //Получение всех форматов из устройства
    uint32_t FormatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, nullptr);
    vector<VkSurfaceFormatKHR> LFormats(FormatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, LFormats.data());

    //Получение формата по определённым параметрам
    for(VkSurfaceFormatKHR Format : LFormats)
    {
        if(Format.colorSpace == Color && Format.format == LFormat)
        {
            Formats = Format;
            break;
        }
    }
}

//Получение параметров определённого формата
void GetDataNullptrEngine::GetFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkFormatProperties& FormatProperties)
{
    vkGetPhysicalDeviceFormatProperties(PhysicalDevice, Format, &FormatProperties);
}

//Получение параметров формата для изображения по определённым параметрам
void GetDataNullptrEngine::GetImageFormatProperties(VkPhysicalDevice PhysicalDevice, VkFormat Format, VkImageType Type, VkImageTiling Tiling,
                                                                       VkImageUsageFlags Usage, VkImageCreateFlags Flag, VkImageFormatProperties& ImageFormatProperties)
{
    vkGetPhysicalDeviceImageFormatProperties(PhysicalDevice, Format, Type, Tiling, Usage, Flag, &ImageFormatProperties);
}

//Получение параметров памяти устройства
void GetDataNullptrEngine::GetPhysicalDeviceMemoryProperties(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceMemoryProperties& MemoryProperties)
{
    vkGetPhysicalDeviceMemoryProperties(PhysicalDevice, &MemoryProperties);
}

//Получение параметров устройства
void GetDataNullptrEngine::GetPhysicalDeviceProperties(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceProperties& Properties)
{
    vkGetPhysicalDeviceProperties(PhysicalDevice, &Properties);
}

//Получение дополнительных функций из устройства
void GetDataNullptrEngine::GetPhysicalDeviceFeatures(VkPhysicalDevice PhysicalDevice, VkPhysicalDeviceFeatures& Features)
{
    vkGetPhysicalDeviceFeatures(PhysicalDevice, &Features);
}

//Получение под-ресурсов изображения
void GetDataNullptrEngine::GetImageSubresource(VkDevice Device, VkImage Image, VkImageSubresource& Subresource, VkSubresourceLayout& Layout)
{
    vkGetImageSubresourceLayout(Device, Image, &Subresource, &Layout);
}
