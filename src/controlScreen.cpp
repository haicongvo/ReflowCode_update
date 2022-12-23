#include "controlScreen.h"
#include "button.h"
#include "OledDisplay.h"
#include "Temp.h"
#include "controlPID.h"
#include "variableComom.h"

OLED oled;
BUTTON button;
TEMP temp;
PID pidsetting;

void DISPLAYSCREEN::ResetValue(void)
{
    //reset value when returning to main screen
    SettingSelection = 1;
    SettingSelectionScreen = 1;
    ModeSelection = false;
    BuzzerOnOff = false;
    FanOnOff = false;
    PIDSetting = false;
    PIDValueChange = false;
}

void DISPLAYSCREEN::ScreenInit()
{
    oled.Init();
    oled.IntroScreen();
    //Display main screen
    oled.MainScreen();
    //Display info on main screen
    oled.DisplayThermal1(temp.ReadThermal_1());
    oled.DisplayThermal2(temp.ReadThermal_2());
    oled.DisplaySetpoint(Setpoint);
    oled.DisplayTableInfo();
    oled.DisplayFanMonitor(false);
    oled.ResetTimeCount();

}

void DISPLAYSCREEN::SettingAndMainScreenDisplay(void)
{
    if(MenuButtonPress)
    {
        MenuButtonPress = false;
        ChangeScreen = true;
        ScreenSettingMode = !ScreenSettingMode;
        //reset value when returning to main screen
        ResetValue();
    }
    if(ChangeScreen)
    {
        oled.ClearAllScreen();
        ChangeScreen = false;
        if(ScreenSettingMode)
        {
            oled.DisplaySettingScreen();
            oled.DisplaySettingSelection(SettingSelection);
        }
        else
        {
            oled.MainScreen();
            oled.DisplayTableInfo();
        }
    }
}

void DISPLAYSCREEN::WhenMainScreenDisplay(void)
{
    if(!ScreenSettingMode)
    {
        float temp1 = temp.ReadThermal_1();
        float temp2 = temp.ReadThermal_2();
        oled.DisplayThermal1(temp1);
        oled.DisplayThermal2(temp2);
        oled.DisplaySetpoint(Setpoint);
        oled.DisplayTableInfo();
        oled.ResetTimeCount();
    }
}

void DISPLAYSCREEN::SelectItemInSetting(void)
{
    if(ScreenSettingMode && (UPButtonPress || DWButtonPress) && !PIDValueChange)
    {
        uint8_t MaxCount = 0;
        uint8_t MinCount = 1;

        if(ModeSelection) MaxCount = ModeSelectOption;
        else if(BuzzerOnOff) MaxCount = BuzzerOnOffOption;
        else if(FanOnOff) MaxCount = FanOnOffOption;
        else if(PIDSetting) MaxCount = PIDSettingOption;
        else MaxCount = SettingOption;

        if(DWButtonPress)
        {
            DWButtonPress = false;
            SettingSelection++;
            if(SettingSelection > MaxCount) SettingSelection = MinCount;
        }
        else if(UPButtonPress)
        {
            UPButtonPress = false;
            SettingSelection--;
            if(SettingSelection < MinCount) SettingSelection = MaxCount;
        }
        oled.DisplaySettingSelection(SettingSelection);
    }
}

void DISPLAYSCREEN::AcceptSettingSelection(void)
{
    if(ScreenSettingMode && OKButtonPress && (!ModeSelection && !BuzzerOnOff && !FanOnOff && !PIDSetting))
    {
        OKButtonPress = false;
        ChangeScreen = true;
        SettingSelectionScreen = SettingSelection;
        SettingSelection = 1;
    }
    if(ChangeScreen)
    {
        oled.ClearAllScreen();
        ChangeScreen = false;
        switch(SettingSelectionScreen)
        {
            case 1: //Mode Selection screen
                oled.DisplayModeSelectionScreen();
                ModeSelection = true;
                break;
            case 2: //Buzzer on/off screen
                oled.DisplayBuzzerOnOffScreen();
                BuzzerOnOff = true;
                break;
            case 3: //Fan on/off screen
                oled.DisplayFanOnOffScreen();
                FanOnOff = true;
                break;
            case 4: // PID setting Screen
                oled.DisplayPIDSettingScreen();
                PIDSetting = true;
                break;
            default:
                break;
        }
        oled.DisplaySettingSelection(SettingSelection);
    }
}

void DISPLAYSCREEN::ModeSelect(void)
{
    if(ScreenSettingMode && ModeSelection && (SettingSelectionScreen == 1))
    {
        if(OKButtonPress)
        {
            OKButtonPress = false;
            ModeSelection = false;
            switch(SettingSelection)
            {
                case 1: //heat mode
                    RunMode = HEATER_MODE;
                    break;
                case 2: //reflow mode
                    RunMode = REFLOW_MODE;
                    break;
                case 3: //cancel
                    break;
                default:
                    break;
            }
            ReturnSettingScreen();
        }
    }
}

void DISPLAYSCREEN::BuzzerSelect(void)
{
    if(ScreenSettingMode && FanOnOff && (SettingSelectionScreen == 2))
    {
        if(OKButtonPress)
        {
            OKButtonPress = false;
            BuzzerOnOff = false;
            switch(SettingSelection)
            {
                case 1: //on mode
                    BuzzerMode = BUZZER_ON;
                    break;
                case 2: //off mode
                    BuzzerMode = BUZZER_OFF;
                    break;
                case 3: //cancel
                    break;
                default:
                    break;
            }
            ReturnSettingScreen();
        }
    }
}

void DISPLAYSCREEN::FanSelect(void)
{
    if(ScreenSettingMode && FanOnOff && (SettingSelectionScreen == 3))
    {
        if(OKButtonPress)
        {
            OKButtonPress = false;
            FanOnOff = false;
            switch (SettingSelection)
            {
            case 1: //auto mode
                FanMode = FAN_AUTO;
                break;
            case 2: //off fan
                FanMode = FAN_OFF;
                break;
            case 3: // on fan
                FanMode = FAN_ON;
                break;
            case 4: //cancel
                break;
            default:
                break;
            }
            ReturnSettingScreen();
        }
    }
}

void DISPLAYSCREEN::PIDChange(void)
{
    if(ScreenSettingMode && PIDSetting && (SettingSelectionScreen == 4))
    {
        if(OKButtonPress && !PIDValueChange)
        {
            OKButtonPress = false;
            switch(SettingSelection)
            {
                case 1: // P change
                    KpTemp = Kp;
                    PIDValueChangeSelect = P_CHANGE;
                    PIDValueChange = true;
                    oled.ClearDisplayPIDValue(P_CHANGE);
                    break;
                case 2: // I change
                    KiTemp = Ki;
                    PIDValueChangeSelect = I_CHANGE;
                    PIDValueChange = true;
                    oled.ClearDisplayPIDValue(I_CHANGE);
                    break;
                case 3: // D change
                    KdTemp = Kd;
                    PIDValueChangeSelect = D_CHANGE;
                    PIDValueChange = true;
                    oled.ClearDisplayPIDValue(D_CHANGE);
                    break;
                case 4: // cancel
                    ReturnSettingScreen();
                    break;
                default:
                    break;
            }
        }

        if(PIDValueChange)
        {
            switch (PIDValueChangeSelect)
            {
                case P_CHANGE: //change P value
                    if(button.ReadLongPressUpDutton()) KpTemp = KpTemp + 0.1;
                    if(button.ReadLongPressDWDutton()) KpTemp = KpTemp - 0.1;
                    if(KpTemp != KpValueTemp)
                    {
                        oled.DisplayPIDChangeValue(P_CHANGE);
                        KpValueTemp = KpTemp;
                    }
                    break;
                case I_CHANGE: //change I value
                    if(button.ReadLongPressUpDutton()) KiTemp = KiTemp + 0.1;
                    if(button.ReadLongPressDWDutton()) KiTemp = KiTemp - 0.1;
                    if(KiTemp != KiValueTemp)
                    {
                        oled.DisplayPIDChangeValue(I_CHANGE);
                        KiValueTemp = KiTemp;
                    }
                    break;
                case D_CHANGE: //change D value
                    if(button.ReadLongPressUpDutton()) KdTemp = KdTemp + 0.1;
                    if(button.ReadLongPressDWDutton()) KdTemp = KdTemp - 0.1;
                    if(KdTemp != KdValueTemp)
                    {
                        oled.DisplayPIDChangeValue(D_CHANGE);
                        KdValueTemp = KdTemp;
                    }
                    break;
                default:
                    break;
            }
        }

        if(OKButtonPress && PIDValueChange) // accpect value PID
        {
            if(PIDValueChangeSelect == P_CHANGE) 
            {
                Kp = KpTemp;
                SettingSelection = 1;
            }
            if(PIDValueChangeSelect == I_CHANGE) 
            {
                Ki = KiTemp;
                SettingSelection = 2;
            }
            if(PIDValueChangeSelect == D_CHANGE) 
            {
                Kd = KdTemp;
                SettingSelection = 3;
            }
            PIDValueChangeSelect = 0;
            OKButtonPress = false;
            PIDValueChange = false;
            KpTemp = 0;
            KiTemp = 0;
            KdTemp = 0;
            KpValueTemp = 0;
            KiValueTemp = 0;
            KdValueTemp = 0;

            oled.ClearAllScreen();
            oled.DisplayPIDSettingScreen();
            oled.DisplaySettingSelection(SettingSelection);
        }
    }
}

void DISPLAYSCREEN::ReturnSettingScreen(void)
{
    ResetValue();
    oled.ClearAllScreen();
    oled.DisplaySettingScreen();
    oled.DisplaySettingSelection(SettingSelection);
}

void DISPLAYSCREEN::SettingTableInfo(void)
{
    if(!ScreenSettingMode && OKButtonPress)
    {
        OKButtonPress = false;
        SettingTableInfoCount ++;
        AcceptSettingTableInfo = true;

        if(RunMode == HEATER_MODE)
        {
            if(SettingTableInfoCount > 1) 
            {
                SettingTableInfoCount = 0;
                AcceptSettingTableInfo = false;
            }
        }
        else if(RunMode == REFLOW_MODE)
        {
            if(SettingTableInfoCount > 8) 
            {
                SettingTableInfoCount = 0;
                AcceptSettingTableInfo = false;
            }
        }
    }

    if(!ScreenSettingMode && AcceptSettingTableInfo)
    {
        
    }
}