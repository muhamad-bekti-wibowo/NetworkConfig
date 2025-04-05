#include <Arduino.h>
const char MainWebPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Redirecting to /config in 10 seconds</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            text-align: center;
            margin-top: 50px;
            background-color: #f5f5f5;
        }
        .countdown {
            font-size: 24px;
            color: #333;
            margin: 20px 0;
        }
        .timer {
            font-size: 36px;
            font-weight: bold;
            color: #2c3e50;
        }
        a {
            color: #3498db;
            text-decoration: none;
        }
        a:hover {
            text-decoration: underline;
        }
    </style>
</head>
<body>
    <h1>Anda akan dialihkan ke halaman /config</h1>
    <div class="countdown">
        Redirect dalam: <span class="timer" id="countdown">10</span> detik
    </div>
    <p>Jika tidak dialihkan otomatis, silakan <a href="/config">klik di sini</a>.</p>

    <script>
        // Hitungan mundur 10 detik
        let seconds = 10;
        const countdownElement = document.getElementById('countdown');
        
        const countdownInterval = setInterval(() => {
            seconds--;
            countdownElement.textContent = seconds;
            
            if (seconds <= 0) {
                clearInterval(countdownInterval);
                window.location.href = "/config";
            }
        }, 1000);
    </script>
</body>
</html>
)=====";