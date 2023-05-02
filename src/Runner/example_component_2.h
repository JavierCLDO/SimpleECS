#pragma once

#include "user_component.h"

class MyComponent_2 : public fen::UserComponent
{
protected:
	void Init() override;
	void Update(const double dt) override;
	void Destroy() override;

private:
	int counter{ 8 };
};