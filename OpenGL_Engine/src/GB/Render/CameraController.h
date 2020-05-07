#pragma once
#include <GB\Render\Camera.h>
#include <GB.h>


namespace GB
{
	class OrthographicCameraController
	{
	public:

		OrthographicCameraController(float aspectRation, bool rotation = false);
		virtual void OnUpdate(float Delta);
		virtual void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }

		void SetZoomLevel(float zoom);
		float GetZoom() const { return m_ZoomLevel; }



	protected:
		virtual void InputControllerSetup(float Delta);

		virtual void OnMouseScrolled(MouseScrolledEvent& e);
		virtual void OnWindowsResized(WindowResizeEvent& e);
	protected:

		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_CameraRotationUpdate; //if the camera is locked or not true = can rotate

		vector3 m_CameraPosition = { 0.0f,0.0f,0.0f };
		float m_CameraRotation = 0.0f; // in degrees.anti-clockwise direction
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
}