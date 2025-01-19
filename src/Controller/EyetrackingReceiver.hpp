# pragma once

# include <Siv3D.hpp>

# include "IPointerReceiver.hpp"
# include "ExpressionApp.hpp"
# include "nvAR.h"

using namespace std;

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

		/// @brief positionのキャッシュ
		Array<Point> positionCache;

		/// @brief positionCache何個にするか
		const int32 positionCacheNum{ 5 };

		/// @brief そのフレーム内でマウスを左クリックいているかどうか
		bool isPressed{ false };

		/// @brief キャリブレーションどこまでできてるか
		int32 calibIndex{ 5 };

		/// @brief キャリブレーション
		void Calibration();

		/// @brief 目のblendShape取得
		void ExtractEyeExpressions();

		/// @brief positionを更新
		void UpdatePosition();

		float CalcNormPos(float min, float max, float t);

		/// @brief キャリブレーション値と取得したblendShape値から位置座標計算
		int32 CalcPosition(int32 min, int32 max, float t);

		// Nvidia AR SDKまわり
		App app;

		/*
		* eyeLookDown_L ... 12
		* eyeLookDown_R ... 13
		* eyeLookIn_L   ... 14
		* eyeLookIn_R   ... 15
		* eyeLookOut_L  ... 16
		* eyeLookOut_R  ... 17
		* eyeLookUp_L   ... 18
		* eyeLookUp_R   ... 19
		*/
		Array<float> eyeExpressions;

		/*
		* eyeLookDown_L_Up   ... 0
		* eyeLookDown_L_Down ... 1
		* eyeLookDown_R_Up   ... 2
		* eyeLookDown_R_Down ... 3
		* eyeLookIn_L_L      ... 4
		* eyeLookIn_L_R      ... 5
		* eyeLookIn_R_R      ... 6
		* eyeLookIn_R_L      ... 7
		* eyeLookOut_L_R     ... 8
		* eyeLookOut_L_L     ... 9
		* eyeLookOut_R_L     ... 10
		* eyeLookOut_R_R     ... 11
		* eyeLookUp_L_Down   ... 12
		* eyeLookUp_L_Up     ... 13
		* eyeLookUp_R_Down   ... 14
		* eyeLookUp_R_Up     ... 15
		*/ 
		Array<float> calibExpressionDatas;

		/*
		calibExpressionDatasとeyeExpressionsから推定した正規化座標
		* eyeLookDown_L ... 0
		* eyeLookDown_R ... 1
		* eyeLookIn_L   ... 2
		* eyeLookIn_R   ... 3
		* eyeLookOut_L  ... 4
		* eyeLookOut_R  ... 5
		* eyeLookUp_L   ... 6
		* eyeLookUp_R   ... 7
		*/
		Array<float> estimateNorm;

		void ReceiveError(NvCV_Status error);
	public:
		EyetrackingReceiver();
		~EyetrackingReceiver();
		void Update();
		Vec2 GetPointerPosition() const;
		bool GetIsPressed() const;
	};
}
