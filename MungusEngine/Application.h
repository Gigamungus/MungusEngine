#pragma once
#include "stdafx.h"

namespace Mungus {
	class Renderer;
	class World;

	struct ActiveBindings;
	struct MUNGUS CursorLocation {
		float xpos;
		float ypos;
	};

	class MUNGUS Application {
	private:
		void inline incrementFrameCount(void);
		void renderActors(void);
		void keyCallBack(GLFWwindow* window, int key, int scanCode, int action, int mods);
		void mouseCallBack(GLFWwindow* window, int button, int action, int mods);
		void cursorCallBack(GLFWwindow* window, double xpos, double ypos);
		void updateCameraPosition(void);
		void updateMouseLocation(void);

		float lmbClickTime;
		float rmbClickTime;
		unsigned long primarySelection;
		bool editingAsset;
		std::string assetBeingEdited;

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
		void addKeyCallback(int key, std::function<void(Mungus::Application*, int, int, int, int)> callback);
		void setNoClipBindings(void);

		const float time(void) const;
		const float frameTime(void) const;
		const unsigned long frameCount(void) const;
		const CursorLocation getLastMouseLocation(void) const;
		const float getLMBClickTime(void) const;

		void inline loadActor(const std::string& actorName);

		void inline setBackground(MungusMath::MVec4 color);
		int getWindowWidth(void) const;
		int getWindowHeight(void) const;

		void disableCursor(void) const;
		void enableCursor(void) const;

		unsigned long getPrimarySelection(void) const { return primarySelection; }
		void setPrimarySelection(unsigned long newSelection) { primarySelection = newSelection; }

		long findFirstActorIntersectingWithRay(const MungusMath::Line& line);
		long findFirstVertexIntersectingWithRay(const MungusMath::Line & line);
		const unsigned long inline createActor(const std::string& name, const MungusMath::MVec3& initialPosition = MungusMath::MVec3{0, 0, 0});
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

			MungusMath::Line getRayFromCursorLocation(const CursorLocation& cursorLocation) const;
			//////////// end camera functions /////////////

			//////////// renderer functions ///////////////

			float getNearRenderDistance(void) const;
			float getFarRenderDistance(void) const;
			float getFieldOfView(void) const;
			float getAspectRatio(void) const;

			void setNearRenderDistance(float nearRenderDistance);
			void setFarRenderDistance(float farRenderDistance);
			void setFieldOfView(float fieldOfView);
			void setAspectRatio(float aspectRatio);

			//////////end renderer functions ///////////////

			////////// asset editor functions //////////////

			void enableWireFrameMode(void) const;
			void exitWireFrameMode(void) const;

			void testChangeVertexCoord(const std::string& asset, long vertexId, const MungusMath::MVec3& newPosition);

			//////////end asset editor functions ///////////

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
