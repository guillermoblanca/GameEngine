#pragma once
#include "GB.h"
#include "GB/Core.h"

class BatchRenderLayer : public GB::Layer
{
public:

	BatchRenderLayer() : Layer("RenderLayer")
	{

	}
	
	virtual ~BatchRenderLayer() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(TimeStep ts) override;
	virtual void OnEvent(GB::Event& e);

	virtual void OnImguiRender() override;
private:

	std::unique_ptr<GB::Material> m_Material; //shader file
	int m_QuadVA =0;
	int m_QuadVB =0;
	int m_QuadIB =0;
	
	GB::Camera* m_CameraController;
	unsigned int m_BasicTexture, m_SecondTexture;
};