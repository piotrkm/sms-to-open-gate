// #########################################################################################
//   __  ___  ___  _  _     __   __  ____  ___    ___  _  _    ___  __  __  ___ 
//  /  \(  ,\(  _)( \( )   / _) (  )(_  _)(  _)  (  ,)( \/ )  / __)(  \/  )/ __)
// ( () )) _/ ) _) )  (   ( (/\ /__\  )(   ) _)   ) ,\ \  /   \__ \ )    ( \__ \
//  \__/(_)  (___)(_)\_)   \__/(_)(_)(__) (___)  (___/(__/    (___/(_/\/\_)(___/
//
// #########################################################################################


#include "gsm.h"
#include "message.h"
#include "gate.h"

#define LED 13          // The pin 13 associated to the onboard LED
#define VERBOSE true    // Set the verbose mode;
                        // Initialise the verbose mode to (true = ON), (false = OFF)


gsmClass gsm {VERBOSE};        // Establish the gsm object
                               
gate GateObj {}; 
                        

                               
                               
// ################################################################
// 
//  Setup section 
//
// ################################################################
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                               // Start the hardware serial
  Serial.println();
  delay(1000);                                                      // Wait a second
  pinMode(LED, OUTPUT);                                             // Initialise the onboard LED
  
  if(gsm.get_verbose())
    Serial.println("\n### [       Program started !         ###]");   
  
    gsm.flush_to_serial();
 
    gsm.initialize();
    
 
  //gsm.send_sms("tresc smsa", "+447843782526");
  
} // END OF _SETUP_




// ################################################################
// 
//  Main loop section 
//
// ################################################################
void loop() {
  // put your main code here, to run repeatedly:

  {
    String incoming_message {};
    
    while(gsm.serial_available())
    {
      incoming_message = gsm.readFromGsm();
    } 
    
    if(incoming_message.substring(0, 5) == "+CLIP" )
      Serial.println("[###   SOMEONE IS CALLING !!!!    ###]");
    
     
    // =====================
    // INCOMING TEXT MESSAGE
    // =====================
    if(incoming_message.substring(0, 5) == "+CMT:" )
    {
      Serial.println("[###   SOMEONE SENT A TEXT !!!    ###]");
      
      message mes(incoming_message);
      String second_line {};
      while(gsm.serial_available())
        {   
          second_line = gsm.readFromGsm();
          mes.set_text(second_line);
        }
      
      if(VERBOSE)
        {
          Serial.print("SMS was sent from number: ");
          Serial.flush();
          Serial.println(mes.get_number());
          Serial.flush();
          Serial.print("Text of the message: ");
          Serial.flush();
          Serial.println(mes.get_text());
          Serial.flush();
        }
      
      
      // =====================
      // OPEN COMMAND
      // =====================
      if(mes.text_contains("OPEN"))
        {
          if(VERBOSE)
            Serial.println("Gate is going to open");
          
          GateObj.open_gate();  
          
        }

      // =====================
      // CLOSE COMMAND
      // =====================
      if(mes.text_contains("CLOSE"))
        {
          if(VERBOSE)
            Serial.println("Gate is going to close");
          
          GateObj.close_gate();  
        }
      
      //gsm.send_sms("Dzieki za SMSa", mes.get_number());
      

      // =====================
      // STATUS COMMAND
      // =====================
      if(mes.text_contains("STATUS"))
        {
          if(VERBOSE)
            Serial.println("Gate status requested");

          String status = GateObj.get_status();
          
          Serial.println(status);


          
        }

    }
    
    //Serial.print(incoming_message);
    //Serial.print(incoming_message.substring(0,5));

  // =========================
  //
  // GPRS CONNECTION
  //
  // =========================
  
  String list [] = {
    "AT+SAPBR=3,1,\"Contype\",\"GPRS\"",
    "AT+SAPBR=3,1,\"APN\",\"internet\"",
    "AT+SAPBR=1,1",
    "AT+SAPBR=2,1",
    "AT+HTTPINIT",
    "AT+HTTPPARA=\"CID\",1",
    "AT+HTTPPARA=\"URL\",\"pkmita.vxm.pl/date.php\"",
    "AT+HTTPACTION=0",
    "AT+SAPBR=0,1",
    "AT+HTTPREAD",
    "AT+HTTPTERM"
  };
  
  // for(size_t i{0}; i < 11; i++ )
  //   {
  //    
  //     gsm.send_command(list[i].c_str());
  //     delay(1500);
  //     while(gsm.serial_available())
  //       incoming_message = gsm.readFromGsm();
  //  
  //     Serial.println(incoming_message);
  //    
  //   }
  

  
  }
    
    
    
    
} // END OF _LOOP_
