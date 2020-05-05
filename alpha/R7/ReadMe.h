/*

   ardUX alpha 7 patch notes

                |-|  |-|  \--\  /--/
                | |  | |   \  \/  /
           ARD  | |  | |    >    <
                | |__| |   /  /\  \
                 \_____/  /__/  \__\
            ARDUINO'S PC-EQUIVLENT
 
   -Added ServoMove, Requiring a Servo Pin and 
   a Servo Rotation in degrees

   -Changed Readme

   -Removed SI integer for the ancient Serial
   Interface mode that never did anything.

   -added more comments to improve reprograming
   quality-of-life.

                     ARDUX Setup
   Wiring
     LCD           Speaker - D6
     |LCD   UNO  
     |-rs - D12  
     |-en - D11 
     |-D4 - D5
     |-D5 - D4
     |-D6 - D3
     |-D7 - D2
     |-RW - gnd

     For more information about wiring LCD go to
     the LCD_Diagram Tab

                      Commands
   -animation
    |-syntax: animation 1 or animation 0

   -Version
    |-syntax: Version

   -playSound
    |-syntax: playSound

   -ServoMove
    |-syntax: ServoMove

   To use commands open serial monitor, type command 
   in text bar and press "Send".



   2020 ardUX owned and maintained by Cashton Harmer
                     May 5th 2020
