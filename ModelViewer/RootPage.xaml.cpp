//
// RootPage.xaml.cpp
// Implementation of the RootPage class
//

#include "pch.h"
#include "RootPage.xaml.h"
#include "DirectXPage.xaml.h"
#include "BlankPage.xaml.h"
#include <ppltasks.h>
#include <experimental/resumable>
#include <pplawait.h>
#include <future>
#include <thread>
#include <iostream>
#include "Scene\GraphNode.h"
#include "ModelFactory.h"
#include "SceneManager.h"
#include "Utility.h"

using namespace ModelViewer;

using namespace Platform;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace concurrency;
using namespace std;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

RootPage::RootPage()
{
	InitializeComponent();
}

void RootPage::SaveInternalState(IPropertySet^ state)
{
	//critical_section::scoped_lock lock(m_main->GetCriticalSection());
	//m_deviceResources->Trim();

	//// Stop rendering when the app is suspended.
	//m_main->StopRenderLoop();

	//// Put code to save app state here.
}

// Loads the current state of the app for resume events.
void RootPage::LoadInternalState(IPropertySet^ state)
{
	// Put code to load app state here.

	// Start rendering when the app is resumed.
	//m_main->StartRenderLoop();
}

void ModelViewer::RootPage::NavView_ItemInvoked(Windows::UI::Xaml::Controls::NavigationView^ sender, Windows::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs^ args)
{

}

void ModelViewer::RootPage::NavView_SelectionChanged(Windows::UI::Xaml::Controls::NavigationView^ sender, Windows::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs^ args)
{

}

void ModelViewer::RootPage::MoreInfoBtn_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}

void ModelViewer::RootPage::NavView_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ContentFrame->Navigate(DirectXPage::typeid);
}

task<MeshNode *> LoadFileAsync()
{
	auto fop = ref new FileOpenPicker();
	fop->FileTypeFilter->Append(".glb");

	auto file = co_await fop->PickSingleFileAsync();

	Utility::Out(L"filename = %s", file->Path->Data());

	auto tempFolder = Windows::Storage::ApplicationData::Current->TemporaryFolder;
	auto tempFile = co_await file->CopyAsync(tempFolder, file->Name, NameCollisionOption::GenerateUniqueName);
	//auto ret = co_await ModelFactory::CreateFromFileAsync(tempFile->Path);

	auto ret = co_await std::async([&tempFile]() { return ModelFactory::CreateFromFileAsync(tempFile->Path); });

	co_return ret.get();
}

void ModelViewer::RootPage::ImportClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto tsk = LoadFileAsync();
	tsk.then([this](MeshNode *node)
	{
		auto nd = make_shared<MeshNode>();
		nd.reset(node);
		// Add the GraphNode to the scene
		SceneManager::Instance().Current()->SelectedNode()->AddChild(nd);
	});
}
