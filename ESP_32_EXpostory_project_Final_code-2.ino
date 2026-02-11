#include <WiFi.h>

// ===== WiFi Login =====
const char* ssid     = "WIFI name";
const char* password = "Password";

// ===== Pins =====
#define RELAY1  12   // Relay control pin (active LOW)

// ===== Web Server =====
WiFiServer server(80);

// ===== HTML Page (Raw Literal) =====
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="IoT-Based Air Purifier project by Waleed Asif, Anis Shah Gillani, and Adnan Liaqat from Air University, Islamabad. Learn about the design, implementation, and control system using recycled hardware.">
    <meta name="keywords" content="IoT, Air Purifier, Recycled Hardware, ESP32, Mechatronics, Biomedical Engineering">
    <title>Design and Implementation of an IoT-Based Air Purifier Using Fully Recycled Hardware</title>
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400;500;700&display=swap" rel="stylesheet">
    <style>
        body {
            font-family: 'Roboto', Arial, sans-serif;
            margin: 0;
            padding: 0;
            background-color: #003366;
            color: #333;
            line-height: 1.6;
        }
        .header {
            text-align: center;
            background: linear-gradient(135deg, #004080, #0066cc);
            color: white;
            padding: 40px 20px;
            font-size: 2.5rem;
            font-weight: 700;
            box-sh
            
            adow: 0 4px 8px rgba(0,0,0,0.3);
        }
        .sub-header {
            font-size: 1.2rem;
            font-style: italic;
            color: #ffffff;
            margin-bottom: 40px;
            text-align: center;
            font-weight: 500;
            padding: 20px;
            background-color: rgba(255,255,255,0.1);
        }
        .tabs {
            display: flex;
            justify-content: center;
            background-color: #004080;
            padding: 15px;
            box-shadow: 0 2px 4px rgba(0,0,0,0.2);
        }
        .tabs a {
            text-decoration: none;
            color: white;
            padding: 15px 30px;
            margin: 0 10px;
            border-radius: 5px;
            background-color: #555;
            transition: all 0.3s ease;
            font-weight: 500;
        }
        .tabs a:hover {
            background-color: #777;
            transform: translateY(-2px);
        }
        .content {
            max-width: 1200px;
            margin: 0 auto;
            padding: 40px 20px;
            background-color: #ffffff;
            border-radius: 10px;
            margin-top: 20px;
            box-shadow: 0 4px 12px rgba(0,0,0,0.1);
        }
        .cream-background {
            background-color: #faf0e6;
            padding: 30px;
            color: #333;
            font-size: 1.5rem;
            font-weight: 500;
            margin-top: 20px;
            border-radius: 10px;
            text-align: center;
            border: 1px solid #ddd;
            box-shadow: 0 2px 6px rgba(0,0,0,0.1);
        }
        .slider-container {
            text-align: center;
            margin-top: 50px;
        }
        .switch {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;
        }
        .switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }
        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: #ccc;
            transition: 0.4s;
            border-radius: 50px;
        }
        .slider:before {
            position: absolute;
            content: "";
            height: 26px;
            width: 26px;
            border-radius: 50px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            transition: 0.4s;
        }
        input:checked + .slider {
            background-color: #4CAF50;
        }
        input:checked + .slider:before {
            transform: translateX(26px);
        }

        .animation-text {
            font-size: 1.5rem;
            color: #333;
            font-weight: 500;
            text-align: center;
            padding: 20px;
        }

        .slider-speed-container {
            margin-top: 30px;
            color: #333;
            text-align: center;
        }
        .slider-speed-container label {
            font-size: 1.2rem;
            font-weight: 500;
        }

        .about-us-content {
            background-color: #faf0e6;
            color: #333;
            padding: 30px;
            border-radius: 10px;
            margin-top: 20px;
            box-shadow: 0 2px 6px rgba(0,0,0,0.1);
        }
        .about-us-content h2 {
            font-size: 1.8rem;
            font-weight: 700;
            margin-bottom: 20px;
        }
        .about-us-content p {
            margin-bottom: 15px;
        }

        footer {
            background-color: #004080;
            color: white;
            text-align: center;
            padding: 20px;
            margin-top: 40px;
            font-size: 0.9rem;
        }
        footer a {
            color: #add8e6;
            text-decoration: none;
        }
        footer a:hover {
            text-decoration: underline;
        }

        @keyframes fadeIn {
            from { opacity: 0; transform: translateY(20px); }
            to { opacity: 1; transform: translateY(0); }
        }
        .header, .sub-header, .content {
            animation: fadeIn 1s ease-out;
        }
    </style>
</head>
<body>

    <div class="header">
        Design and Implementation of an IoT-Based Air Purifier Using Fully Recycled Hardware
    </div>

    <div class="sub-header">
        Waleed Asif (242052) | Anis Shah Gillani (242073) | Adnan Liaqat (242039)<br>
        Department of Mechatronics Engineering and Biomedical Engineering, Air University, Islamabad<br>
        Supervisor: Fizza Farukh
    </div>

    <div class="tabs">
        <a href="#control-system">Control System</a>
        <a href="#project-details">Project Details</a>
        <a href="#about">About Us</a>
    </div>

    <!-- Control System Section -->
    <div class="content" id="control-system">
        <div class="cream-background">
            <h2>Control System</h2>
        </div>
        
        <div class="cream-background">
            <h3>Control Panel</h3>
            <p>This interactive control panel allows real-time management of the air purifier's fan and speed settings.</p>
        </div>

        <div class="slider-container">
            <label>Fan Status:</label><br>
            <label class="switch">
                <input type="checkbox" id="fan-switch">
                <span class="slider"></span>
            </label><br><br>
            <label id="fan-status">OFF</label>
        </div>

        <div class="slider-speed-container">
            <label>Fan Speed (0 to 100):</label><br>
            <input type="range" id="speed-control" name="speed" min="0" max="100" value="0">
            <br><br>
            <label id="speed-status">0</label>
        </div>

        <div class="cream-background">
            <div class="animation-text">
                This project demonstrates sustainable engineering practices through the use of recycled materials in IoT applications.
            </div>
        </div>
    </div>

    <!-- Project Details Section -->
    <div class="content" id="project-details">
        <h2>Project Details</h2>
        <p><strong>IoT-Based Air Purifier Made from Recycled Components — My Complete DIY Build</strong></p>
        <p>Indoor air quality matters more today than ever before. But instead of buying an expensive commercial air purifier, I decided to create my own — using IoT technology, upcycled materials, and a few essential electronics. The goal was simple:</p>
        <ul>
            <li>✔ Build a low-cost air purifier</li>
            <li>✔ Use recycled components</li>
            <li>✔ Add IoT monitoring and automation</li>
            <li>✔ Make something powerful, sustainable, and fully DIY</li>
        </ul>
        <p>This project turned into a working IoT-based smart air purifier, all powered by an ESP32 microcontroller and old parts that would otherwise have gone to waste.</p>
        <p><strong>⭐ Why I Built an IoT-Based Air Purifier</strong></p>
        <p>I wanted a purifier that:</p>
        <ul>
            <li>Cleans air effectively using real car-grade air filters</li>
            <li>Runs on low power</li>
            <li>Uses IoT for remote monitoring and control</li>
            <li>Is built entirely from recycled and reused materials</li>
            <li>Costs much less than commercial purifiers</li>
        </ul>
        <p>With this in mind, I collected old components like laptop chargers, car air filters, wooden leftover pieces, and 3D-printed parts.</p>

        <p><strong>🧰 Components Used (Mostly Recycled)</strong></p>
        <h3>Electronics</h3>
        <ul>
            <li>ESP32 microcontroller – for Wi-Fi + IoT control</li>
            <li>Two LM2596 buck converters</li>
            <li>1 for the 12V car fan</li>
            <li>1 for ESP32 + 5V Relay</li>
            <li>5V Relay Module – for switching the fan</li>
            <li>24V old laptop charger – main power supply</li>
            <li>Cooling Fan (from old PC/car AC duct)</li>
        </ul>
        <h3>Mechanical + Recycled Parts</h3>
        <ul>
            <li>Three car air filters (reused, cleaned, and combined)</li>
            <li>Custom wooden structure – top + bottom plates for airflow</li>
            <li>3D-Printed Electronics Box – holds ESP32, LM2596s, relay, power input</li>
            <li>Scrap wires and connectors</li>
        </ul>

        <p><strong>🔧 Step-By-Step: How I Built the Purifier</strong></p>
        <h3>Step 1: Designing the Airflow System</h3>
        <p>I started with three old car air filters. They were cleaned thoroughly and arranged in a box-like structure to increase the surface area for maximum filtration.</p>
        <p>The fan was mounted on the top wooden plate, pulling air upward. The bottom wooden plate allows air intake from below. Air moves through all filters and exits purified from the top.</p>
        <p>This created a vertical airflow design, similar to commercial HEPA purifiers.</p>

        <h3>Step 2: Making the Purifier Body</h3>
        <p>Wooden Base and Top</p>
        <p>I cut two wooden plates:</p>
        <ul>
            <li>Bottom plate → holds the filter box</li>
            <li>Top plate → holds the fan</li>
        </ul>
        <p>3D-Printed Electronics Box</p>
        <p>I designed and printed a compact casing to store:</p>
        <ul>
            <li>ESP32</li>
            <li>Both LM2596 buck converters</li>
            <li>Relay</li>
            <li>Wiring and connectors</li>
        </ul>
        <p>This box attaches neatly to the side of the filter unit.</p>

        <h3>Step 3: Power Management Using Recycled LM2596 Converters</h3>
        <p>Since I used a 24V old laptop charger, I had to step down voltages:</p>
        <ul>
            <li>LM2596 #1 → 12V for the Fan</li>
            <li>LM2596 #2 → 5V for ESP32 and Relay</li>
        </ul>
        <p>This allowed me to:</p>
        <ul>
            <li>Power everything from one old charger</li>
            <li>Avoid buying new adapters</li>
            <li>Keep the setup clean and efficient</li>
        </ul>

        <h3>Step 4: Installing the Fan</h3>
        <p>The fan sits at the top, tightly fixed with screws. It pulls air through the filters, and air exits upward. The strong airflow helps remove dust and pollutants.</p>
        <p>I made sure the edges were sealed so that all air must pass through the filters.</p>

        <h3>Step 5: Wiring the Electronics</h3>
        <p>Wiring included:</p>
        <ul>
            <li>24V → LM2596 (12V) → Fan</li>
            <li>24V → LM2596 (5V) → Relay + ESP32</li>
            <li>Relay signal pin → ESP32 GPIO</li>
            <li>ESP32 connected to Wi-Fi for IoT control</li>
        </ul>
        <p>I kept all cables inside the 3D-printed box for safety and neatness.</p>

        <h3>💡 Step 6: IoT Features (Powered by ESP32)</h3>
        <ul>
            <li>✔ Wi-Fi Control</li>
            <li>✔ Real-Time Monitoring</li>
            <li>✔ Automation</li>
            <li>✔ Cloud Dashboard (optional)</li>
        </ul>

        <p>This turned a simple purifier into a smart purifier.</p>

        <h3>🎉 Final Assembly</h3>
        <p>All components were mounted:</p>
        <ul>
            <li>Filters enclosed in a sturdy box</li>
            <li>Fan fitted on top plate</li>
            <li>Power cable connected</li>
            <li>3D printed electronics box fixed on the side</li>
        </ul>

        <p>The final build looked clean, modern, and surprisingly powerful — despite being made mostly from recycled parts.</p>

        <p><strong>🌿 Environmental Impact</strong></p>
        <p>This project used components that would otherwise be thrown away:</p>
        <ul>
            <li>Old laptop charger</li>
            <li>Discarded car air filters</li>
            <li>Recycled wood</li>
            <li>Spare cooling fan</li>
            <li>Reused LM2596 modules</li>
        </ul>
        <p>It proves that sustainability + technology can work together beautifully.</p>

        <p><strong>🧪 Performance & Testing</strong></p>
        <p>The purifier was tested in a closed room:</p>
        <ul>
            <li>Dust smell reduced noticeably</li>
            <li>Airflow was strong due to powerful fan</li>
            <li>Filters captured visible dust within days</li>
            <li>ESP32 remote control worked flawlessly</li>
        </ul>
        <p>Adding optional sensors (PM2.5, CO₂, VOC) can make it even more advanced.</p>

        <p><strong>📌 Conclusion</strong></p>
        <p>This IoT-Based Air Purifier Using Recycled Materials is:</p>
        <ul>
            <li>Affordable</li>
            <li>Eco-friendly</li>
            <li>Functional</li>
            <li>Smart</li>
            <li>Easy to build</li>
            <li>Highly customizable</li>
        </ul>
        <p>It’s a great project for anyone interested in IoT, sustainability, and DIY engineering.</p>
    </div>

    <!-- About Us Section -->
    <div class="content" id="about">
        <div class="cream-background">
            <h2>About Us</h2>
        </div>
        <div class="about-us-content">
            <h2>Project Team</h2>
            <p><strong>Team Members:</strong> Waleed Asif (242052), Anis Shah Gillani (242073), Adnan Liaqat (242039)</p>
            <p><strong>Department:</strong> Department of Mechatronics Engineering and Biomedical Engineering, Air University, Islamabad</p>
            <p><strong>Supervisor:</strong> Fizza Farukh</p>
            <p><strong>Contact Information:</strong></p>
            <p>Email: <a href="mailto:waleedasif651@gmail.com">waleedasif651@gmail.com</a></p>
        </div>
    </div>

    <footer>
        <p>&copy; 2023 Air University Project. All rights reserved. | <a href="#top">Back to Top</a></p>
    </footer>

    <!-- JavaScript for Fan & Speed Control -->
    <script>
        const fanSwitch = document.getElementById('fan-switch');
        const fanStatus = document.getElementById('fan-status');
        const speedControl = document.getElementById('speed-control');
        const speedStatus = document.getElementById('speed-status');
        
        fanSwitch.addEventListener('change', function() {
            if (fanSwitch.checked) {
                fanStatus.textContent = 'ON';
                fetch('/ON');
            } else {
                fanStatus.textContent = 'OFF';
                fetch('/OFF');
            }
        });

        speedControl.addEventListener('input', function() {
            speedStatus.textContent = speedControl.value;
            fetch('/speed?value=' + speedControl.value);
        });
    </script>

</body>
</html>
)=====";


// ===== Helper to send small plain-text response for AJAX calls =====
void sendSimpleOK(WiFiClient &client) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/plain");
  client.println("Connection: close");
  client.println();
  client.println("OK");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n==============================");
  Serial.println("   ESP32 IoT Air Purifier UI  ");
  Serial.println("==============================\n");

  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, HIGH);   // Relay OFF initially (active LOW)
  Serial.println("Relay Initialized → OFF");

  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    attempts++;
    if (attempts > 30) {
      Serial.println("\nWiFi Failed! Restarting ESP32...");
      ESP.restart();
    }
  }

  Serial.println("\n\nWiFi Connected Successfully!");
  Serial.print("ESP32 IP Address → ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  server.begin();
  Serial.println("Web Server Started on Port 80\n");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("⚠ WiFi Lost! Attempting Reconnect...");
    WiFi.reconnect();
    delay(2000);
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client Connected!");

    String request = client.readStringUntil('\r');
    Serial.print("Request: ");
    Serial.println(request);
    client.flush();

    // ---- Route Handling ----

    // Turn Relay ON
    if (request.indexOf("GET /ON") != -1) {
      digitalWrite(RELAY1, LOW);   // active LOW
      Serial.println("Relay → ON");
      sendSimpleOK(client);
    }
    // Turn Relay OFF
    else if (request.indexOf("GET /OFF") != -1) {
      digitalWrite(RELAY1, HIGH);
      Serial.println("Relay → OFF");
      sendSimpleOK(client);
    }
    // Speed control (from slider)
    else if (request.indexOf("GET /speed?value=") != -1) {
      int idx = request.indexOf("GET /speed?value=") + strlen("GET /speed?value=");
      int endIdx = request.indexOf(' ', idx);
      String speedStr = request.substring(idx, endIdx);
      int speedVal = speedStr.toInt();
      Serial.print("Speed value received → ");
      Serial.println(speedVal);
      // Here you can map speedVal (0–100) to PWM and control a fan if you add hardware
      sendSimpleOK(client);
    }
    // Default: serve the full HTML page
    else {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");
      client.println();
      client.print(MAIN_page);
    }

    client.stop();
    Serial.println("Client Disconnected\n");
  }
}
