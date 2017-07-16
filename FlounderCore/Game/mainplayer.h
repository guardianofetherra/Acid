#pragma once

#include "../Sources/camera/iplayer.h"
#include "../Sources/framework/framework.h"

namespace flounder {
	class mainplayer : 
		public iplayer
	{
	private:
		vector3 *m_position;
		vector3 *m_rotation;
	public:
		mainplayer();

		~mainplayer();

		void update() override;

		inline vector3 *getPosition() override { return m_position; }

		inline vector3 *getRotation() override { return m_rotation; }
	};
}