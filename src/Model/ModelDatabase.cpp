# pragma once

# include "./Model/ModelDatabase.hpp"

const Mesh backObstacleModel{ MeshData::TwoSidedPlane(1) };
const s3d::Model obstacleModel{ U"./ThirdParty/Quaternius_UltimateSpaceKit/Environment/OBJ/Planet_4.obj" };

PhongMaterial backObstacleModel;

namespace BeamForEyes::Model
{
	ModelDatabase::ModelDatabase()
	{
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
