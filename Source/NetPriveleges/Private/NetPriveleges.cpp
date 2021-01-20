// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetPriveleges.h"
#include "NetPrivelegesStyle.h"
#include "NetPrivelegesCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName NetPrivelegesTabName("NetPriveleges");

#define LOCTEXT_NAMESPACE "FNetPrivelegesModule"

void FNetPrivelegesModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FNetPrivelegesStyle::Initialize();
	FNetPrivelegesStyle::ReloadTextures();

	FNetPrivelegesCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FNetPrivelegesCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FNetPrivelegesModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FNetPrivelegesModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(NetPrivelegesTabName, FOnSpawnTab::CreateRaw(this, &FNetPrivelegesModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FNetPrivelegesTabTitle", "NetPriveleges")) // TODO
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FNetPrivelegesModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FNetPrivelegesStyle::Shutdown();

	FNetPrivelegesCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(NetPrivelegesTabName);
}

TSharedRef<SDockTab> FNetPrivelegesModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FNetPrivelegesModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("NetPriveleges.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FNetPrivelegesModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(NetPrivelegesTabName);
}

void FNetPrivelegesModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FNetPrivelegesCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FNetPrivelegesCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FNetPrivelegesModule, NetPriveleges)