// Fill out your copyright notice in the Description page of Project Settings.

#include "TankHUD.h"
//Include First
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "SMenu.h"
#include "TankWidget.h"
#include "Widgets/SWeakWidget.h"

// #include "GameFramework/HUD.h"
// #include "GameFramework/PlayerController.h"

void ATankHUD::BeginPlay()
{
    Super::BeginPlay();
};

void ATankHUD::DrawHUD()
{
    Super::DrawHUD();
};

void ATankHUD::_show_pause_menu()
{
    if (GEngine && GEngine->GameViewport)
    {
        UE_LOG(LogTemp, Error, TEXT("We Definitly Made IT ~!"));
        FText text = FText::FromString("HaHaHa");
        smenu = SNew(SMenu).OwningHUD(this).Title(text);
        // smenu->Get().OnSettingClicked();

        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(widget_container, SWeakWidget).PossiblyNullContent(smenu.ToSharedRef()));

        if (PlayerOwner)
        {
            PlayerOwner->bShowMouseCursor = true;
            PlayerOwner->SetInputMode(FInputModeUIOnly());
        }
    }
};
void ATankHUD::_remove_menu()
{
    if (GEngine && GEngine->GameViewport && widget_container.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(widget_container.ToSharedRef());
    }
    if (PlayerOwner)
    {
        PlayerOwner->bShowMouseCursor = false;
        PlayerOwner->SetInputMode(FInputModeGameOnly());
        // this->Destroy();
        // UE_LOG(LogTemp, Warning, TEXT("HUD Destroy ~!"));
    }
};

void ATankHUD::_set_current_widget(UTankWidget *current_widget_toset = nullptr)
{
    if (current_widget != nullptr)
    {
        current_widget->RemoveFromViewport();
        current_widget = nullptr;
    }
    if (current_widget_toset != nullptr)
    {
        current_widget = current_widget_toset;
        current_widget->AddToViewport();
    }
};
