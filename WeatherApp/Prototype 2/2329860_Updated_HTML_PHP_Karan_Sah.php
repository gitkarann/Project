<!-- The DOCTYPE declaration specifies the version of HTML used in the document -->
<!DOCTYPE html>
<!-- Start of HTML document -->
<html lang="en">
  <!-- Head consists of metadata on the document, like encoding, title and stylesheets -->
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <meta http-equiv="X-UA-Compatible" content="ie=edge">
  <title>OpenWeatherMap Api</title>
  <link rel="stylesheet" href="2329860_Updated_CSS_Karan_Sah.css">
</head>
<!-- Body comprises of visible contents -->
<body>
  <!-- Header and form input to enter a city name is in main section -->
  <div class="main">
    <div class="header">
      <h1>OpenWeatherMap API</h1>
      <p>City Name is to be Entered for Weather Description</p>
    </div>

    <div class="input">
      <input type="text" placeholder="Enter the city" class="input_text">
      <input type="submit" value="Submit" class="submit">
    </div>
  </div>
<!-- Cards which display information on weather of every day is in container div -->
  <div class="container">
    <div class="card">
      <h1 class="name" id="name"></h1>
      <p class="temp"></p>
      <p class="wind"></p>
      <p class="humid"></p>
      <p class="clouds"></p>
      <p class="desc"></p>
    </div>
  </div>

  <div class="container">
    <div class="card">
      <h1 class="name">Bolton 2023-04-29</h1>
      <p class="temp">Temperature: 22 &deg;C</p>
      <p class="wind">Wind Speed: 12 km/h</p>
      <p class="humid">Humidity: 70%</p>
      <p class="clouds">Cloudiness: Mostly Sunny</p>
    </div>
  </div>

  <div class="container">
    <div class="card">
      <h1 class="name">Bolton 2023-04-30</h1>
      <p class="temp">Temperature: 20 &deg;C</p>
      <p class="wind">Wind Speed: 10 km/h</p>
      <p class="humid">Humidity: 65%</p>
      <p class="clouds">Cloudiness: Partly Cloudy</p>
    </div>
  </div>

  <div class="container">
    <div class="card">
      <h1 class="name">Bolton 2023-05-01</h1>
      <p class="temp">Temperature: 18 &deg;C</p>
      <p class="wind">Wind Speed: 8 km/h</p>
      <p class="humid">Humidity: 75%</p>
      <p class="clouds">Cloudiness: Scattered Showers</p>
    </div>
  </div>

  <div class="container">
    <div class="card">
      <h1 class="name">Bolton 2023-05-02</h1>
      <p class="temp">Temperature: 16 &deg;C</p>
      <p class="wind">Wind Speed: 6 km/h</p>
      <p class="humid">Humidity: 80%</p>
      <p class="clouds">Cloudiness: Rainy</p>
    </div>
  </div>

  <div class="container">
    <div class="card">
      <h1 class="name">Bolton 2023-05-03</h1>
      <p class="temp">Temperature: 15°C</p>
      <p class="wind">Wind Speed: 5 km/h</p>
      <p class="humid">Humidity: 75%</p>
      <p class="clouds">Cloudiness: Overcast</p>
      <p class="desc">Weather Description: Overcast</p>
    </div>
  </div>
  <div class="container">
    <div class="card">
      <h1 class="name">Bolton 2023-05-04</h1>
      <p class="temp">Temperature: 18°C</p>
      <p class="wind">Wind Speed: 10 km/h</p>
      <p class="humid">Humidity: 70%</p>
      <p class="clouds">Cloudiness: Partly cloudy</p>
      <p class="desc">Weather Description: Partly cloudy</p>
    </div>
  </div>
  <!-- Every container div has information for a certain day -->
  <div class="container">
    <div class="card">
      <h1 class="name">Bolton 2023-05-05</h1>
      <p class="temp">Temperature: 21°C</p>
      <p class="wind">Wind Speed: 15 km/h</p>
      <p class="humid">Humidity: 68%</p>
      <p class="clouds">Cloudiness: Sunny</p>
      <p class="desc">Weather Description: Sunny</p>
    </div>
  </div>
</div>
<!-- API call and the weather informations update is included in the script tag -->
 
  <script src="2329860_Updated_JS_Karan_Sah.js"></script>
</body>
<!-- The HTML document ended -->
</html>
<?php
//server details in connecting database
$servername = "localhost";
$database = "weatherapp";
$username = "root";
$password = "";

// Creating connection to database
$conn = mysqli_connect($servername, $username, $password, $database);

// Check connection whether it was successful else script termination
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

// Fetching weather data from OpenWeatherMap API and parsing to JSON data
$json_data = file_get_contents("https://api.openweathermap.org/data/2.5/weather?q=bolton&appid=9251fd367cbb3b3dd7495b1ddd664b90&units=metric");
$data = json_decode($json_data,true);
//Retrieve relevant data of weather from parsed JSON data
$city = $data['name'];
$temp = $data['main']['temp'];
$humidity = $data['main']['humidity'];
$windspeed =$data['wind']['speed'];
$description = $data['weather'][0]['description'];
$timestamp = $data['dt'];
$datetime = gmdate("Y-m-d\TH:i:s\Z", $timestamp);
$only_date = date('Y-m-d', $timestamp);

// Checking on whether the recent data already is in the database
$sql = "SELECT * FROM weatherapp WHERE DATE(datetime) = STR_TO_DATE('$only_date', '%d/%m/%Y')";
$result = mysqli_query($conn, $sql);

if (mysqli_num_rows($result) == 0) {
    // If no record is found for the current data, then insert a new one
    $sql = "INSERT INTO weatherapp(city,temperature,humidity,windspeed,description,datetime) VALUES('$city','$temp','$humidity','$windspeed','$description','$datetime')";
    if (!mysqli_query($conn,$sql)) {
        die("Error: " . mysqli_error($conn));
    }
}

// Collect the weather data from the database
$sql = "SELECT * FROM weatherapp";
$result = mysqli_query($conn, $sql);

?>
<!-- HTML table along with headers -->
<table>
    <thead>
        <tr>
            <th>City</th>
            <th>Temperature</th>
            <th>Humidity</th>
            <th>Wind Speed</th>
            <th>Discription </th>
            <th>Date</th>
        </tr>
    </thead>
    <tbody>
        <?php
        // Each row in the database result set is looped through
        while ($row = mysqli_fetch_assoc($result)) {
            while($row = mysqli_fetch_array($result)) {
                echo "<tr>";
                echo "<td>" . $row['city'] . "</td>";
                echo "<td>" . $row['temperature'] . "</td>";
                echo "<td>" . $row['humidity'] . "</td>";
                echo "<td>" . $row['windspeed'] . "</td>";
                echo "<td>" . $row['description'] . "</td>";
                echo "<td>" . $row['datetime'] . "</td>";
                echo "</tr>";
        }
    }
    // HTML table ended
        ?>
    </tbody>
</table>

<?php
mysqli_close($conn);
?>