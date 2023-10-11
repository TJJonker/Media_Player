#include "pch.h"
#include "ImGuiRenderer.h"
#include <vendor/DearImGUI/imgui.h>
#include <vendor/DearImGUI/imgui_impl_glfw.h>
#include <vendor/DearImGUI/imgui_impl_opengl3.h>
#include <vendor/DearImGUI/imgui_internal.h>

/// <summary>
/// ImGuiRender constructor.
/// </summary>
/// <param name="window">Reference to the GLFWWindow to draw on.</param>
ImGuiRenderer::ImGuiRenderer(GLFWwindow* window)
{
	Initialize(window);
}

/// <summary>
/// ImGuiRenderer destructor.
/// </summary>
ImGuiRenderer::~ImGuiRenderer()
{
	Destroy();
}

/// <summary>
/// Renders the ImGui GUI.
/// </summary>
void ImGuiRenderer::Render()
{
	Begin();

	// Creates a docking space in the viewport.
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

	static const char* dockName = "Dock";
	static bool firsTime = true;
	// Creates a docked layout.
	if(firsTime){
		firsTime = false;
		ImGuiID dockspace_id = ImGui::GetID(dockName); 
		ImGuiViewport* viewport = ImGui::GetMainViewport(); 

		ImGui::DockBuilderRemoveNode(dockspace_id); 
		ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_NoResize | ImGuiDockNodeFlags_NoUndocking); 
		ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size); 

		ImGuiID dock_main = dockspace_id;
		ImGuiID dock_left = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Left, 0.25f, NULL, &dock_main);
		ImGuiID dock_bottom = ImGui::DockBuilderSplitNode(dock_main, ImGuiDir_Down, 0.4f, NULL, &dock_main);

		ImGui::DockBuilderDockWindow("Audio", dock_left); 
		ImGui::DockBuilderDockWindow("Player", dock_main);
		ImGui::DockBuilderDockWindow("Manipulator", dock_bottom);
	}

	static bool open = true;

	// Creates the left sidebar, containing the audio files in the AudioLibrary.
	if (ImGui::Begin("Audio", &open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
		for (unsigned int i = 0; i < m_ListOfAudioNames->size(); i++) {
			if (ImGui::Button((*m_ListOfAudioNames)[i])) {
				m_Channel->AudioName = (*m_ListOfAudioNames)[i];
				m_Channel->PlayNewAudio = true;
			}
			ImGui::Spacing(); 
		}
		ImGui::End();
	}

	// Creates the middle top menu, containing the audio player.
	if (ImGui::Begin("Player", &open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {

		ImGui::Dummy(ImVec2(0, 50));
		const char* audioName = m_Channel->AudioName == "" ? "- Select an audiofile -" : m_Channel->AudioName;
		ImVec2 textSize = ImGui::CalcTextSize(audioName);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - textSize.x) * 0.5f); // Center vertically
		ImGui::Text(audioName);


		const char* playingStopped = !m_Channel->IsPlaying() ? "Stopped" : "Playing...";
		textSize = ImGui::CalcTextSize(playingStopped);
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - textSize.x) * 0.5f); // Center vertically
		ImGui::Text(playingStopped);
		ImGui::Dummy(ImVec2(0, 100));

		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - 350) * 0.5f); // Center vertically
		if (ImGui::BeginTable("Controller", 2)) {
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			if (ImGui::Button("Stop", ImVec2(100, 50))) {
				m_Channel->ShouldStop = true;
			}
			ImGui::TableNextColumn();
			const char* playPauseButtonText = m_Channel->IsPaused ? "Play" : "Pause";
			if (ImGui::Button(playPauseButtonText, ImVec2(100, 50))) {
				m_Channel->IsPaused = !m_Channel->IsPaused;
				m_Channel->PauseChanged = true;
			}
			ImGui::EndTable();
		}
		ImGui::End();
	}
	
	// Creates the middle bottom menu, containing the audio manipulation options.
	if (ImGui::Begin("Manipulator", &open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
		if (ImGui::BeginTable("Manipulation", 2)) {
			ImGui::TableNextRow(); 
			ImGui::TableNextColumn();

			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - 160) * 0.5f); // Center vertically
			ImGui::Text("Volume");
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - 150) * 0.5f); // Center vertically
			if (ImGui::VSliderInt("##Volume", ImVec2(30, 150), &m_Channel->Volume, 0, 100, "%d"))
				m_Channel->HasChanged = true;

			ImGui::TableNextColumn();
		
			ImGui::Text("Pan");
			if (ImGui::SliderFloat("##Pan", &m_Channel->Pan, -1.0f, 1.0f, "%.2f"))
				m_Channel->HasChanged = true;
		
			ImGui::Dummy(ImVec2(0, 30));

			ImGui::Text("Pitch");
			if (ImGui::SliderFloat("##Pitch", &m_Channel->Pitch, 0.0f, 5.0f, "%.2f"))
				m_Channel->HasChanged = true;

			ImGui::EndTable();
			ImGui::End();
		}
	}

	End();
}

/// <summary>
/// Initializes ImGUi.
/// </summary>
/// <param name="window">Reference to the GLFW window.</param>
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

/// <summary>
/// Destroys the ImGUi context.
/// </summary>
void ImGuiRenderer::Destroy()
{
	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

/// <summary>
/// Prepares ImGui for drawing a new frame.
/// </summary>
void ImGuiRenderer::Begin()
{
	// Tell OpenGL a new frame is about to begin
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

/// <summary>
/// Finsishes the ImGui drawing process and renders to the screen.
/// </summary>
void ImGuiRenderer::End()
{	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
