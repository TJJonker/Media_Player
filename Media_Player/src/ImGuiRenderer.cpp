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

	// Create a docking layout over the entire viewport
	ImGuiID dockspace_id = ImGui::GetID("DockSpace");
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	static bool oi = true;
	if (oi) {
		oi = false;
		ImGui::DockBuilderRemoveNode(dockspace_id);
		ImGui::DockBuilderAddNode(dockspace_id);

		ImGuiID dock1 = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.5f, nullptr, &dockspace_id);
		ImGuiID dock2 = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.5f, nullptr, &dockspace_id);

		ImGui::DockBuilderDockWindow("Interactive List", dock2);
	}

	ImGui::Begin("Interactive List");

	// Create a scrollable area for the list
	ImVec2 workSize = ImGui::GetMainViewport()->GetWorkCenter();
	ImGui::BeginChild("List", ImVec2(200, workSize.y * 2), true);

	// Define an array to store the state of each checkbox
	static bool itemChecked[10] = { false };

	// Add items to the list with checkboxes
	for (int i = 0; i < 10; i++) {
		ImGui::Checkbox(("Item " + std::to_string(i)).c_str(), &itemChecked[i]);
	}

	// End the scrollable area
	ImGui::EndChild();

	ImGui::End();


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
