//--------------------------------------     ( BEN YOUNES IHAB )
//----------------------------------------------- Functions 
void launchWeb()
{
  Serial.println("");
  if (WiFi.status() == WL_CONNECTED)
    Serial.println("WiFi connected");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAP IP: ");
  Serial.println(WiFi.softAPIP());
  webServer();
  server.begin();
  Serial.println("Server started");
}
void configMode(void)
{
  WiFi.mode(WIFI_STA);      // SELECTING WIFI MODE
  WiFi.disconnect();       // DISCONECTING 
  delay(100);             // SCANING AVAILABLE WIFI
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0)
    Serial.println("No networks found");
  else
  {
    Serial.print(n);
    Serial.println("Networks found :");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      
      delay(10);
    }
  }
  delay(100);
  WiFi.softAP("ESP-1", "");
  Serial.println("Initializing softap for config mode");
  launchWeb();
  Serial.println("Over");
}
void testwifi(){
  if ((WiFi.status() == WL_CONNECTED))
  {
    for (int i = 0; i < 10; i++)
    {
      Serial.println("Connected  Successfully");
      Serial.println(WiFi.localIP());
      delay(10000);
    }
  }
  else
  {
    Serial.println("Unsuccessfully");
  }
}
