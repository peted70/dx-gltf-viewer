#pragma once
class Axis
{
public:
	Axis(float axisLength);
	void Initialise(ID3D11Device *device);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);
	int IndexCount() { return m_indexCount; };

private:
	float _axisLength;
	int m_vertexCount;
	int m_indexCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	ID3D11RasterizerState * _pRasterState;
};

