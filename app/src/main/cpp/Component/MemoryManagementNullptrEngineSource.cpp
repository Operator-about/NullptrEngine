#include"MemoryManagementNullptrEngineComponent.h"

//Выделения памяти для устройства
void MemoryManagementNullptrEngine::SetMemoryDevice(VkDevice Device, uint32_t Size, uint32_t MemoryTypeCount, VkDeviceMemory& Memory)
{
    VkMemoryAllocateInfo MemoryInfo = {
            .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            .allocationSize = Size, //Размер памяти
            .memoryTypeIndex = MemoryTypeCount //Кол-во типов памяти по индексу
    };


    vkAllocateMemory(Device, &MemoryInfo, nullptr, &Memory);
}

//Получения информации из памяти
void MemoryManagementNullptrEngine::GetMemoryDeviceInfo(VkDevice Device, VkDeviceMemory Memory, VkDeviceSize& ReturnInfo)
{
    vkGetDeviceMemoryCommitment(Device, Memory, &ReturnInfo);
}

//Очистка памяти CPU от кэша устройства
void MemoryManagementNullptrEngine::FlushMemoryCPU(VkDevice Device, uint32_t MemoryCount, VkMappedMemoryRange& Memory)
{
    vkFlushMappedMemoryRanges(Device, MemoryCount, &Memory);
}

//Обновления памяти CPU о кэша устройства
void MemoryManagementNullptrEngine::UpdateMemoryCPU(VkDevice Device, uint32_t MemoryCount, VkMappedMemoryRange& Memory)
{
    vkInvalidateMappedMemoryRanges(Device, MemoryCount, &Memory);
}


//Получение требований для памяти от буфера
void MemoryManagementNullptrEngine::GetBufferMemoryRequirements(VkDevice Device, VkBuffer Buffer, VkMemoryRequirements& MemoryReq)
{
    vkGetBufferMemoryRequirements(Device, Buffer, &MemoryReq);
}

//Получение требований для памяти от изображения
void MemoryManagementNullptrEngine::GetImageMemoryRequirements(VkDevice Device, VkImage Image, VkMemoryRequirements& MemoryReq)
{

    vkGetImageMemoryRequirements(Device, Image, &MemoryReq);

}

//Осввобождение памяти
void MemoryManagementNullptrEngine::Free(VkDevice Device, VkDeviceMemory Memory)
{
    vkFreeMemory(Device, Memory, nullptr);
}

//Предоставление доступа CPU к памяти устройства
void MemoryManagementNullptrEngine::MappMemoryCPU(VkDevice Device, VkDeviceMemory Memory, VkDeviceSize Offset, VkDeviceSize Size, VkMemoryMapFlags Flags, void*& Data)
{
    vkMapMemory(Device, Memory, Offset, Size, Flags, &Data);
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