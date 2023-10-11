#include "pch.h"
#include "ImGuiRenderer.h"
#include <vendor/DearImGUI/imgui.h>
#include <vendor/DearImGUI/imgui_impl_glfw.h>
#include <vendor/DearImGUI/imgui_impl_opengl3.h>
#include <vendor/DearImGUI/imgui_internal.h>

ImGuiRenderer::ImGuiRenderer(GLFWwindow* window)
{
	Initialize(window);
}

ImGuiRenderer::~ImGuiRenderer()
{
	Destroy();
}

void ImGuiRenderer::Render()
{
	Begin();

	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	//static bool open = true;

	static const char* dockName = "De";
	static bool thing = true;
	//if (ImGui::DockBuilderGetNode(ImGui::GetID(dockName)) == NULL) {
	if(thing){
		thing = false;
		ImGuiID dockspace_id = ImGui::GetID(dockName); 
		ImGuiViewport* viewport = ImGui::GetMainViewport(); 

		ImGui::DockBuilderRemoveNode(dockspace_id); 
		ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_NoUndocking); 
		ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size); 

		ImGuiID dock_main = dockspace_id;
		ImGuiID dock_left = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Left, 0.3f, NULL, &dock_main);
		ImGuiID dock_bottom = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Down, 0.4f, NULL, &dock_main);

		ImGui::DockBuilderDockWindow("Left", dock_left); 
		ImGui::DockBuilderDockWindow("Main", dock_main);
		ImGui::DockBuilderDockWindow("Bottom", dock_bottom);
	}

	ImGui::Begin("Left");
	ImGui::Text("Left");
	ImGui::End();

	ImGui::Begin("Main");
	ImGui::Text("Main");
	ImGui::End();

	ImGui::Begin("Bottom");

	if (ImGui::BeginTable("Manipulation", 2)) {
		ImGui::TableNextRow(); 
		ImGui::TableNextColumn();

		// Vertical slider 1
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - 160) * 0.5f); // Center vertically
		ImGui::Text("Volume");
		int volume = 50;
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - 150) * 0.5f); // Center vertically
		ImGui::VSliderInt("##Volume", ImVec2(30, 150), &volume, 0, 100, "%d");

		ImGui::TableNextColumn();
		
		// Vertical slider 2
		ImGui::Text("Pan");
		float Pan = 0.f;
		ImGui::SliderFloat("##Pan", &Pan, -1.0f, 1.0f, "%.2f");
		
		ImGui::Dummy(ImVec2(0, 30));

		// Horizontal knob-style slider
		ImGui::Text("Pitch");
		float Pitch = 0.f;
		ImGui::SliderFloat("##Pitch", &Pitch, -1.0f, 1.0f, "%.2f");

		ImGui::EndTable();
		ImGui::End();
	}

	End();
}

void ImGuiRenderer::Initialize(GLFWwindow* window)
{
    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

void ImGuiRenderer::Destroy()
{
	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiRenderer::Begin()
{
	// Tell OpenGL a new frame is about to begin
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiRenderer::End()
{	// Renders the ImGUI elements
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
