# pragma once

# include <Siv3D.hpp>

# include "IPointerReceiver.hpp"

namespace BeamFromEyes::Controller
{
	class MousePointerReceiver : public IPointerReceiver
	{
	private:
		/// @brief モニター上のゲームウィンドウの位置
		Point windowPos;

		/// @brief シーンサイズ
		Size sceneSize;

		/// @brief ポインターの場所
		Point position{ 0, 0 };

		/// @brief そのフレーム内でマウスを左クリックいているかどうか
		bool isPressed{ false };
	public:
		MousePointerReceiver();
		~MousePointerReceiver();
		void Update();
		Vec2 GetPointerPosition();
		bool GetIsPressed();
	};
}
