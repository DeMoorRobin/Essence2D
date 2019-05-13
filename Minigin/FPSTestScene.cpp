#include "MiniginPCH.h"
#include "FPSTestScene.h"
#include "GameObject.h"
#include "Font.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "GL/glew.h"

FPSTestScene::FPSTestScene()
{
	Initialize();
}


FPSTestScene::~FPSTestScene()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &indexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vertexBuffer);

}

void FPSTestScene::Update()
{
	if (dae::InputManager::GetInstance().GetButton("A"))
	{
		std::cout << "A" << std::endl;
	}
	if (dae::InputManager::GetInstance().GetButtonDown("BDown"))
	{
		std::cout << "BDown" << std::endl;
	}
	if (dae::InputManager::GetInstance().GetButtonUp("XUp"))
	{
		std::cout << "XUp" << std::endl;
	}
}

void FPSTestScene::Draw()
{
	
	glColor3f(1.0f, 0.0f, 0.0f);
	
	glUseProgram(programID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*)0);
	glDisableVertexAttribArray(0);

	//auto er = glGetError();
	//if (GL_INVALID_ENUM != er)
	//{
	//	std::cout << gluErrorString(er) << std::endl;
	//}
}

void FPSTestScene::Initialize()
{
	//dae::GameObject* fpsObject = new dae::GameObject();
	//AddChild(fpsObject);
	//std::cout << sizeof(dae::Texture2D) << std::endl;
	//std::cout << sizeof(dae::RenderComponent) << std::endl;
	////
	////dae::RenderComponent* renderComp = new dae::RenderComponent{};
	//dae::RenderComponent* renderComp = dae::Renderer::GetInstance().RequestRenderComponent();
	//fpsObject->AddRenderComponent(renderComp);
	//
	//renderComp->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("background.jpg"));
	//fpsObject->GetTransform()->Translate(320.0f, 240.0f);
	//fpsObject->GetTransform()->SetScale(0.5f, 1.0f);
	////dae::TextComponent* textComp = new dae::TextComponent{"WOLOLOLO","../Data/Lingua.otf" ,10};
	////fpsObject->AddComponent(textComp);
	////TransformComponent* plop = new TransformComponent{};
	////fpsObject->AddComponent(plop);

	const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   -1.0f, 1.0f, 0.0f,
   0.0f, - 1.0f, 0.0f,
   1.0f,1.0f,0.0f,
   1.0f,-1.0f,0.0f
	};
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	const GLubyte Indices[]
	{
		0,1,2,2,3,4
	};
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	dae::InputManager::GetInstance().Assignbutton("A", dae::ControllerButton::ButtonA);
	dae::InputManager::GetInstance().Assignbutton("BDown", dae::ControllerButton::ButtonB);
	dae::InputManager::GetInstance().Assignbutton("XUp", dae::ControllerButton::ButtonX);
	programID = dae::ResourceManager::GetInstance().LoadShaders("vertexShader.glsl", "pixelShader.glsl");
}