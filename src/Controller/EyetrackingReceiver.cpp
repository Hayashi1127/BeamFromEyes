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
		Float2 positionNorm{ 0, 0 };
		if (estimateNorm.at(5) < estimateNorm.at(4)) // 左を向いていると考えられる時
		{
			if (estimateNorm.at(4) < 0.6)
			{
				positionNorm.x = 0.05 * estimateNorm.at(4) + estimateNorm.at(3) / 1.05; // Outは軽く見る
			}
			else
			{
				positionNorm.x = 0.05 * estimateNorm.at(3) + estimateNorm.at(4) / 1.05; // Inは軽く見る
			}

			positionNorm.x = 1 - positionNorm.x;
		}
		else                                         // 右を向いていると考えられる時
		{
			if (estimateNorm.at(5) < 0.5)
			{
				positionNorm.x += 0.05 * estimateNorm.at(5) + estimateNorm.at(2) / 1.05; // Outは軽く見る
			}
			else
			{
				positionNorm.x += 0.05 * estimateNorm.at(2) + estimateNorm.at(5) / 1.05; // Inは軽く見る
			}
		}

		// 左目基準で上下どちらを向いているか判定、estimateNormが大きい方を採用
		if (estimateNorm.at(0) < estimateNorm.at(6)) // 上を向いていると考えられる時
		{
			positionNorm.y = estimateNorm.at(6) + estimateNorm.at(7) / 2.0;
			positionNorm.y = 1 - positionNorm.y;
		}
		else                                         // 下を向いていると考えられる時
		{
			positionNorm.y += estimateNorm.at(0) + estimateNorm.at(1) / 2.0;
		}

		positionNorm.x /= 2;
		positionNorm.y /= 2;
		positionNormCache.push_back(positionNorm);

		// 数フレーム使って補正
		Float2 smoothedPositionNorm{ 0, 0 };
		if (positionNormCache.size() >= positionCacheNum)
		{
			float weightDiff{ 0.2 };
			float weight{ 0.2 };
			float weightSum{ 0 };
			for (int i = 0; i < positionCacheNum - 1 ; i++)
			{
				smoothedPositionNorm += weight * positionNormCache[i];
				weightSum += weight;
				weight += weightDiff;
			}

			smoothedPositionNorm += positionNormCache[positionCacheNum - 1];
			weightSum += 1;

			smoothedPositionNorm = smoothedPositionNorm / weightSum;
			positionNormCache.pop_front();
		}
		else
		{
			smoothedPositionNorm = positionNorm;
		}

		position.x = CalcPosition(0, sceneSize.x, smoothedPositionNorm.x);
		position.y = CalcPosition(0, sceneSize.y, smoothedPositionNorm.y);
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
