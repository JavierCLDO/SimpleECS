#pragma once

#include "user_component.h"

class MyComponent : public fen::UserComponent
{
protected:
	void Init() override;
	void Update(const double dt) override;
	void Destroy() override;

private:
	int counter{ 15 };
};