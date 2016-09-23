/*
 * Copyright 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//--------------------------------------------------------------------------------
// Teapot Renderer.h
// Renderer for teapots
//--------------------------------------------------------------------------------
#ifndef _TEAPOTRENDERER_H
#define _TEAPOTRENDERER_H

//--------------------------------------------------------------------------------
// Include files
//--------------------------------------------------------------------------------
#include <jni.h>
#include <errno.h>

#include <vector>

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <GLES/glext.h>
#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/native_window_jni.h>
#include <cpu-features.h>

#define CLASS_NAME "android/app/NativeActivity"
#define APPLICATION_CLASS_NAME "com/sample/teapot/TeapotApplication"

#include "NDKHelper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 Demonstration OpenGL stereo application
 */

typedef struct {
	float x, y, z;
} XYZ;

typedef struct {
	XYZ vp; /* View position           */
	XYZ vd; /* View direction vector   */
	XYZ vu; /* View up direction       */
	XYZ pr; /* Point to rotate about   */
	float focallength; /* Focal Length along vd   */
	float aperture; /* Camera aperture         */
	float eyesep; /* Eye separation          */
	float near, far; /* Cutting plane distances */
	int stereo; /* Are we in stereo mode   */
	int screenwidth; /* Screen dimensions       */
	int screenheight; /*                         */
} CAMERA;

#define NOSTEREO 0
#define STEREO 1
#define ABS(x) (x < 0 ? -(x) : (x))
#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)
#define TRUE  1
#define FALSE 0
#define ESC 27
#define PI 3.141592653589793238462643
#define DTOR            0.0174532925
#define RTOD            57.2957795
#define CROSSPROD(p1,p2,p3) \
   p3.x = p1.y*p2.z - p1.z*p2.y; \
   p3.y = p1.z*p2.x - p1.x*p2.z; \
   p3.z = p1.x*p2.y - p1.y*p2.x

/*------------------- Teapot Renderer --------------- */

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

struct TEAPOT_VERTEX {
	float pos[3];
	float normal[3];
};

enum SHADER_ATTRIBUTES {
	ATTRIB_VERTEX, ATTRIB_NORMAL, ATTRIB_UV,
};

struct SHADER_PARAMS {
	GLuint program_;
	GLuint light0_;
	GLuint material_diffuse_;
	GLuint material_ambient_;
	GLuint material_specular_;

	GLuint matrix_projection_;
	GLuint matrix_view_;
};

struct TEAPOT_MATERIALS {
	float diffuse_color[3];
	float specular_color[4];
	float ambient_color[3];
};

class TeapotRenderer {
	int32_t num_indices_;
	int32_t num_vertices_;
	GLuint ibo_;
	GLuint vbo_;

	bool LoadShaders(SHADER_PARAMS* params, const char* strVsh,
			const char* strFsh);

	ndk_helper::Mat4 mat_model_;

	ndk_helper::TapCamera* camera_;

	XYZ r;
	float ratio, radians, wd2, ndfl;
	float left, right, top, bottom;

public:
	TeapotRenderer();
	virtual ~TeapotRenderer();
	void Init();
	void Render(ndk_helper::Mat4 mat_projection, ndk_helper::Mat4 mat_view);
	void Update(float dTime);
	void UpdateViewport();

	void UpdateLeft(float dTime);
	void UpdateRight(float dTime);
	void UpdateViewportLeft();
	void UpdateViewportRight();

	bool Bind(ndk_helper::TapCamera* camera);
	void Unload();


	/* ------------------------------------ */
	void Normalise(XYZ *p);
	void InitStereoCamera();
	ndk_helper::Mat4 glhFrustrumf(float left, float right, float bottom,
			float top, float znear, float zfar);

	//no stereo
	ndk_helper::Mat4 mat_projection_;
	ndk_helper::Mat4 mat_view_;
	SHADER_PARAMS shader_param_;

	//Left eye
	ndk_helper::Mat4 mat_projection_left_;
	ndk_helper::Mat4 mat_view_left_;

	//Right eye
	ndk_helper::Mat4 mat_projection_right_;
	ndk_helper::Mat4 mat_view_right_;
	CAMERA stereo_cam; //store stereo params

};

#endif

