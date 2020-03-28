// Simple CW IDer /////////////////
// By: Bob Anding
// Simple Ider to encode and decode CW massage Array with tone and keyer outputs
//  Build 4-20-16
//  Copyright (c) 2016 BOB ANDING
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details:
//
//  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
//  Boston, MA  02111-1307  USA
/////////////////////////////

/////////// PLACE MESSAGE HERE  ////////////////////////////

char message []={0x06, 0x06, 0x20, 0x0f, 0x1d}; //message = "AA5OY"

////////////////////////////////////////////////////////////
int msglength = sizeof(message) / sizeof(message[0]); // sketch calculates message length, no EOM character needed
////////////////////////////////////////////////////////////////
int dit = 56; // adjust WPM speed here (Slow =  100, Fast = 35)
int dah = 3* dit; // sets dah lenght as a fuction of dit length
int wdsp = 7 * dit;// sets word space  lenght as a fuction of dit length
int CW =A5; // output pin for CW tone 
int PTT = 10; // PTT 
int Keyer = 11; //Keyer pin CW output
int freq = 900; //CW tone frequency (500 - 900)
//////////////// SET TIMER LENGTH and CW WPM speed //////////////

int timerLng = 5; // set length of timer in sceonds, timer length may vary 

///////////////////////////////////////////////////

//////////////// SETUP  ///////////////////////////
void setup() {
///////////// Setup GPIO Pin assignments ///////////////////
pinMode(CW,OUTPUT); // AUDIO OUTPUT pin
pinMode(9,INPUT_PULLUP);  // CW message trigger
pinMode(10,OUTPUT); // PTT pin
pinMode(11,OUTPUT); // Keyer pin
pinMode(13,OUTPUT); // Active Timer pin
}

/////////// LOOP  ///////////////////////

void loop() {
 if(!(digitalRead(9))) timer(); // check for button press, if button is pressed run timer
delay(100);  // put your main code here, to run repeatedly:

}

////////////Functions //////////////////////////

//////////////Message reader //////////////////////
void msgReader()
{
int  element = 0; // letter of message
char temp; 
int LSB =0;

digitalWrite(PTT, HIGH); // turn on PTT
delay(500); // 

for (element =0; element < msglength ; element ++) //  read cw message a letter at a time
  {
 temp =  message[element]; // evaluating each message character
    for(int x = 0;  temp > 1 ; x++) // reads character and checks for End of Character = 1 
      {
      LSB = bitRead(temp, 0); //LSB of temp, each loop shifts right one 
      delay(dit);//delay(dah * 1.3); //add element space
  
      if(LSB == 1)
      {
         digitalWrite(Keyer, HIGH); // turn on Keyer
      tone(CW,freq);//send dah, tone(pin, frequency, duration)  
      delay(dah); //delay(dah); //add element space
      noTone(CW);
      }
      else  
      {
         digitalWrite(Keyer, HIGH); // turn on Keyer
        tone(CW,freq);//send dit, tone(pin, frequency, duration) 
        delay(dit); //add element space
        noTone(CW);
      }
      
      
      temp = temp >> 1;  // shift right one, when temp = 1 quit loop
      digitalWrite(Keyer, LOW); // turn off Keyer
      }
   delay(dah); //character space between elements
   
}
delay(500); // wait 
digitalWrite(PTT, LOW); //turn off  PTT
}

///////////////TIMER ///////////
void timer() 
{

    for(int x = 0;  x < timerLng;  x++)
   {
      digitalWrite(13,1);  // timer LED on
      delay(500); 
      digitalWrite(13,0); // timer LED off
      delay(500); 
   }
   msgReader(); 
}

/////// Character list for entering CW meassage  //////
/****************************
 * character to hex number list    
    0x06  = a
    0x11  = b
    0x15  = c
    0x09  = d
    0x02  = e
    0x14  = f
    0x0b  = g
    0x10  = h
    0x04  = i
    0x1e  = j
    0x0d  = k
    0x12  = l
    0x07  = m
    0x05  = n
    0x0f  = o
    0x16  = p
    0x1b  = q
    0x0a  = r
    0x08  = s
    0x03  = t
    0x0c  = u
    0x18  = v
    0x0e  = w
    0x19  = x
    0x1d  = y
    0x13  = z
    0x3e  = 1
    0x3c  = 2
    0x38  = 3
    0x30  = 4
    0x20  = 5
    0x21  = 6
    0x23  = 7
    0x27  = 8
    0x2f  = 9
    0x3f  = 0
    0x29  = / 
    0x4c  = ?    
    0x00  = word space
    0xff  = eom
    0x6a = '.'
    0x73 = ','
    0x56 = '@'
    
   
* additional prosigns can be added if needed 
    0x68 = '*'  SK
    0xd1 = '^'  BK
    0x2a = '+'  AR
    0x31 =  '$'   BT 

///////////////////////////
 */
