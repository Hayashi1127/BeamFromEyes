﻿# pragma once

#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "nvAR.h"
#include "nvAR_defs.h"
#include "nvCVOpenCV.h"

#include "opencv2/opencv.hpp"
#include "MeshRenderer.h"

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <Windows.h>
#define strcasecmp _stricmp
#else
#include <sys/stat.h>
#endif // _WIN32

#ifdef _ENABLE_UI
#include "ExpressionAppUI.h"
#endif  // _ENABLE_UI

#if CV_MAJOR_VERSION >= 4
#define CV_CAP_PROP_FPS           cv::CAP_PROP_FPS
#define CV_CAP_PROP_FRAME_COUNT   cv::CAP_PROP_FRAME_COUNT
#define CV_CAP_PROP_FRAME_HEIGHT  cv::CAP_PROP_FRAME_HEIGHT
#define CV_CAP_PROP_FRAME_WIDTH   cv::CAP_PROP_FRAME_WIDTH
#define CV_CAP_PROP_POS_FRAMES    cv::CAP_PROP_POS_FRAMES
#define CV_INTER_AREA             cv::INTER_AREA
#define CV_INTER_LINEAR           cv::INTER_LINEAR
#endif // CV_MAJOR_VERSION

#ifndef M_PI
#define M_PI                      3.1415926535897932385
#endif /* M_PI */
#ifndef M_2PI
#define M_2PI                     6.2831853071795864769
#endif /* M_2PI */
#ifndef M_PI_2
#define M_PI_2                    1.5707963267948966192
#endif /* M_PI_2 */
#define D_RADIANS_PER_DEGREE        (M_PI / 180.)
#define F_PI                        ((float)M_PI)
#define F_PI_2                      ((float)M_PI_2)
#define F_2PI                       ((float)M_2PI)
#define F_RADIANS_PER_DEGREE        (float)(M_PI / 180.)
#define CTL(x)                      ((x) & 0x1F)
#define HELP_REQUESTED              411

#define BAIL_IF_ERR(err)            do { if ((int)(err) != 0)     { goto bail;             } } while(0)
#define BAIL_IF_NULL(x, err, code)  do { if ((void*)(x) == NULL)  { err = code; goto bail; } } while(0)
#define BAIL_IF_CUERR(cu, err)      do { if (cudaSuccess != (cu)) { err = NvFromCuErr(cu); } } while(0)
#define BAIL(err, code)             do {                            err = code; goto bail;   } while(0)

#define DEFAULT_CODEC         "avc1"
#define DEFAULT_FACE_MODEL    "face_model2.nvf"
#define DEFAULT_RENDER_MODEL  "face_model2.nvf"
#define NUM_CAMERA_INTRINSIC_PARAMS 3



class MyTimer {
public:
	MyTimer() { dt = dt.zero(); }  /**< Clear the duration to 0. */
	void start() { t0 = std::chrono::high_resolution_clock::now(); }  /**< Start  the timer. */
	void pause() { dt = std::chrono::high_resolution_clock::now() - t0; }  /**< Pause  the timer. */
	void resume() { t0 = std::chrono::high_resolution_clock::now() - dt; }  /**< Resume the timer. */
	void stop() { pause(); }  /**< Stop   the timer. */
	double elapsedTimeFloat() const {
		return std::chrono::duration<double>(dt).count();
	} /**< Report the elapsed time as a float. */
private:
	std::chrono::high_resolution_clock::time_point t0;
	std::chrono::high_resolution_clock::duration dt;
};


class App {
public:

	App() {}
	~App() { stop(); }

	NvCV_Status run();
	NvCV_Status stop();
	NvCV_Status setInputVideo(const std::string& file); // open immediately
	NvCV_Status setInputCamera(int index, const std::string& resStr); // open immediately
	NvCV_Status setOutputVideo(const std::string& file);
	NvCV_Status set(int codec, double fps, unsigned width, unsigned height);  // deferred open
	NvCV_Status init();
	NvCV_Status resizeDst();
	NvCV_Status openOutputVideo(int codec, double fps, unsigned width, unsigned height);
	NvCV_Status initFaceFit();
	NvCV_Status initMLPExpressions();
	NvCV_Status calibrateExpressionWeights();
	NvCV_Status unCalibrateExpressionWeights();
	NvCV_Status normalizeExpressionsWeights();
	NvCV_Status updateCamera();
	NvCV_Status toggleFaceBoxFiltering();
	NvCV_Status toggleLandmarkFiltering();
	NvCV_Status togglePoseFiltering();
	NvCV_Status toggleExpressionFiltering();
	NvCV_Status toggleGazeFiltering();
	NvCV_Status toggleClosureEnhancement();
	NvCV_Status togglePoseMode();
	NvCV_Status overlayLandmarks(const float landmarks[126 * 2], unsigned screenHeight, NvCVImage* im);
	void getFPS();
	void drawFPS(cv::Mat& img);
	void barPlotExprs();

	const char* getErrorStringFromCode(NvCV_Status err);

	struct Pose {
		NvAR_Quaternion rotation;
		NvAR_Vector3f translation;
		float* data() { return &rotation.x; }
		const float* data() const { return &rotation.x; }
	};
	CUstream          _stream = 0;
	cv::Mat           _ocvSrcImg, _ocvDstImg; // _ocvSrcImg is allocated, _ocvDstImg is just a wrapper
	cv::VideoCapture  _vidIn{};
	cv::VideoWriter   _vidOut{};
	double            _frameRate;
	int               _miniX, _miniY, _renderX, _renderY, _plotX, _plotY;
	NvAR_FaceMesh     _arMesh{ nullptr, 0, nullptr, 0 };
	NvAR_FeatureHandle _featureHan{};
	NvAR_RenderingParams _renderParams;
	NvCVImage         _srcImg, _compImg, _srcGpu, _renderImg; // wrapper, alloced, alloced, alloced
	Pose              _pose;
	float             _cameraIntrinsicParams[NUM_CAMERA_INTRINSIC_PARAMS];
	std::string       _inFile, _outFile;
	std::vector<NvAR_Rect> _outputBboxData;
	NvAR_BBoxes        _outputBboxes;
	std::vector<float> _expressions, _expressionZeroPoint, _expressionScale, _expressionExponent, _eigenvalues,
		_landmarkConfidence;
	std::vector<NvAR_Point2f> _landmarks;
	std::vector<NvAR_Vector3f> _vertices;
	std::vector< NvAR_Vector3u16> _triangles;
	unsigned          _videoWidth, _videoHeight, _miniWidth, _miniHeight, _renderWidth, _renderHeight,
		_plotWidth, _plotHeight, _compWidth, _compHeight, _eigenCount, _exprCount, _landmarkCount,
		_viewMode, _exprMode, _filtering;
	unsigned          _poseMode = 0;
	bool              _enableCheekPuff;
	MeshRendererBroker _broker;
	MeshRenderer* _renderer = nullptr;
	static const char _windowTitle[], * _exprAbbr[][4], * _sfmExprAbbr[][4];
	MyTimer           _timer;
	bool              _showFPS;
	bool              _performCalibration;
	bool              _cameraNeedsUpdate;
	double            _frameTime;
	float             _globalExpressionParam;
#ifdef _ENABLE_UI
	ExpressionAppUI   ui_obj_;
#endif  // _ENABLE_UI
	enum {
		EXPR_MODE_MESH = 1,
		EXPR_MODE_MLP = 2,
	};
	enum {
		VIEW_MESH = (1 << 0),
		VIEW_IMAGE = (1 << 1),
		VIEW_PLOT = (1 << 2),
		VIEW_LM = (1 << 3)
	};
	enum {
		APP_ERR_GENERAL = 1,
		APP_ERR_OPEN,
		APP_ERR_READ,
		APP_ERR_WRITE,
		APP_ERR_INIT,
		APP_ERR_RUN,
		APP_ERR_EFFECT,
		APP_ERR_PARAM,
		APP_ERR_UNIMPLEMENTED,
		APP_ERR_MISSING,
		APP_ERR_VIDEO,
		APP_ERR_IMAGE_SIZE,
		APP_ERR_NOT_FOUND,
		APP_ERR_FACE_MODEL,
		APP_ERR_GLFW_INIT,
		APP_ERR_GL_INIT,
		APP_ERR_RENDER_INIT,
		APP_ERR_GL_RESOURCE,
		APP_ERR_GL_GENERAL,
		APP_ERR_FACE_FIT,
		APP_ERR_NO_FACE,
		APP_ERR_CANCEL,
		APP_ERR_CAMERA,
		APP_ERR_ARG_PARSE,
		APP_ERR_EOF
	};
};
