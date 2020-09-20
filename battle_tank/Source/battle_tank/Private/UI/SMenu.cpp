// Fill out your copyright notice in the Description page of Project Settings.

#include "SMenu.h"
//include first
#include "GameFramework/GameModeBase.h"
#include "TankHUD.h"

#define LOCTEXT_NAMESPACE "MainMenu"

void SMenu::Construct(const FArguments &InArgs)
{
    bCanSupportFocus = true;

    owning_HUD = InArgs._OwningHUD;
    title = InArgs._Title;
    const FMargin contetnt_padding = FMargin(500.f, 300.f);
    const FMargin button_padding = FMargin(10.f);
    // title = InArgs._Title;
    FText title_text = LOCTEXT("GameTitle", "Candy Tank");
    FText play_text = LOCTEXT("PlayGame", "Play");
    FText load_text = LOCTEXT("LoadGame", "Load Game");
    FText setting_text = LOCTEXT("Settings", "Settings");
    FText quit_text = LOCTEXT("QuitGame", "Quit");

    FSlateFontInfo button_text_style = FCoreStyle::Get().GetFontStyle("EmbossedText");
    button_text_style.Size = 40.f;

    FSlateFontInfo title_text_style = button_text_style;
    title_text_style.Size = 60.f;

    ChildSlot
        [SNew(SOverlay)

         //  + SOverlay::Slot()
         //        .HAlign(HAlign_Fill)
         //        .VAlign(VAlign_Fill)
         //            [SNew(SImage)
         //                 .ColorAndOpacity(FColor::Black)]

         + SOverlay::Slot()
               .HAlign(HAlign_Fill)
               .VAlign(VAlign_Fill)
               .Padding(contetnt_padding)
                   [SNew(SVerticalBox)

                    //Title Text
                    + SVerticalBox::Slot()
                          [SNew(STextBlock)
                               .Font(title_text_style)
                               .Text(title_text)
                               .Justification(ETextJustify::Center)]

                    //Play Text
                    + SVerticalBox::Slot()
                          .Padding(button_padding)
                              [SNew(SButton)
                                   .OnClicked(this, &SMenu::OnPlayClicked)
                                       [SNew(STextBlock)
                                            .Font(button_text_style)
                                            .Text(play_text)
                                            .Justification(ETextJustify::Center)]]
                    //Load Text
                    + SVerticalBox::Slot()
                          .Padding(button_padding)
                              [SNew(SButton)
                                   [SNew(STextBlock)
                                        .Font(button_text_style)
                                        .Text(load_text)
                                        .Justification(ETextJustify::Center)]]

                    //Setting Text
                    + SVerticalBox::Slot()
                          .Padding(button_padding)
                              [SNew(SButton)
                                   .OnClicked(this, &SMenu::OnSettingClicked)
                                       [SAssignNew(setting_ptr, STextBlock)
                                            .Font(button_text_style)
                                            .Text(setting_text)
                                            .Justification(ETextJustify::Center)]]

                    //Quit Text
                    + SVerticalBox::Slot()
                          .Padding(button_padding)
                              [SNew(SButton)
                                   .OnClicked(this, &SMenu::OnQuitClicked)
                                       [SNew(STextBlock)
                                            .Font(button_text_style)
                                            .Text(quit_text)
                                            .Justification(ETextJustify::Center)]]]];
};

FReply SMenu::OnPlayClicked() const
{
    if (owning_HUD.IsValid())
    {
        owning_HUD->_remove_menu();
    }
    return FReply::Handled();
};
FReply SMenu::OnQuitClicked() const
{
    if (owning_HUD.IsValid())
    {
        if (APlayerController *PC = owning_HUD->PlayerOwner)
        {
            PC->ConsoleCommand("quit");
        }
    }
    return FReply::Handled();
};

FReply SMenu::OnSettingClicked()
{
    setting_ptr.Get()->SetText(title);
    UE_LOG(LogTemp, Error, TEXT("SMenu said : %s ~!"), *(title.ToString()));
    return FReply::Handled();
};

#undef LOCTEXT_NAMESPACE
