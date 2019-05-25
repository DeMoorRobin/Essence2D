#pragma once
#include "BaseComponent.h"
#include <unordered_map>
namespace dae
{
	struct Frame
	{
		float left, bottom, width, height;
	};

	class AnimationRenderComponent final : public BaseComponent
	{
	public:
		AnimationRenderComponent(const std::string& textureFile, float defaultXSize, float defaultYSize);
		~AnimationRenderComponent();
		void AddAnimation(std::vector<Frame>* pAnimation, int id);

		void SetCurrentAnimation(int id, float timePerFrame, int startFrame = 0, bool restartOnSame = false);
		int GetCurrentAnimation() { return m_CurrentAnimation; };
	protected:
		void Initialize() override;
		void Update() override;
	private:
		std::string m_TextureFile;
		float m_DefaultXSize, m_DefaultYSize;
		GLuint m_VertexID, m_ProgramID;
		
		std::unordered_map<int, int> m_IdToAnimMap;
		int m_CurrentFrame, m_CurrentAnimation;
		double m_FrameDuration, m_ElapsedTime;

		std::vector<std::vector<Frame>*> m_pFrames;
	};

}

