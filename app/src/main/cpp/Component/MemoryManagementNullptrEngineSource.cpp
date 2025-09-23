#include"MemoryManagementNullptrEngineComponent.h"

//Выделения памяти для устройства
VkDeviceMemory MemoryManagementNullptrEngine::SetMemoryDevice(VkDevice Device, uint32_t Size, uint32_t MemoryTypeCount)
{
    VkMemoryAllocateInfo MemoryInfo = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .allocationSize = Size, //Размер памяти
            .memoryTypeIndex = MemoryTypeCount //Кол-во типов памяти по индексу
    };

    VkDeviceMemory Memory = {};

    vkAllocateMemory(Device, &MemoryInfo, nullptr, &Memory);

    return Memory;
}

//Получения информации из памяти
VkDeviceSize MemoryManagementNullptrEngine::GetMemoryDeviceInfo(VkDevice Device, VkDeviceMemory Memory)
{
    VkDeviceSize MemorySize = {};
    vkGetDeviceMemoryCommitment(Device, Memory, &MemorySize);

    return MemorySize;
}

//Очистка памяти CPU от кэша устройства
VkMappedMemoryRange MemoryManagementNullptrEngine::FlushMemoryCPU(VkDevice Device, uint32_t MemoryCount)
{
    VkMappedMemoryRange MemoryRange = {};

    vkFlushMappedMemoryRanges(Device, MemoryCount, &MemoryRange);

    return MemoryRange;
}

//Обновления памяти CPU о кэша устройства
VkMappedMemoryRange MemoryManagementNullptrEngine::UpdateMemoryCPU(VkDevice Device, uint32_t MemoryCount)
{
    VkMappedMemoryRange MemoryRange = {};

    vkInvalidateMappedMemoryRanges(Device, MemoryCount, &MemoryRange);

    return MemoryRange;
}


//Получение требований для памяти от буфера
VkMemoryRequirements MemoryManagementNullptrEngine::GetBufferMemoryRequirements(VkDevice Device, VkBuffer Buffer)
{
    VkMemoryRequirements Memory = {};

    vkGetBufferMemoryRequirements(Device, Buffer, &Memory);

    return Memory;
}

//Получение требований для памяти от изображения
VkMemoryRequirements MemoryManagementNullptrEngine::GetImageMemoryRequirements(VkDevice Device, VkImage Image)
{
    VkMemoryRequirements Memory = {};

    vkGetImageMemoryRequirements(Device, Image, &Memory);

    return Memory;
}

//Осввобождение памяти
void MemoryManagementNullptrEngine::Free(VkDevice Device, VkDeviceMemory Memory)
{
    vkFreeMemory(Device, Memory, nullptr);
}

//Предоставление доступа CPU к памяти устройства
void* MemoryManagementNullptrEngine::MappMemoryCPU(VkDevice Device, VkDeviceMemory Memory, VkDeviceSize Offset, VkDeviceSize Size, VkMemoryMapFlags Flags)
{
    void* Data;
    vkMapMemory(Device, Memory, Offset, Size, Flags, &Data);

    return Data;
}

//Закрытие доступа CPU к памяти устройства
void MemoryManagementNullptrEngine::UnMappMemoryCPU(VkDevice Device, VkDeviceMemory Memory)
{
    vkUnmapMemory(Device, Memory);
}

//Связывание памяти с буфером(в Offest указывается точка памяти для связывания)
void MemoryManagementNullptrEngine::BindBufferMemory(VkDevice Device, VkDeviceMemory Memory, VkBuffer Buffer, VkDeviceSize Offset)
{
    vkBindBufferMemory(Device, Buffer, Memory, Offset);
}

//Связывание памяти с изображением(в Offest указывается точка памяти для связывания)
void MemoryManagementNullptrEngine::BindImageMemory(VkDevice Device, VkDeviceMemory Memory, VkImage Image, VkDeviceSize Offset)
{
    vkBindImageMemory(Device, Image, Memory, Offset);
}