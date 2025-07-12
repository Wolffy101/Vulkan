#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan.h>

class VulkanApp
{
  public:
    void run()
    {
        initWindow();
        initVulkan();
        std::cout << "Vulkan initialized successfully through C++ interface!" << std::endl;
        cleanup();
    }

  private:
    GLFWwindow *window;

    void initWindow()
    {
        if (!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // 禁用 OpenGL
        window = glfwCreateWindow(800, 600, "Vulkan C++ App", nullptr, nullptr);
        if (!window)
            throw std::runtime_error("Failed to create GLFW window");
    }

    void initVulkan()
    {
        VkInstance instance;
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "LearnVK";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        std::vector<const char *> extensions;
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        for (uint32_t i = 0; i < glfwExtensionCount; i++)
        {
            extensions.push_back(glfwExtensions[i]);
        }

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
            throw std::runtime_error("Failed to create Vulkan instance");

        vkDestroyInstance(instance, nullptr); // 清理资源（这里只是验证初始化）
    }

    void cleanup()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main()
{
    try
    {
        VulkanApp app;
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
