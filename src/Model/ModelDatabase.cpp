# pragma once

# include "./Model/ModelDatabase.hpp"

const s3d::Model obstacleModel{ U"./ThirdParty/Quaternius_UltimateSpaceKit/Environment/OBJ/Planet_4.obj" };

namespace BeamForEyes::Model
{
	ModelDatabase::ModelDatabase()
	{
		s3d::Model::RegisterDiffuseTextures(obstacleModel, TextureDesc::MippedSRGB);
	}

	ModelDatabase::~ModelDatabase()
	{

	}
}
