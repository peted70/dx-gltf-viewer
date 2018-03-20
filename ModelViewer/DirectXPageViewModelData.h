#pragma once
class DirectXPageViewModelData : public Observable
{
public:
	DirectXPageViewModelData();

	// Inherited via Observable
	virtual void Notify(const Observable & data) override;

public:
	float _lightDirection[3] = { 0.5f, 0.5f, 0.0f };

	float _lightPitch = 0.0f;
	float _lightRotation = 0.0f;
	float _lightScale = 0.0f;
	float _ibl = 1.0f;
	float _lightColour[3] = {255.f, 255.f, 255.f};

	bool _metallic = true;
	bool _roughness = true;
	bool _baseColour = true;
	bool _diffuse = true;
	bool _specular = true;
	bool _f = true;
	bool _g = true;
	bool _d = true;
};


