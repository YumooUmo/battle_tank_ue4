// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 * 
 */
class SMenu : public SCompoundWidget
{
public:
    SLATE_BEGIN_ARGS(SMenu) {}
    SLATE_ARGUMENT(TWeakObjectPtr<class ATankHUD>, OwningHUD)
    SLATE_ARGUMENT(FText, Title)
    SLATE_END_ARGS()

    void Construct(const FArguments &InArgs);

    TWeakObjectPtr<class ATankHUD> owning_HUD;

    FText title;
    TSharedPtr<class STextBlock> setting_ptr;
    virtual bool SupportsKeyboardFocus() const override { return true; }

    FReply OnPlayClicked() const;
    FReply OnQuitClicked() const;

    FReply OnSettingClicked() ;
};
