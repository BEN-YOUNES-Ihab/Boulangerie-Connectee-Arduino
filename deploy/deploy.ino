#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <LittleFS.h>
#include <FS.h>
//--------------------------------------     ( BEN YOUNES IHAB )
String error="";
 IPAddress IPClient ;
//const int ledPin = BUILTIN_LED; //BUILTIN_LED
//const int switchPin= D1; 
//const int relayPin= D8;

const int ledPin = 2; //BUILTIN_LED
const int switchPin= 0; 
const int relayPin= 4;
//Function Decalration
void launchWeb(void);
void setupAP(void);
//Establishing Local server at port 80
ESP8266WebServer server(80);
//--------------------------------------------------------------SETUP
void setup()
{ 
  //--------------------------------------      ( BEN YOUNES IHAB )
  String esid;
  String epass = "";
  String eip = "";
  String edns = "";
  String egateway = "";
  String esubnet = "";
  String euser = "";
  String euserpass = "";
  String eipserv = "";
  String emode ="";
  String ebox ="";
  
  Serial.begin(115200); //Initialising if(DEBUG)Serial Monitor
  Serial.println("Disconnecting current wifi connection");
  WiFi.disconnect();
  WiFi.softAPdisconnect (true);
  EEPROM.begin(512); //Initialasing EEPROM
  LittleFS.begin();   //Initialasing LITTLEFS
  delay(10);
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  Serial.println();
  Serial.println("Startup");
  //---------------------------------------- Read eeprom for psw account
  euserpass = readeeprom(97,130);
  Serial.print("Password: ");
  Serial.println(euserpass);
  //------------------------------------Read eeprom for user account
  euser = readeeprom(131,170);
  Serial.print("USER: ");
  Serial.println(euser);
  //---------------------------------------- Read eeprom for ip 
  eip  = readeeprom(171,202);
  Serial.print("IP: ");
  Serial.println(eip);
  //------------------------------------Read eeprom for dns
  edns = readeeprom(203,234);
  Serial.print("DNS: ");
  Serial.println(edns);
  //------------------------------------Read eeprom for gateway
  egateway = readeeprom(235,264);
  Serial.print("GATEWAY: ");
  Serial.println(egateway);
  //------------------------------------Read eeprom for subnet
  esubnet = readeeprom(265,300);
  Serial.print("SUBNET: ");
  Serial.println(esubnet);
  //---------------------------------------- Read eeprom for server ip
  eipserv = secondread(301);
  Serial.print("SERVER IP : ");
  Serial.println(eipserv);
  //---------------------------------------- Read eeprom for ssid 
  esid = readeeprom(0,32);
  Serial.print("SSID: ");
  Serial.println(esid);
  //---------------------------------------- Read eeprom for  pass
  epass = readeeprom(32,96);
  Serial.print("PASS: ");
  Serial.println(epass);
  //---------------------------------------- Read eeprom for Remember Box
  ebox += char(EEPROM.read(355));
  Serial.print("Reading EEPROM Remember Box : ");
  Serial.println(ebox);
  //---------------------------------------- Read eeprom for DHCP/STATIC
  emode += char(EEPROM.read(350));
  Serial.print("Reading EEPROM DHCP(1) / STATIC(0) : ");
  Serial.println(emode);
  //---------------------------------------- CONNECTNG TO WIFI
  if (emode == "0") { //-----------------------------static or dhcp
    Serial.println("Static mode activated"); 
    WiFi.config(convertToip(eip),convertToip(edns),convertToip(egateway),convertToip(esubnet));
  }else{
    Serial.println("DHCP mode activated");
  }
  WiFi.begin(esid.c_str(), epass.c_str());
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
}

//-------------------------------------------------LOOP
void loop() {
 testwifi();
  if (digitalRead(switchPin) == LOW)
  {
    //--------------------------------------     ( CHORFA )
    //------------------------------------------- NORMAL MODE
    Serial.println("NORMAL MODE / D1 LOW ");
    delay(10000);
    return;
  }
  else
  {
    //--------------------------------------     ( BEN YOUNES IHAB)
    //------------------------------------------- CONFIG MODE
    Serial.println("CONFIG MODE  / D1 HIGH");                             
    configMode(); // Setup HotSpot
  }
  //----------------------------------------------HandleClient
  Serial.println("CONFIG MODE STARTED");
  while ((WiFi.status() != WL_CONNECTED))
  {
    server.handleClient();
  }
}
