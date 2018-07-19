#pragma once
#include "IRendering.h"
#include "GlobalStructs.h"
#include "RenderingInternStructs.h"
#include <GLFW/glfw3.h>
#include <set>
#include <iostream>

const int WIDTH = 1600;
const int HEIGHT = 800;

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
			/// Devices which need to get initialized before the graphicspipeline can get created
			VkInstance m_vkInstance;
			VkDebugReportCallbackEXT m_callback;
			GLFWwindow* m_pWnd;
			VkSurfaceKHR m_surface;
			VkPhysicalDevice m_physicalDevice;
			VkDevice m_logicalDevice;
			VkQueue m_graphicsQueue;
			VkQueue m_presentQueue;
			VkCommandPool m_commandPool;
			VkDescriptorPool m_descriptorPool;
			/// Handles which are needed to create the graphicspipeline
			VkSwapchainKHR m_swapChain;
			std::vector<VkImage> m_swapChainImages;
			std::vector<VkImageView> m_swapChainImageViews;
			VkFormat m_swapChainImageFormat;
			VkExtent2D m_swapChainExtent;
			VkRenderPass m_renderPass;
			VkPipeline m_graphicsPipeline;
		public: 
			/**
			 * Default Constructor
			 */
			Renderer(); 
			/**
			* Initializes the vulkan renderer to be ready to use
			*/
			void Init(GLFWwindow* wnd) override;	
			/**
			* Gets new mesh datas, which will get computed and registered in the renderer. To access them you have to use the index which is the return value
			* @param meshData The raw mesh data includes vertices, indices eg. 
			* @return Returns the index of the overall computed and allocated data which aren't visible from outside of the renderer. 
			*/
			uint32_t ApplyRawMeshData(NV::IRendering::RawMeshData& meshData) override;
			/**
			 * Releases the whole engine and every part of it
			 */
			void Release() override;
		private: 
			///	    ---------** Functions for the Init method **---------
			/**
			* Initializes the devices which are needed to work with the renderer 
			*/
			void InitDevices();
			/**
			 * Initializes the vulkan features to be ready to use
			 */
			void InitVulkan();
			///		---------** The whole init functions for everything before the rendering happens **---------
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
			/**
			 * Creates the command pool which can be used for commandbuffers
			 */
			void CreateCommandPool();
			/**
			 * Creates the descriptor pool where you can get the available descriptorSets
			 */
			void CreateDescriptorPool();

			/// ----------** Everything what happens while the rendering is in process **------------- 
			/**
			 * Creates the swap chain which is needed for the graphics pipeline
			 */
			void CreateSwapChain();
			/**
			 * Creates the image views for the swap chain
			 */
			void CreateImageViews(); 
			/**
			 * Creates the render passs
			 */
			void CreateRenderPass();
			/**
			 * Creates the graphics pipeline based on the available objects cretaed before
			 */
			void CreateGraphicsPipeline();

			/// ----------** Everything what happens when vulkan gets (partial) released **------------- 

			void Cleanup();

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
			/**
			 * Proxy method to callback debug reports
			 * @param instance The instance of vulkan where you want to get the reports from
			 * @param pCreateInfo Pointer to an create info which defines the information about the creation
			 * @param pAllocator Pointer to the allocator which will allocate the space for the callback
			 * @param pCallBack Pointer to the callback which should receive the debug reports
			 * @return Returns a result of the debug report
			 */
			VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
			/**
			 * static function which destroys a VkDebugReportCallbackEXT object
			 * @param instance The instance where you want to destroy the callback from 
			 * @param callback The callback you want to destroy 
			 * @param pAllocator The allocator where the callback is allocate and where the callback need to get removed from
			 */
			static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);

			/// ----------** Helper functions **-------------------
							/// ***----*** The helper functions to initialize the devices ***-----***
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
						/// ***----*** The helper functions to initialize vulkan to prepare rendering ***-----***
			/** 
			* Checks if the device supports query swapchains
			* @param device The device to check for support
			* @return The details of the swapchainsupport
			*/
			SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
			/**
			 * Chooses the swapchain surface format 
			 * @param availableFormats The formats where to choose from 
			 * @return Returns the best fitting surface format
			 */
			VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats); 
			/**
			 * Chooses the swapchain present mode 
			 * @param availablePresentModes The present modes where to choose from
			 * @return The best fiiting present mode
			 */
			VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			/**
			 * Chooses the swap chain extent 
			 * @param capabilities The capabilites to choose from 
			 * @return The best fitting extent
			 */
			VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
			/**
			 * Creates an Image view
			 * @param image The image which you want to create
			 * @param format The format the image should have at the end
			 * @param aspectFlags The aspectflags for the image
			 * @param mipLevels The mipLevels of the image
			 * @return The created image
			 */
			VkImageView CreateImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
			/**
			 * Finds the current Depth format
			 * @return The depth format which is found
			 */
			VkFormat FindDepthFormat(); 
			/**
			 * Find supported formats
			 * @param candidates A vector of formats as candidates for the supported format
			 * @param tiling The tiling of the format you search for 
			 * @param features The features of the format which have to fit 
			 * @return The format which supports the params.
			 */
			VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        };
    }
}
