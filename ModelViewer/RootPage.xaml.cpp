//
// RootPage.xaml.cpp
// Implementation of the RootPage class
//

#include "pch.h"
#include "RootPage.xaml.h"
#include "DirectXPage.xaml.h"
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

#include <fstream>

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
	NavView->IsPaneOpen = false;
}

future<shared_ptr<GraphNode>> LoadFileAsync()
{
	auto fop = ref new FileOpenPicker();
	fop->FileTypeFilter->Append(".glb");
	fop->FileTypeFilter->Append(".gltf");

	auto file = co_await fop->PickSingleFileAsync();
	if (file == nullptr)
		co_return nullptr;

	Utility::Out(L"filename = %s", file->Path->Data());

	// Since we don't have access to open a file in native code I'll take a copy of the file here
	// and access it from the application's temp folder. Another option might be to implement a streambuf
	// which streams data from a Winrt stream but since this is just a sample that seems quite high effort.
	// A knock-on effect from this is that GLTF files won't load (only GLB) since the files referenced by the
	// GLTF file i.e. .bin, .jpg, etc. won't have also been copied across..
	//
	auto tempFolder = Windows::Storage::ApplicationData::Current->TemporaryFolder;
	auto tempFile = co_await file->CopyAsync(tempFolder, file->Name, NameCollisionOption::GenerateUniqueName);

	Utility::Out(L"temp file path = %s", tempFile->Path->Data());
	auto ret = co_await ModelFactory::Instance().CreateFromFileAsync(tempFile->Path);
	co_return ret;
}

std::future<void> Load()
{
	Utility::Out(L"At Start of Load");
	auto node = co_await LoadFileAsync();
	if (node == nullptr)
		co_return;

	Utility::Out(L"Loaded");

	// Add the GraphNode to the scene
	auto current = SceneManager::Instance().Current();
	SceneManager::Instance().AddNode(node);
}

void ModelViewer::RootPage::ImportClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Load();
}
