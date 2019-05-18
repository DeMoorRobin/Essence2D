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
	
	//auto loc = glGetUniformLocation(programID, "tex");
	
	//glActiveTexture(GL_TEXTURE0);
	auto t = dae::ResourceManager::GetInstance().LoadTexture("tileset.png");
	//
	//glUniform1i(loc, 0);
	glUseProgram(programID);
	auto a = glGetError();
	if (a == GL_NO_ERROR) std::cout << "no error\n";

	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, t.GetID());
	auto loc = glGetUniformLocation(programID, "baseImage");
	glUniform1f(loc, 0);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (GLvoid*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, (GLvoid*)12);
	glActiveTexture(GL_TEXTURE0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDrawElements(GL_TRIANGLES, 48*64*6, GL_UNSIGNED_SHORT, (GLvoid*)0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

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


	/*
		2-------3
		|       |
		|       |
		0-------1

	*/
	std::vector<Vertex> vertices{};
	std::vector<GLushort> indices{};
	const GLfloat size{ 10.0f };
	//const int blocks{ 64 * 35 };
	const GLushort height{ 48 };
	const GLushort width{ 64 };
	for (GLushort i{}; i < height; ++i)
	{
		for (GLushort j{}; j < width; ++j)
		{
			Vertex a{};
			a.x = size * j;
			a.y = size * i;
			a.z = 0;
			a.u = 0.0f;
			a.v = 0.0f;

			vertices.push_back(a);

			a.x = size * (j + 1);
			a.y = size * i;
			a.z = 0;
			a.u = 1.0f;
			a.v = 0.0f;
			vertices.push_back(a);
			a.x = size * j;
			a.y = size * (i + 1);
			a.z = 0;
			a.u = 0.0f;
			a.v = 1.0f;
			vertices.push_back(a);
			a.x = size * (j + 1);
			a.y = size * (i + 1);
			a.z = 0;
			a.u = 1.0f;
			a.v = 1.0f;
			vertices.push_back(a);

			indices.push_back(i * width	 * 4 + j * 4);      //0
			indices.push_back(i * width	 * 4 + j * 4 + 2);   //2
			indices.push_back(i * width	 * 4 + j * 4 + 1);   //1
									
			indices.push_back(i * width * 4 + j * 4 + 2); //2
			indices.push_back(i * width * 4 + j * 4 + 3); //3
			indices.push_back(i * width * 4 + j * 4 + 1); //1
		}
	}

	std::cout << sizeof(Vertex) << std::endl;
	//vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	//index buffer
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * indices.size(), indices.data(), GL_STATIC_DRAW);

	

	dae::InputManager::GetInstance().Assignbutton("A", dae::ControllerButton::ButtonA);
	dae::InputManager::GetInstance().Assignbutton("BDown", dae::ControllerButton::ButtonB);
	dae::InputManager::GetInstance().Assignbutton("XUp", dae::ControllerButton::ButtonX);
	programID = dae::ResourceManager::GetInstance().LoadShaders("vertexShader.glsl", "pixelShader.glsl");
}