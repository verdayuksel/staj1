#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
#include <vector>
#include <string>

// Kullanıcı verilerini saklamak için yapı
struct User {
    std::string name;
    std::string surname;
    int age;
};

// Global değişkenler
std::vector<User> users;
bool showList = false;
char currentName[128] = "";
char currentSurname[128] = "";
int currentAge = 0;

void error_callback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}

void render(GLFWwindow* window);

int main() {
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    // OpenGL bağlamı için pencere ayarlarını yapın
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL Example", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 150");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        render(window);
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void render(GLFWwindow* window) {
    // Yeni çerçeve başlat
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("KAYIT SİSTEMİ");

    if (showList) {
        // Kayıtlı kullanıcıları göster
        ImGui::Text("KAYITLI KİŞİLER");

        for (size_t i = 0; i < users.size(); ++i) {
            ImGui::Text("%zu. %s %s %d", i + 1, users[i].name.c_str(), users[i].surname.c_str(), users[i].age);
        }

        if (ImGui::Button("Yeni Kayıt")) {
            showList = false; // Yeni kayıt formuna dön
        }
    } else {
        // Kayıt formu
        ImGui::InputText("Ad", currentName, IM_ARRAYSIZE(currentName));
        ImGui::InputText("Soyad", currentSurname, IM_ARRAYSIZE(currentSurname));
        ImGui::InputInt("Yaş", &currentAge);

        if (ImGui::Button("Kayıt Et")) {
            if (currentName[0] != '\0' && currentSurname[0] != '\0' && currentAge > 0) {
                users.push_back({currentName, currentSurname, currentAge});
                std::fill(std::begin(currentName), std::end(currentName), 0);
                std::fill(std::begin(currentSurname), std::end(currentSurname), 0);
                currentAge = 0;
            } else {
                ImGui::Text("Lütfen tüm alanları doldurduğunuzdan emin olun.");
            }
        }

        if (ImGui::Button("Listele")) {
            showList = true; // Kayıtlı kullanıcıları göster
        }
    }

    ImGui::End();

    // Render işlemlerini yap
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
