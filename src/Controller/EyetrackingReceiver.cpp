# pragma once

# include <Siv3D.hpp>

# include "EyetrackingReceiver.hpp"
# include "ExpressionApp.hpp"

namespace BeamFromEyes::Controller
{
	void EyetrackingReceiver::Update()
	{
		windowPos = Window::GetPos();
		sceneSize = Scene::Size();
		position = Cursor::ScreenPos(); //- windowPos - sceneSize / 2;

		isPressed = MouseL.pressed();

		NvCV_Status err = app.run();
		if (err != NVCV_SUCCESS)
		{
			ReceiveError(err);
		}

		if (calibIndex < calibExpressionDatas.size()/2)
		{
			Calibration();
		}
		else
		{
			ExtractEyeExpressions();
			UpdatePosition();
		}

		if (MouseR.pressed())
		{
			calibIndex = 0;
			positionCache.clear();
		}
	}

	Vec2 EyetrackingReceiver::GetPointerPosition() const
	{
		return position;
	}

	bool EyetrackingReceiver::GetIsPressed() const
	{
		return isPressed;
	}

	EyetrackingReceiver::EyetrackingReceiver()
	{
		windowPos = Window::GetPos();

		// Nvidia AR SDK初期化
		// app初期化
		NvCV_Status err = app.init();
		if (err != NVCV_SUCCESS)
		{
			ReceiveError(err);
		}

		eyeExpressions = Array<float>(8, 0);
		calibExpressionDatas = Array<float>(16, 0);
		estimateNorm = Array<float>(8, 0);
	}

	EyetrackingReceiver::~EyetrackingReceiver()
	{
	}

	void EyetrackingReceiver::Calibration()
	{
		if (isPressed)
		{
			switch (calibIndex)
			{
			case 0: // eyeLookDown_L_Down, eyeLookDown_R_Down, eyeLookUp_L_Down, eyeLookUp_R_Down 下
				calibExpressionDatas.at(1) = app._expressions[12];
				calibExpressionDatas.at(3) = app._expressions[13];
				calibExpressionDatas.at(12) = app._expressions[18];
				calibExpressionDatas.at(14) = app._expressions[19];
				break;
			case 1: // eyeLookIn_L_R, eyeLookOut_R_R, eyeLookOut_L_R, eyeLookIn_R_R 右
				calibExpressionDatas.at(5) = app._expressions[14];
				calibExpressionDatas.at(11) = app._expressions[17];
				calibExpressionDatas.at(8) = app._expressions[16];
				calibExpressionDatas.at(6) = app._expressions[15];
				break;
			case 2: // eyeLookOut_L_L, eyeLookIn_R_L, eyeLookIn_L_L, eyeLookOut_R_L 左
				calibExpressionDatas.at(9) = app._expressions[16];
				calibExpressionDatas.at(7) = app._expressions[15];
				calibExpressionDatas.at(4) = app._expressions[14];
				calibExpressionDatas.at(10) = app._expressions[17];
				break;
			case 3: // eyeLookUp_L_Up, eyeLookUp_R_Up, eyeLookDown_L_Up, eyeLookDown_R_Up 上
				calibExpressionDatas.at(13) = app._expressions[18];
				calibExpressionDatas.at(15) = app._expressions[19];
				calibExpressionDatas.at(0) = app._expressions[12];
				calibExpressionDatas.at(2) = app._expressions[13];
				break;
			}

			calibIndex++;
		}
	}

	void EyetrackingReceiver::ExtractEyeExpressions()
	{
		for (int i = 0; i < eyeExpressions.size(); i++)
		{
			eyeExpressions.at(i) = app._expressions[i + 12];
		}
	}

	void EyetrackingReceiver::UpdatePosition()
	{
		int32 posMin=0, posMax;
		for (int i = 0; i < estimateNorm.size(); i++)
		{
			estimateNorm.at(i) = CalcNormPos(calibExpressionDatas[2 * i], calibExpressionDatas[2 * i + 1], eyeExpressions.at(i));
		}


		// Out基準で左右どちらを向いているか判定、estimateNormが大きい方を採用
		if (estimateNorm.at(5) < estimateNorm.at(4)) // 左を向いていると考えられる時
		{
			//float norm{ 0.0f };
			//if (estimateNorm.at(4) < 0.6)
			//{
			//	norm = 0.5 * estimateNorm.at(4) + estimateNorm.at(3) / 1.5; // Outは軽く見る
			//}
			//else
			//{
			//	norm = 0.005 * estimateNorm.at(3) + estimateNorm.at(4) / 1.005; // Inは軽く見る
			//}

			float norm = estimateNorm.at(3) + estimateNorm.at(4) / 2;
			position.x = CalcPosition(0, sceneSize.x, 1 - norm);
		}
		else                                         // 右を向いていると考えられる時
		{
			//float norm{ 0.0f };
			//if (estimateNorm.at(5) < 0.5)
			//{
			//	norm = 0.5 * estimateNorm.at(5) + estimateNorm.at(2) / 1.5; // Outは軽く見る
			//}
			//else
			//{
			//	norm = 0.005 * estimateNorm.at(2) + estimateNorm.at(5) / 1.005; // Inは軽く見る
			//}

			float norm = estimateNorm.at(2) + estimateNorm.at(5) / 2;
			position.x = CalcPosition(0, sceneSize.x, norm);
		}

		// 左目基準で上下どちらを向いているか判定、estimateNormが大きい方を採用
		if (estimateNorm.at(0) < estimateNorm.at(6)) // 上を向いていると考えられる時
		{
			float norm = estimateNorm.at(6) + estimateNorm.at(7) / 2.0;
			position.y = CalcPosition(0, sceneSize.y, 1 - norm);
		}
		else                                         // 下を向いていると考えられる時
		{
			float norm = estimateNorm.at(0) + estimateNorm.at(1) / 2.0;
			position.y = CalcPosition(0, sceneSize.y, norm);
		}

		if (positionCache.size() >= positionCacheNum)
		{
			Point sum{ 0, 0 };
			int32 weightSum = 0;
			for (int i = 0; i < positionCacheNum; i++)
			{
				sum += positionCache[i];
				//weightSum += i;
			}

			position = (position + sum) / (positionCacheNum+1);
			positionCache.pop_front();
		}

		positionCache.push_back(position);
	}

	float EyetrackingReceiver::CalcNormPos(float calib1, float calib2, float t)
	{
		float norm = (t - Min(calib1, calib2)) / (Max(calib1, calib2) - Min(calib1, calib2));
		return Clamp(norm, 0.0f, 1.0f);
	}

	int32 EyetrackingReceiver::CalcPosition(int32 min, int32 max, float t)
	{
		int32 estimate = t * max + min;
		return Clamp(estimate, min, max);
	}

	void EyetrackingReceiver::ReceiveError(NvCV_Status error)
	{
		Print << error;
	}
}
