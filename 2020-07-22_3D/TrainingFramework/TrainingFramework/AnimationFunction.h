#pragma once
#include "stdafx.h"
class AnimationFunction {
public:
	static float EaseInOut(float start, float end, float value);
	static float Linear(float start, float end, float value);
	static float EaseOutCirc(float start, float end, float value);
	static float GetColorFromGradient(unsigned int v1, unsigned int v2, float value);
	static float EaseOutQuint(float start, float end, float value);
};