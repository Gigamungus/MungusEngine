#pragma once
#include "stdafx.h"

namespace Mungus {
	class Renderer;
	class World;

	struct ActiveBindings;
	struct CursorLocation;

	class MUNGUS Application {
	private:
		void inline incrementFrameCount(void);
		void renderActors(void);
		void keyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods);
		void mouseCallBack(GLFWwindow* window, int button, int action, int mods);
		void cursorCallBack(GLFWwindow* window, double xpos, double ypos);
		void updateCameraPosition(void);
		void updateMouseLocation(void);

	protected:
		std::shared_ptr<Mungus::World> world;
		std::shared_ptr<Mungus::Renderer> renderer;
		std::shared_ptr<ActiveBindings> bindings;
		std::shared_ptr<CursorLocation> lastMouseLocation;

	public:
		Application(void);
		virtual ~Application();
		
		void run(void);


		///////////// client can call these ///////////////
		void setRPGBindings(void);
		const float time(void) const;
		const float frameTime(void) const;
		const unsigned long frameCount(void) const;
		const CursorLocation getLastMouseLocation(void) const;
		void inline loadAsset(const std::string& assetPath);
		void inline setBackground(MungusMath::MVec4 color);
		const unsigned long inline createEntity(const std::string& name);
		const unsigned long setEntityPosition(const unsigned long id, float x, float y, float z);
		const unsigned long scaleEntity(const unsigned long id, float x, float y, float z);
		const unsigned long rotateEntity(const unsigned long id, const MungusMath::MVec3& axis, float angle);
		const unsigned long turnEntity(const unsigned long id, float angle);
		const unsigned long pitchEntity(const unsigned long id, float angle);
		const unsigned long rollEntity(const unsigned long id, float angle);

			////////////////// camera functions/////////////
			const MungusMath::MVec3 getCameraPosition(void) const;
			void setCameraPosition(float x, float y, float z);
			void moveCamera(const MungusMath::MVec3& moveBy);

			const MungusMath::MVec3 getCameraForward(void) const;
			const MungusMath::MVec3 getCameraUp(void) const;
			const MungusMath::MVec3 getCameraRight(void) const;
			const MungusMath::MVec3 getCameraPlanarForward(void) const;
			const MungusMath::MVec3 getCameraPlanarUp(void) const;
			const MungusMath::MVec3 getCameraPlanarRight(void) const;
			void rotateCamera(const MungusMath::MVec3& axis, float theta);
			void turnCamera(float angle);
			void pitchCamera(float angle);
			void rollCamera(float angle);

			inline const float getCameraRotationSpeed(void) const;
			inline void setCameraRotationSpeed(float speed);
			
			inline const float getCameraMovementSpeed(void) const;
			inline void setCameraMovementSpeed(float speed);

			void setCameraStrafingStatus(int setting);
			void setCameraAscendingStatus(int setting);
			void setCameraAdvancingStatus(int setting);
			void setCameraTurningStatus(int setting);
			void setCameraPitchingStatus(int setting);
			void setCameraRollingStatus(int setting);
			//////////// end camera functions /////////////

		////////////////// end client call functions //////////////////

		//////// client should override these ///////
		virtual void startup(void);
		virtual void mainLoop(void);
		/////////////////////////////////////////////

		///////////////// good luck with your project //////////////////
	};

	// must be created by client
	Application* createApplication();
}
