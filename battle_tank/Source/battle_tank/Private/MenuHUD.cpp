// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuHUD.h"
#include "Engine/Engine.h"
#include "SMenu.h"
#include "Widgets/SWeakWidget.h"
// #include "GameFramework/HUD.h"
// #include "GameFramework/PlayerController.h"

void AMenuHUD::BeginPlay()
{
    Super::BeginPlay();
}
void AMenuHUD::_show_menu()
{
    if (GEngine && GEngine->GameViewport)
    {
        UE_LOG(LogTemp, Error, TEXT("We Definitly Made IT ~!"));
        smenu = SNew(SMenu).OwningHUD(this).Title(FString("HaHaHa"));
        // smenu->Get().OnSettingClicked();

        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(widget_container, SWeakWidget).PossiblyNullContent(smenu.ToSharedRef()));

        if (PlayerOwner)
        {
            PlayerOwner->bShowMouseCursor = true;
            PlayerOwner->SetInputMode(FInputModeUIOnly());
        }
    }
};
void AMenuHUD::_remove_menu()
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
