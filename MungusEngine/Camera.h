#pragma once
#include "stdafx.h"
#include "Entity.h"

namespace Mungus {
	class Actor;
	class BoundingBox;
	struct CursorLocation;

	class Camera : public Entity {
	private:
		float rotationSpeed;
		float movementSpeed;

		float nearRenderDistance;
		float farRenderDistance;
		float fieldOfView;
		float aspectRatio;

	public:
		int strafing;
		int ascending;
		int advancing;
		int turning;
		int pitching;
		int rolling;

		Camera();
		virtual ~Camera();

		const MungusMath::MMat4 viewMatrix(void) const;
		const MungusMath::MMat4 perspectiveMatrix() const;

		const float getRotationSpeed(void) const;
		inline void setRotationSpeed(float speed) { rotationSpeed = speed; }

		inline float getMovementSpeed(void) const { return movementSpeed; }
		inline void setMovementSpeed(float speed) { movementSpeed = speed; }

		MungusMath::Line getRayFromCursorLocation(const CursorLocation& cursorLocation, float windowWidth, float windowHeight) const;


		inline float getNearRenderDistance(void) const { return nearRenderDistance; }
		inline float getFarRenderDistance(void) const { return farRenderDistance; }
		inline float getFieldOfView(void) const { return fieldOfView; }
		inline float getAspectRatio(void) const { return aspectRatio; }

		inline void setNearRenderDistance(float nearRenderDistance) { this->nearRenderDistance = nearRenderDistance; }
		inline void setFarRenderDistance(float farRenderDistance) { this->farRenderDistance = farRenderDistance; }
		inline void setFieldOfView(float fieldOfView) { this->fieldOfView = fieldOfView; }
		inline void setAspectRatio(float aspectRatio) { std::cout << aspectRatio << "\n"; this->aspectRatio = aspectRatio; }

		bool visible(const Actor& actor) const;
		bool visible(const std::shared_ptr<Mungus::BoundingBox> boundingBox) const;
	};

}