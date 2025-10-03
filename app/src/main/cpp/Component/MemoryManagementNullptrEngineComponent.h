#ifndef NULLPTRENGINE_MEMORYMANAGEMENTNULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_MEMORYMANAGEMENTNULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
using namespace std;

class MemoryManagementNullptrEngine
{
public:
    void SetMemoryDevice(VkDevice Device, uint32_t Size, uint32_t MemoryTypeCount, VkDeviceMemory& Memory); //Выделение памяти, параметры: устройство, размер, тип памяти по индексу
    void GetMemoryDeviceInfo(VkDevice Device, VkDeviceMemory Memory, VkDeviceSize& ReturnInfo); //Получение информации о памяти устройства, параметры: устройство, память
    //Выдача на стороны CPU доступ к памяти устройства , параметры: устройство, память, отступ по чтению памяти, размер читаемой памяти, флаг
    void MappMemoryCPU(VkDevice Device, VkDeviceMemory Memory, VkDeviceSize Offset, VkDeviceSize Size, VkMemoryMapFlags Flags, void*& Data);
    void UnMappMemoryCPU(VkDevice Device, VkDeviceMemory Memory); //Закрытие на стороне CPU достп к памяти устройства, параметры: устройство, память
    void FlushMemoryCPU(VkDevice Device, uint32_t MemoryCount, VkMappedMemoryRange& Memory); //Очистка на стороне CPU кэша о устройстве
    void UpdateMemoryCPU(VkDevice Device, uint32_t MemoryCount, VkMappedMemoryRange& Memory); //Обновление на стороне CPU кэша о устройстве
    void GetBufferMemoryRequirements(VkDevice Device, VkBuffer Buffer, VkMemoryRequirements& MemoryReq); //Получение требований буфера к памяти, параметры: устройство, буфер
    void GetImageMemoryRequirements(VkDevice Device, VkImage Image, VkMemoryRequirements& MemoryReq); //Получение требований изображений к памяти, параметры: устройство, изображения
    void BindBufferMemory(VkDevice Device, VkDeviceMemory Memory, VkBuffer Buffer, VkDeviceSize Offset); //Привязка буфера к выделенной памяти, параметры: устройство, память, буфер, отступ записи
    void BindImageMemory(VkDevice Device, VkDeviceMemory Memory, VkImage Image, VkDeviceSize Offset); //Привязка изображение к выделенной памяти, параметры: устройство, память, изображение, отступ записи
    void ResetCommandBuffer(VkCommandBuffer Buffer, VkCommandBufferResetFlags Flag, bool SoftReset = false, VkQueue Queue = nullptr); //Сброс CommandBuffer, параметры: Commandbuffer, флаг, аккуратное выключение, поток

    //Сброс CommandPool, параметры: Устройство, CommandPool, флаг, аккуратное выключение, поток
    void ResetCommandPool(VkDevice Device, VkCommandPool Pool, VkCommandPoolResetFlags Flag, bool SoftReset = false, VkQueue Queue = nullptr);
    void Free(VkDevice Device, VkDeviceMemory Memory); //Освобождение выделенной памяти, параметры: устройство, память
};

#endif
