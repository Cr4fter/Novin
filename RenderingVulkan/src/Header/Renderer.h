#pragma once
#include "IRendering.h"
#include "GlobalStructs.h"
#include "RenderingInternStructs.h"
#include <GLFW/glfw3.h>
#include <set>
#include <iostream>
namespace NV
{
    namespace Rendering
    {
		struct QueueFamilyIndices {
			int GraphicsFamily = -1;
			int PresentFamily = -1;

			bool IsComplete() {
				return GraphicsFamily >= 0 && PresentFamily >= 0;
			}
		};

		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR Capabilites;
			std::vector<VkSurfaceFormatKHR> Formats;
			std::vector<VkPresentModeKHR> PresentModes;
		};

        class Renderer : public IRendering::IRenderer
        {
		private: 
			const std::vector<const char*> validationLayers = {
				"VK_LAYER_LUNARG_standard_validation"
		};

			const std::vector<const char*> deviceExtensions = {
				VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};

			const int MAX_FRAMES_IN_FLIGHT = 2;


#ifdef NDEBUG 
			const bool enableValidationLayers = false;
#else 
			const bool enableValidationLayers = true;
#endif
			VkInstance m_vkInstance;
			VkDebugReportCallbackEXT m_callback;
			GLFWwindow* m_pWnd;
			VkSurfaceKHR m_surface;
			VkPhysicalDevice m_physicalDevice;
			VkDevice m_logicalDevice;
			VkQueue m_graphicsQueue;
			VkQueue m_presentQueue;
		public: 
			/**
			* Initializes the vulkan renderer to be ready to use
			*/
			void Init(GLFWwindow* wnd) override; 
			/**
			* Gets new mesh datas, which will get computed and registered in the renderer. To access them you have to use the index which is the return value
			* @param meshData The raw mesh data includes vertices, indices eg. 
			* @return Returns the index of the overall computed and allocated data which aren't visible from outside of the renderer. 
			*/
			uint32_t GetRawMeshData(NV::IRendering::RawMeshData& meshData) override;
		private: 
			///		---------** The whole init functions for everything before the rendering happens **---------
			/**
			* Initialized the devices which are needed to work with the renderer 
			*/
			void InitDevices();
			/**
			* compute the whole mesh data to allocate the resources of them and create the vertex and index buffer eg. 
			* @param rawMeshData Only the raw mesh datas like vertices and indices without any sort of computed or vulkan dependence.
			*/
			void ComputeMeshData(NV::IRendering::RawMeshData& rawMeshData); 
			/** 
			* Creates the vulkan instance. 
			*/
			void CreateInstance();
			/**
			 * Setup the debug callback 
			 */
			void SetupDebugCallback();
			/**
			 * Creates the window surface to get information.
			 */
			void CreateSurface();
			/**
			 * Picks the most valuable physical device of the current system.
			 */
			void PickPhysicalDevice();
			/** 
			* Creates the logical device of vulkan 
			*/
			void CreateLogicalDevice();


			/// ----------** Everything what happens while the rendering is in process **------------- 
			void CreateSwapChain(); 

			/// ----------** Static functions **----------
			static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallBack(
				VkDebugReportFlagsEXT flags,
				VkDebugReportObjectTypeEXT objType,
				uint64_t obj,
				size_t location,
				int32_t code,
				const char* layerPrefix,
				const char* msg,
				void* userData);
			/// ----------** Proxy Methods **----------------
			VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
			static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);

			/// ----------** Helper functions **-------------------
			/** 
			* Checks if the validation layer is supported
			* @return if the validation layer is supported.
			*/
			bool CheckValidationLayerSupport();
			/**
			 * Returns the required extensions. 
			 * @return the whole required extensions
			 */
			std::vector<const char*> GetRequiredExtensions();
			/**
			 * Checks if the selected device is suitable
			 *@param device The device to check for suitability
			 *@return If it's suitable or not
			 */
			bool IsDeviceSuitable(VkPhysicalDevice device);
			/**
			* Finds queue families of the device
			* @param device The device which should get checked of families
			* @return The indices of the queuefamilies which get found.
			*/
			QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);
			/** 
			* Checks if the device supports the extensions
			* @param device The device to check for support
			* @return If it supports or not
			*/
			bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
			/** 
			* Checks if the device supports query swapchains
			* @param device The device to check for support
			* @return The details of the swapchainsupport
			*/
			SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

        };
    }
}
