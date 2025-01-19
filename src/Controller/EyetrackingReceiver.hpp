# pragma once


# include <Siv3D.hpp>

# include "IPointerReceiver.hpp"
# include "ExpressionApp.hpp"
# include "nvAR.h"
// # include "nvAR_defs.h"
// #include "nvCVOpenCV.h"

namespace BeamFromEyes::Controller
{
	class EyetrackingReceiver : public IPointerReceiver
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

		bool hasCalibData{ false };

		// Nvidia AR SDKまわり
		App app;

		/*
		* eyeLookDown_L
		* eyeLookDown_R
		* eyeLookIn_L
		* eyeLookIn_R
		* eyeLookOut_L
		* eyeLookOut_R
		* eyeLookUp_L
		* eyeLookUp_R
		*/ 
		Array<float> eyeExpressions, calibExpressions;

		void ReceiveError(NvCV_Status error);
	public:
		EyetrackingReceiver();
		~EyetrackingReceiver();
		void Update();
		Vec2 GetPointerPosition() const;
		bool GetIsPressed() const;
	};
}
