
//--------------------------------------      ( BEN YOUNES IHAB )
void webServer()
{   
    //--------------------------------------------config.css
    server.on("/config.css",streamCssFile); 
    //-------------------------------------------- loginpage.html                                                                                                                                                                             
    server.on("/", []() {
      error = "";
      streamFile("loginpage.html");
    });
    //--------------------------------------------home.html
    server.on("/home.html", []() { 
      error = "";     
      WiFiClient c = server.client();
      IPAddress CurrentClientIP = c.remoteIP();
      if (IPClient == CurrentClientIP) {
      streamFile("home.html");
      }else {
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html");
      }
    }); 
    //--------------------------------------------configserveur.html 
    server.on("/configserveur.html", []() {
      error = "";
      WiFiClient c = server.client();
      IPAddress CurrentClientIP = c.remoteIP();
      if (IPClient == CurrentClientIP) {
      streamFile("configserveur.html");
      }else {
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html");
      }
    });
    //--------------------------------------------configcompte
    server.on("/configcompte.html", []() {
      error = "";
      WiFiClient c = server.client();
      IPAddress CurrentClientIP = c.remoteIP();
      if (IPClient == CurrentClientIP) {
      streamFile("configcompte.html");
      }else {
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html");
      }
    });
    //--------------------------------------------config.html
    server.on("/config.html", []() {
      error = "";
      WiFiClient c = server.client();
      IPAddress CurrentClientIP = c.remoteIP();
      if (IPClient == CurrentClientIP) {
      streamFile("config.html");
      }else {
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html");
      }
    });
    //--------------------------------------------configwifi.html
    server.on("/configwifi.html", []() {
      error = "";
      WiFiClient c = server.client();
      IPAddress CurrentClientIP = c.remoteIP();
      if (IPClient == CurrentClientIP) {
      streamFile("configwifi.html");
      }else {
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html");
      }
    });
    //--------------------------------------------------------------HOME
    server.on("/home", []() { 
      String _username = server.arg("username");
      String _psw = server.arg("psw");
      String _remember = server.arg("remember");
      int lusername = _username.length() + 131  ;
      int lpsw = _psw.length() + 97 ;
      String epsw ="";
      String eusername ="";
      String val = "01";
      epsw += readeeprom(97,lpsw); 
      eusername += readeeprom(131,lusername);
      Serial.print("Remember box value : ");
      Serial.println(_remember);
      Serial.print("PASS: ");
      Serial.println(epsw );
      Serial.print("USERNAME: ");
      Serial.println(eusername );
      Serial.print("Entred username  :");
      Serial.println(_username);
      Serial.print("Entred Pass  :");
      Serial.println(_psw);
      if ((_username.length()) > 0 && (_psw.length() > 0) && (eusername==_username)&& (epsw==_psw) ) {
        Serial.println("Opening home");
        error="";
        if (_remember=="1"){
          EEPROM.write(355, val[1]);
        }
        else{
          EEPROM.write(355, val[0]);
        }
        EEPROM.commit();
        WiFiClient c = server.client();
         IPClient = c.remoteIP();
        Serial.print("IPClient : ");
        Serial.println(IPClient);
        streamFile("home.html");
      }
      else {
        Serial.println("Writing Error");
        error = "Le nom d'utilisateur ou le mot de passe est incorrect.";
        streamFile("loginpage.html");
      }
    });
    //--------------------------------------------------------------WIFI CONFIG
    server.on("/setting", []() {
      WiFiClient c = server.client();
      IPAddress CurrentClientIP = c.remoteIP();
      if (IPClient == CurrentClientIP) {
        String qsid = server.arg("ssid");
        String qpass = server.arg("pass");
        if (qsid.length() > 0 && qpass.length() > 0) {
          Serial.println("clearing eeprom");
          for (int i = 0; i < 96; ++i) {
            EEPROM.write(i, 0);
          }
          Serial.println(qsid);
          Serial.println(qpass);
          Serial.println("writing eeprom ssid:");
          for (int i = 0; i < qsid.length(); ++i)
          {
            EEPROM.write(i, qsid[i]);
            Serial.print("Wrote ssid: ");
            Serial.println(qsid[i]);
          }
          Serial.println("writing eeprom pass:");
          for (int i = 0; i < qpass.length(); ++i)
          {
            EEPROM.write(32 + i, qpass[i]);
            Serial.print("Wrote pass: ");
            Serial.println(qpass[i]);
          }
          EEPROM.write(32 + qpass.length(), '\0');
          EEPROM.commit();
          error="";
          streamFile("configwifi.html");
        } else {
            Serial.println("Writing Error");
            error = "SSID ou Cle pas valide";
            streamFile("configwifi.html");
        } 
      }
      else {
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html");
      } 
    });
    //--------------------------------------------------------------ACCOUNT PASSWORD CONFIG 
      server.on("/comptepass", []() { 
        WiFiClient c = server.client();
        IPAddress CurrentClientIP = c.remoteIP();
        if (IPClient == CurrentClientIP) {
          String _currentpass = server.arg("currentpass");
          String _newpass = server.arg("newpass");
          String _confirmpass = server.arg("confirmpass");
          String ecurrentpass= "";
          int l = _currentpass.length() +97 ;
          Serial.println("Reading EEPROM CURRENTPASS");
          ecurrentpass += readeeprom(97,l);
          Serial.print("CURRENTPASS : ");
          Serial.println(ecurrentpass);
          Serial.print("Entred current pass : ");
          Serial.println(_currentpass);
          Serial.print("New pass : ");
          Serial.println(_newpass);
          Serial.print("Confirm Pass : ");
          Serial.println(_confirmpass);
          if ((_currentpass.length() > 0) && (_newpass.length() > 0) & (_confirmpass.length() > 0) && (_newpass == _confirmpass) && (ecurrentpass == _currentpass))  {
            Serial.println("clearing eeprom");
            for (int i = 97; i < 130; ++i) {
              EEPROM.write(i, 0);
            }
            Serial.println("writing eeprom currentpass :");
            for (int i = 0; i < _newpass.length(); ++i)
            {
              EEPROM.write(97 + i, _newpass[i]);
              Serial.print("Wrote new pass: ");
              Serial.println(_newpass[i]);
            }
            EEPROM.commit();
            error="";
            streamFile("configcompte.html");
        } else {
            Serial.println("Writing Error");
            error = "Nom d'utilisateur, Ancien mot de passe ou confirmation mot de passe invalide";
            streamFile("configcompte.html");
        }
        }
      else {
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html");
      }  
    });
    //--------------------------------------------------------------ACCOUNT USER CONFIG  
    server.on("/compteuser", []() {
      WiFiClient c = server.client();
      IPAddress CurrentClientIP = c.remoteIP();
      if (IPClient == CurrentClientIP) {
        String _user = server.arg("user");
        if (_user.length() > 0) {
          Serial.println("clearing eeprom");
          for (int i = 131; i < 170; ++i) {
            EEPROM.write(i, 0);
          }
          Serial.println(_user);
          Serial.println("");
          Serial.println("writing eeprom user:");
          for (int i = 0; i < _user.length(); ++i)
          {
            EEPROM.write(131 + i, _user[i]);
            Serial.print("Wrote user : ");
            Serial.println(_user[i]);
          }
          EEPROM.commit();
          error="";
          streamFile("configcompte.html");
        } else {
            Serial.println("Writing Error");
            error = "Nom d'utilisateur, Ancien mot de passe ou confirmation mot de passe invalide";
            streamFile("configcompte.html");
        }
      }
      else {
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html");
      } 
    });
    //--------------------------------------------------------------CONFIG ESP IP
    server.on("/ipcapteur", []() {
      WiFiClient c = server.client();
      IPAddress CurrentClientIP = c.remoteIP();
      if (IPClient == CurrentClientIP) {
        String _ip = server.arg("ip");
        String _dns = server.arg("dns");
        String _gateway = server.arg("gateway");
        String _subnet = server.arg("subnet");
        String _demo = server.arg("demo5");
        // && (CheckMask(_subnet)==true)
        IPAddress ip;
        if ((_ip.length() > 0 ) && (_dns.length() > 0) && (_gateway.length() > 0) && (_subnet.length() > 0 ) && (CheckMask(_subnet)==true) && (ip.fromString(_ip)) && (ip.fromString(_dns)) && (ip.fromString(_gateway)) && (ip.fromString(_subnet) )) {
          Serial.println("clearing eeprom");
          for (int i = 171; i < 300; ++i) {
            EEPROM.write(i, 0);
          }
          Serial.print("  IP : ");
          Serial.println(_ip);
          Serial.print("  DNS : ");
          Serial.println(_dns);
          Serial.print("  Gateway : ");
          Serial.println(_gateway);
          Serial.print("  Subnet : ");
          Serial.println(_subnet);
          Serial.print("State : ");
          Serial.println(_demo);
          Serial.print("writing eeprom ip : ");
          for (int i = 0; i < _ip.length(); ++i)
          {
            EEPROM.write(171 + i, _ip[i]);
            Serial.println(_ip[i]);
          }
          Serial.println("  writing eeprom dns:");
          for (int i = 0; i < _dns.length(); ++i)
          {
            EEPROM.write(203 + i, _dns[i]);
           // Serial.print("  Wrote DNS : ");
            Serial.println(_dns[i]);
          }
          Serial.println("  writing eeprom gateway:");
          for (int i = 0; i < _gateway.length(); ++i)
          {
            EEPROM.write(235 + i, _gateway[i]);
            //Serial.print("  Wrote Gateway: ");
            Serial.println(_gateway[i]);
          }
          Serial.println("  writing eeprom subnet:");
          for (int i = 0; i < _subnet.length(); ++i)
          {
            EEPROM.write(265 + i, _subnet[i]);
           // Serial.print("  Wrote Subnet: ");
            Serial.println(_subnet[i]);
          }
          Serial.println("STATIC MODE");
          EEPROM.write(350, _demo[0]);
          EEPROM.commit();
          error="";
          streamFile("config.html");
        } 
        else if (_demo=="1"){
          Serial.print("DHCP MODE : ");
          Serial.println(_demo[0]);
          EEPROM.write(350, _demo[0]);
          EEPROM.commit();
          error="";
          streamFile("config.html");
        }
        else {
          Serial.println("Writing Error");
          error = "Format IP/Masque pas valide";
          streamFile("config.html");
        }
      }
      else{
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html");   
      }
    });
    //--------------------------------------------------------------CONFIG SERVER IP
    server.on("/ipserveur", []() {
      WiFiClient c = server.client();
      IPAddress CurrentClientIP = c.remoteIP();
      if (IPClient == CurrentClientIP) {
        String _ipserv = server.arg("ipserv");
        IPAddress ips;
        // + checking ip
        if ((_ipserv.length() > 0) && (ips.fromString(_ipserv)) ) {
          Serial.println("clearing eeprom");
          for (int i =301; i < 332; ++i) {
            EEPROM.write(i, 0);
          }
          Serial.println("  IP SERV :");
          Serial.println(_ipserv);
          Serial.println("writing eeprom serevr ip : ");
          for (int i = 0; i < _ipserv.length(); ++i)
          {
            EEPROM.write(301 + i, _ipserv[i]);
            Serial.println(_ipserv[i]);
          }
          EEPROM.write(301 + _ipserv.length(), '\0');
          EEPROM.commit();
          error="";
          streamFile("configserveur.html");
        }
        else {
          Serial.println("Writing Error");
          error = "Format IP pas valide";
          streamFile("configserveur.html");
        }
      }
      else{
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html"); 
      }
    });
    //--------------------------------------------------------------RELAYPIN CONFIG 
    server.on("/onoff", []() {
      WiFiClient c = server.client();
      IPAddress CurrentClientIP = c.remoteIP();
      if (IPClient == CurrentClientIP) {
        String _relay = server.arg("relay");
        if(_relay=="1"){
          Serial.println("ON / relayPin and ledPin HIGHT");
          digitalWrite(relayPin, HIGH); 
          digitalWrite(ledPin, HIGH);            
        }else
        {
          Serial.println("OFF / relayPin and ledPin LOW");
          digitalWrite(relayPin, LOW); 
          digitalWrite(ledPin, LOW);              
        }
        streamFile("home.html");
      }
      else{
        error = "Authentification requise, veuillez vous connecter à votre compte";
        streamFile("loginpage.html");
      }
    });
    //-------------------------------------------------------------------HTTP GET
    server.on("/ipw", HTTP_GET, [](){
      server.send_P(200, "text/plain", getIP().c_str());
    });
    server.on("/subw", HTTP_GET, [](){
      server.send_P(200, "text/plain", getSUBNET().c_str());
    });
    server.on("/gatw", HTTP_GET, [](){
      server.send_P(200, "text/plain", getGATEWAY().c_str());
    });
    server.on("/macw", HTTP_GET, [](){
      server.send_P(200, "text/plain", getMAC().c_str());
    });
    server.on("/error", HTTP_GET, [](){
      server.send_P(200, "text/plain", error.c_str());
    });
    server.on("/ssid", HTTP_GET, [](){
      server.send_P(200, "text/plain", readeeprom(0,32).c_str());
    });
    server.on("/pass", HTTP_GET, [](){
      String b = ConvertPsw(secondread(32));
      server.send_P(200, "text/plain", b.c_str());
    });
    server.on("/ipserv", HTTP_GET, [](){
      server.send_P(200, "text/plain", readeeprom(301,332).c_str());
    });
    server.on("/servip", HTTP_GET, [](){
      server.send_P(200, "text/plain", secondread(301).c_str());
    });
    server.on("/ip", HTTP_GET, [](){
      server.send_P(200, "text/plain", readeeprom(171,202).c_str());
    });
    server.on("/dns", HTTP_GET, [](){
      server.send_P(200, "text/plain", readeeprom(203,234).c_str());
    });
    server.on("/subnet", HTTP_GET, [](){
      server.send_P(200, "text/plain", readeeprom(265,300).c_str());
    });
    server.on("/gateway", HTTP_GET, [](){
      server.send_P(200, "text/plain", readeeprom(235,264).c_str());
    });
    server.on("/ssid", HTTP_GET, [](){
      server.send_P(200, "text/plain", readeeprom(0,32).c_str());
    });
    server.on("/state", HTTP_GET, [](){
      server.send_P(200, "text/plain", GetLedstate().c_str());
    });
    server.on("/remember", HTTP_GET, [](){
      server.send_P(200, "text/plain", rememberBox().c_str());
    });    
    server.on("/mode", HTTP_GET, [](){
      server.send_P(200, "text/plain", GetMode().c_str());
    }); 
}
