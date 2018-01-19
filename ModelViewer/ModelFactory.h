#pragma once
#include "Scene\GraphNode.h"
#include "Scene\MeshNode.h"
#include "ppltasks.h"
#include <future>
#include <experimental/resumable>

using namespace Windows::Foundation;
using namespace ModelViewer;
using namespace std;
using namespace Platform;
using namespace concurrency;

class ModelFactory
{
public:
	ModelFactory();
	~ModelFactory();

	static future<shared_ptr<MeshNode>> CreateFromFileAsync(String^ filename);
};

