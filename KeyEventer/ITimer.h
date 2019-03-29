#pragma once

struct ITimer
{
	virtual void Start() = 0;
	virtual ~ITimer() = default;
};