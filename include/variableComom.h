#ifndef _variableComom_h_
#define _variableComom_h_

// BUTTON STATUS
extern bool MenuButtonPress; 
extern bool OKButtonPress; 
extern bool UPButtonPress; 
extern bool DWButtonPress;

extern float Kp;
extern float Ki;
extern float Kd;

extern float KpTemp;
extern float KiTemp;
extern float KdTemp;
extern float Setpoint;
extern float CurrentTemp;

//----- SETTING OPTION ------------//
#define SettingOption 5
#define ModeSelectOption 3 // 2 option + cancel
#define BuzzerOnOffOption 3 //2 option + cancel
#define FanOnOffOption 4 //3 option + cancel
#define PIDSettingOption 4 //3 option + cancel

extern bool ModeSelection;
extern bool BuzzerOnOff;
extern bool FanOnOff;
extern bool PIDSetting;
extern bool PIDValueChange;

//------ REFLOW DATA -------//
extern uint8_t RefHeatTemp;
extern uint8_t RefHeatTime;

extern int RefSoakTemp;
extern uint8_t RefSoakTime;

extern uint8_t RefRampTemp;
extern uint8_t RefRampTime;

extern int RefReflowTemp;
extern uint8_t RefReflowTime;

//------ HEATER DATA ------//
extern uint8_t HeatTemp;
extern uint8_t HeatDelayTime;

//------- SCREEN INFO -------//
extern uint8_t SettingSelectionScreen;

//------- SETTING DATA -------//
extern uint8_t RunMode;
extern uint8_t BuzzerMode;
extern uint8_t FanMode;
extern uint8_t PIDValueChangeSelect;

//------- Status device ------//
extern bool FanStatus;
extern bool BuzzerStatus;

enum MODECONTROL {
    HEATER_MODE,
    REFLOW_MODE
};

enum FANCONTROL {
    FAN_AUTO,
    FAN_OFF,
    FAN_ON
};

enum BUZZERCONTROL {
    BUZZER_OFF,
    BUZZER_ON
};

enum PIDVALUESETTING {
    P_CHANGE = 1,
    I_CHANGE = 2,
    D_CHANGE = 3
};

enum CONTROL {
    OFF,
    ON
};

#endif