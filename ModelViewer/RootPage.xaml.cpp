//
// RootPage.xaml.cpp
// Implementation of the RootPage class
//

#include "pch.h"
#include "RootPage.xaml.h"
#include "DirectXPage.xaml.h"
#include "BlankPage.xaml.h"
#include <ppltasks.h>

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

void ModelViewer::RootPage::ImportClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto fop = ref new FileOpenPicker();
	create_task(fop->PickSingleFileAsync()).then([this](StorageFile^ file)
	{
		if (file)
		{
			//do some stuff
		}
		else
		{
			//do some stuff
		}
	});
}
