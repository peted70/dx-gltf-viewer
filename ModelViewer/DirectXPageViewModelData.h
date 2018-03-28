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
	unsigned char _lightColour[3] = {255, 255, 255};

	bool _metallic = false;
	bool _roughness = false;
	bool _baseColour = false;
	bool _diffuse = false;
	bool _specular = false;
	bool _f = false;
	bool _g = false;
	bool _d = false;
};


