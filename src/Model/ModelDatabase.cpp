# pragma once

# include <stdio.h>
# include <Siv3D.hpp>

# include "./Model/ModelDatabase.hpp"

namespace BeamFromEyes::Model
{
	ModelDatabase::ModelDatabase()
	{
		Mesh backObstacleModel{ MeshData::TwoSidedPlane(1) };
		
		s3d::Model::RegisterDiffuseTextures(obstacleModel, TextureDesc::MippedSRGB);

		// マテリアル設定
		backObstacleMaterial.ambientColor = ColorF{ 1.0 };
		backObstacleMaterial.diffuseColor = ColorF{ 0.0 };
		backObstacleMaterial.emissionColor = Linear::Palette::Ghostwhite;
	}

	ModelDatabase::~ModelDatabase()
	{

	}
}
