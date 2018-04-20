#pragma once

class ID3D11DeviceContext2;

class SceneContext
{
public:
	SceneContext(ID3D11DeviceContext2 *context);
	~SceneContext();

	ID3D11DeviceContext2& context() { return *_context; }

private:
	ID3D11DeviceContext2 * _context;
};

