#pragma once
#include "stdafx.h"


namespace Mungus {
	class Application;
	class Actor;
	class Asset;
	class Camera;
	template<typename T> class AABBTree;
	class Shader;

	struct CursorLocation;

	class MUNGUS World {
	private:
		const Application* owner;
		unsigned long frameCount;
		std::unordered_map<std::string, std::shared_ptr<Mungus::Asset>> assets;
		std::shared_ptr<AABBTree<Actor>> actorsTree;
		std::shared_ptr<Camera> camera;

	public:
		World(const Application* owner);
		virtual ~World() {};

		void inline loadActor(	const std::string& title,
								const std::unordered_map<std::string, Shader>& programs);

		const Camera inline getCamera(void) const;
		Camera& getCamera(void);
		const inline unsigned long getFrameCount(void) const { return frameCount; }
		void inline incrementFrameCount(void) { frameCount++; }

		const std::unordered_map<unsigned long, std::shared_ptr<Mungus::Actor>> inline getActors(void) const;
		const unsigned long createActor(const std::string& name, const MungusMath::MVec3& initialPosition);
		const unsigned long setEntityPosition(const unsigned long id, const MungusMath::MVec3& position);
		const unsigned long scaleEntity(const unsigned long id, const MungusMath::MVec3& scale);
		const unsigned long rotateEntity(const unsigned long id, const MungusMath::MVec3& axis, float angle);
		const unsigned long turnEntity(const unsigned long id, float angle);
		const unsigned long pitchEntity(const unsigned long id, float angle);
		const unsigned long rollEntity(const unsigned long id, float angle);

		const MungusMath::MVec3 getCameraPosition(void) const;
		void setCameraPosition(float x, float y, float z);
		void moveCamera(const MungusMath::MVec3& moveBy);

		const MungusMath::MVec3 getCameraForward(void) const;
		const MungusMath::MVec3 getCameraUp(void) const;
		const MungusMath::MVec3 getCameraRight(void) const;
		const MungusMath::MVec3 getCameraPlanarForward(void) const;
		const MungusMath::MVec3 getCameraPlanarUp(void) const;
		const MungusMath::MVec3 getCameraPlanarRight(void) const;

		void setCameraStrafingStatus(int setting);
		void setCameraAscendingStatus(int setting);
		void setCameraAdvancingStatus(int setting);
		void setCameraTurningStatus(int setting);
		void setCameraPitchingStatus(int setting);
		void setCameraRollingStatus(int setting);

		const float getCameraRotationSpeed() const;
		void setCameraRotationSpeed(float speed);
		float getCameraMovementSpeed() const;
		void setCameraMovementSpeed(float speed);

		void rotateCamera(const MungusMath::MVec3& axis, float theta);
		void turnCamera(float angle);
		void pitchCamera(float angle);
		void rollCamera(float angle);

		MungusMath::Line getRayFromCursorLocation(const CursorLocation& cursorLocation, float windowWidth, float windowHeight) const;

		unsigned long findFirstIntersecting(const MungusMath::Line& line);

	};


}