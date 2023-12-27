#include "Core/Core.h"

OKE3D::Core::Core()
{
	this->window = nullptr;
}

OKE3D::Core::~Core() {
	this->window = nullptr;
	delete window;
}
