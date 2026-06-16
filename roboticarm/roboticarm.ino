#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ESP32Servo.h>

// 🔴 WIFI
#define WIFI_SSID "Galaxy"
#define WIFI_PASSWORD "01234567890"

// 🔴 FIREBASE
#define API_KEY "AIzaSyB0-XbbOjKufubDSwxrITrRvQICGs451lo"
#define DATABASE_URL "https://roboticarmapp-default-rtdb.asia-southeast1.firebasedatabase.app/"

// 🔐 DEVICE CODE
#define DEVICE_CODE "ARM-ESP32-002"

// Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Servos
Servo baseServo, shoulderServo, elbowServo, wristServo, gripperServo, fingerServo;

// Pins
int basePin = 13;
int shoulderPin = 12;
int elbowPin = 14;
int wristPin = 27;
int gripperPin = 26;
int fingerPin = 25;

// Angles
int baseAngle = 90;
int shoulderAngle = 90;
int elbowAngle = 90;
int wristAngle = 90;
int gripperAngle = 90;
int fingerAngle = 90;

void setup() {
  Serial.begin(115200);

  Serial.println("Starting Robotic Arm...");
  Serial.print("Device Code: ");
  Serial.println(DEVICE_CODE);

  // WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nWiFi Connected");

  // Firebase config
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("Firebase Connected");

  // Attach servos
  baseServo.attach(basePin);
  shoulderServo.attach(shoulderPin);
  elbowServo.attach(elbowPin);
  wristServo.attach(wristPin);
  gripperServo.attach(gripperPin);
  fingerServo.attach(fingerPin);

  updateServos();
}

void loop() {
  String basePath = "/devices/" + String(DEVICE_CODE);

  Firebase.RTDB.getString(&fbdo, basePath + "/mode");
  String mode = fbdo.stringData();

  if (mode == "live") {
    handleLiveControl();
  }
  else if (mode == "record") {
    handleRecordState();
  }
  else if (mode == "play") {
    handlePlayState();
  }

  delay(200);
}

void handleLiveControl() {
  String p = "/devices/" + String(DEVICE_CODE) + "/live";

  Firebase.RTDB.getInt(&fbdo, p + "/base"); baseAngle = fbdo.intData();
  Firebase.RTDB.getInt(&fbdo, p + "/shoulder"); shoulderAngle = fbdo.intData();
  Firebase.RTDB.getInt(&fbdo, p + "/elbow"); elbowAngle = fbdo.intData();
  Firebase.RTDB.getInt(&fbdo, p + "/wrist"); wristAngle = fbdo.intData();
  Firebase.RTDB.getInt(&fbdo, p + "/gripper"); gripperAngle = fbdo.intData();
  Firebase.RTDB.getInt(&fbdo, p + "/finger"); fingerAngle = fbdo.intData();

  updateServos();
  printAngles();
}

void updateServos() {
  baseServo.write(baseAngle);
  shoulderServo.write(shoulderAngle);
  elbowServo.write(elbowAngle);
  wristServo.write(wristAngle);
  gripperServo.write(gripperAngle);
  fingerServo.write(fingerAngle);
}

void sendToFirebase() {
  String path = "/devices/" + String(DEVICE_CODE);

  Firebase.RTDB.setInt(&fbdo, path + "/base", baseAngle);
  Firebase.RTDB.setInt(&fbdo, path + "/shoulder", shoulderAngle);
  Firebase.RTDB.setInt(&fbdo, path + "/elbow", elbowAngle);
  Firebase.RTDB.setInt(&fbdo, path + "/wrist", wristAngle);
  Firebase.RTDB.setInt(&fbdo, path + "/gripper", gripperAngle);
  Firebase.RTDB.setInt(&fbdo, path + "/finger", fingerAngle);
}

void printAngles() {
  Serial.println("---- Movement ----");
  Serial.print("Base: "); Serial.println(baseAngle);
  Serial.print("Shoulder: "); Serial.println(shoulderAngle);
  Serial.print("Elbow: "); Serial.println(elbowAngle);
  Serial.print("Wrist: "); Serial.println(wristAngle);
  Serial.print("Gripper: "); Serial.println(gripperAngle);
  Serial.print("Finger: "); Serial.println(fingerAngle);
  Serial.println("------------------\n");
}

int recordStep = 0;

void handleRecordState() {
  handleLiveControl(); // follow sliders

  String basePath = "/devices/" + String(DEVICE_CODE);
  Firebase.RTDB.getString(&fbdo, basePath + "/currentState");
  String state = fbdo.stringData();

  String stepPath = basePath + "/states/" + state + "/" + String(recordStep);

  Firebase.RTDB.setInt(&fbdo, stepPath + "/base", baseAngle);
  Firebase.RTDB.setInt(&fbdo, stepPath + "/shoulder", shoulderAngle);
  Firebase.RTDB.setInt(&fbdo, stepPath + "/elbow", elbowAngle);
  Firebase.RTDB.setInt(&fbdo, stepPath + "/wrist", wristAngle);
  Firebase.RTDB.setInt(&fbdo, stepPath + "/gripper", gripperAngle);
  Firebase.RTDB.setInt(&fbdo, stepPath + "/finger", fingerAngle);

  Serial.print("Recorded step ");
  Serial.println(recordStep);

  recordStep++;
  delay(700);
}

void handlePlayState() {
  String basePath = "/devices/" + String(DEVICE_CODE);

  Firebase.RTDB.getString(&fbdo, basePath + "/currentState");
  String state = fbdo.stringData();

  Firebase.RTDB.getBool(&fbdo, basePath + "/loop");
  bool loopPlay = fbdo.boolData();

  int step = 0;

  do {
    step = 0;
    while (true) {
      String stepPath = basePath + "/states/" + state + "/" + String(step);

      if (!Firebase.RTDB.getInt(&fbdo, stepPath + "/base")) break;

      baseAngle = fbdo.intData();
      Firebase.RTDB.getInt(&fbdo, stepPath + "/shoulder"); shoulderAngle = fbdo.intData();
      Firebase.RTDB.getInt(&fbdo, stepPath + "/elbow"); elbowAngle = fbdo.intData();
      Firebase.RTDB.getInt(&fbdo, stepPath + "/wrist"); wristAngle = fbdo.intData();
      Firebase.RTDB.getInt(&fbdo, stepPath + "/gripper"); gripperAngle = fbdo.intData();
      Firebase.RTDB.getInt(&fbdo, stepPath + "/finger"); fingerAngle = fbdo.intData();

      updateServos();
      printAngles();

      delay(800);
      step++;
    }
  } while (loopPlay);
}

