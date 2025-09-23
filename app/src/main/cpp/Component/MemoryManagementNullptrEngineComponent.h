#ifndef NULLPTRENGINE_MEMORYMANAGEMENTNULLPTRENGINECOMPONENT_H
#define NULLPTRENGINE_MEMORYMANAGEMENTNULLPTRENGINECOMPONENT_H

#include<vulkan/vulkan.h>
#include<vulkan/vulkan_android.h>
#include<iostream>
using namespace std;

class MemoryManagementNullptrEngine
{
public:
    VkDeviceMemory SetMemoryDevice(VkDevice Device, uint32_t Size, uint32_t MemoryTypeCount); //Выделение памяти, параметры: устройство, размер, тип памяти по индексу
    VkDeviceSize GetMemoryDeviceInfo(VkDevice Device, VkDeviceMemory Memory); //Получение информации о памяти устройства, параметры: устройство, память
    //Выдача на стороны CPU доступ к памяти устройства , параметры: устройство, память, отступ по чтению памяти, размер читаемой памяти, флаг
    void* MappMemoryCPU(VkDevice Device, VkDeviceMemory Memory, VkDeviceSize Offset, VkDeviceSize Size, VkMemoryMapFlags Flags);
    void UnMappMemoryCPU(VkDevice Device, VkDeviceMemory Memory); //Закрытие на стороне CPU достп к памяти устройства, параметры: устройство, память
    VkMappedMemoryRange FlushMemoryCPU(VkDevice Device, uint32_t MemoryCount); //Очистка на стороне CPU кэша о устройстве
    VkMappedMemoryRange UpdateMemoryCPU(VkDevice Device, uint32_t MemoryCount); //Обновление на стороне CPU кэша о устройстве
    VkMemoryRequirements GetBufferMemoryRequirements(VkDevice Device, VkBuffer Buffer); //Получение требований буфера к памяти, параметры: устройство, буфер
    VkMemoryRequirements GetImageMemoryRequirements(VkDevice Device, VkImage Buffer); //Получение требований изображений к памяти, параметры: устройство, изображения
    void BindBufferMemory(VkDevice Device, VkDeviceMemory Memory, VkBuffer Buffer, VkDeviceSize Offset); //Привязка буфера к выделенной памяти, параметры: устройство, память, буфер, отступ записи
    void BindImageMemory(VkDevice Device, VkDeviceMemory Memory, VkImage Image, VkDeviceSize Offset); //Привязка изображение к выделенной памяти, параметры: устройство, память, изображение, отступ записи
    void Free(VkDevice Device, VkDeviceMemory Memory); //Освобождение выделенной памяти, параметры: устройство, память
};

#endif
