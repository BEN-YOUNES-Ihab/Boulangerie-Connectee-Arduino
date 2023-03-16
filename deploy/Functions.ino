//--------------------------------------     ( BEN YOUNES IHAB )

//---------------------------------------------GET FUNCTIONS
String getIP() {
  IPAddress local = WiFi.localIP();
  String ip= convertTostring(local);
  return ip;
}
String getSUBNET() {
  IPAddress local = WiFi.subnetMask();
  String sub= convertTostring(local);
  return sub;
}
String getGATEWAY() {
  IPAddress local = WiFi.gatewayIP();
  String gat= convertTostring(local);
  return gat;
}
String getMAC() {
  String clientMac = "";
unsigned char mac[6];
WiFi.macAddress(mac);
clientMac += macToStr(mac);
return clientMac;
}
//---------------------------------------------------Read mode state
String GetMode(){
  String value;
  String emode;
  emode = char(EEPROM.read(350));
  if (emode == "1") { 
    value = "Automatique (DHCP)";
  }else{
    value = "Statique";
  }  
  return value;
}
//--------------------------------------------------READ LED STATE
String GetLedstate(){
      String state;
      if(digitalRead(ledPin)== HIGH){
        state="ON";
      }else{
        state="OFF";
      }
      return state;
}
//--------------------------------------------------READ EEPROM FUNCTIONS
String readeeprom(int n,int z){
  String ch = "";
  for (int i = n; i < z; ++i)
  {
    ch += char(EEPROM.read(i));
  }
  return ch;
}
String secondread(int i){
  String ch = "";
 while ( char(EEPROM.read(i)) != '\0'){
  ch += char(EEPROM.read(i)) ; 
  i++;
 }
return ch;
}

//--------------------------------------------------STREAM FILE FUNCTIONS
void streamFile(String x) {
   File f = LittleFS.open(x, "r");
   server.streamFile(f,"text/html");
   f.close();
}
void streamCssFile() {
   File f = LittleFS.open("config.css", "r");
   server.streamFile(f,"text/css");
   f.close();
}
//--------------------------------------------------CONVERT FUNCTIONS
IPAddress convertToip(String ipstr){
  IPAddress ip;
  if(ip.fromString(ipstr)){
  ip.fromString(ipstr);
  return ip ;
  }
}
String convertTostring(IPAddress adr ){
String ip="";
if(adr.toString()){
ip =  adr.toString();
return ip ;
}
}

String macToStr(const uint8_t* mac)
{
String result;
for (int i = 0; i < 6; ++i) {
result += String(mac[i], 16);
if (i < 5)
result += ':';
}
return result;
}

//--------------------------------------------------Convert Psw
String ConvertPsw(String a){
      String b ="";
      for (int i=0; i<a.length();i++)
        b=b+"*";
      return b;
}
//---------------------------------------------------check mask
boolean CheckMask(String mask){
      IPAddress _mask=convertToip(mask);
      boolean result ;
      int j=0;
      for (int i = 0 ; i<3 ; ++i){
       if (_mask[i] >= _mask[i+1]) {
          j++;
          }
      }
      if (j==3){ 
          result=true;
      }else{
      result=false;
      }
      return result;  
}
//---------------------------------------------------Read remember box state
String rememberBox(){
  String value;
  String eremember;
  eremember = char(EEPROM.read(355));
  if (eremember == "1") { 
    value = readeeprom(131,170);
  }else{
    value = "";
  }  
  return value;
}
