#include "button.h"
#include "pincfg.h"
#include "variableComom.h"

BUTTON buttonvariable;

void BUTTON::ReadAllButton(void)
{
  ReadMenuButtonStatus();
  ReadOKButtonStatus();
  if(!PIDValueChange)// When changing the PID value (PIDValueChange = true), the up/down button for selection is disabled
  {
    ReadDWButtonStatus();
    ReadUPButtonStatus();
  }
}

void BUTTON::ReadMenuButtonStatus()
{
  if((unsigned long)(millis() - lastTimeMenuButtonStateChanged) > debounceDuration) 
  {
    byte buttonState = digitalRead(MENU_BUTTON);
    if(buttonState != lastMenuButtonState) 
    {
      lastTimeMenuButtonStateChanged = millis();
      lastMenuButtonState = buttonState;
      if(buttonState == 1) 
      {
        //do something
        MenuButtonPress = true;
      }
    }
  }
}

void BUTTON::ReadOKButtonStatus()
{
  if((unsigned long)(millis() - lastTimeOKButtonStateChanged) > debounceDuration) 
  {
    byte buttonState = digitalRead(OK_BUTTON);
    if(buttonState != lastOKButtonState) 
    {
      lastTimeOKButtonStateChanged = millis();
      lastOKButtonState = buttonState;
      if(buttonState == 1) 
      {
        //do something
        OKButtonPress = true;
      }
    }
  }
}

void BUTTON::ReadUPButtonStatus()
{
  if((unsigned long)(millis() - lastTimeUPButtonStateChanged) > debounceDuration) 
  {
    byte buttonState = digitalRead(UP_BUTTON);
    if(buttonState != lastUPButtonState) 
    {
      lastTimeUPButtonStateChanged = millis();
      lastUPButtonState = buttonState;
      if(buttonState == 1) 
      {
        //do something
        UPButtonPress = true;
      }
    }
  }
}

void BUTTON::ReadDWButtonStatus()
{
  if((unsigned long)(millis() - lastTimeDWButtonStateChanged) > debounceDuration) 
  {
    byte buttonState = digitalRead(DW_BUTTON);
    if(buttonState != lastDWButtonState) 
    {
      lastTimeDWButtonStateChanged = millis();
      lastDWButtonState = buttonState;
      if(buttonState == 1) 
      {
        //do something
        DWButtonPress = true;
      }
    }
  }
}

bool BUTTON::ReadLongPressUpDutton()
{
  if((unsigned long)(millis() - lastTimeUPButtonToRead) > WaitTimeToRead)
  {
    lastTimeUPButtonToRead = millis();
    if(digitalRead(UP_BUTTON) == LOW) return true;
  }
  return false;
}

bool BUTTON::ReadLongPressDWDutton()
{
  if((unsigned long)(millis() - lastTimeDWButtonToRead) > WaitTimeToRead)
  {
    lastTimeDWButtonToRead = millis();
    if(digitalRead(DW_BUTTON) == LOW) return true;
  }
  return false;
}
