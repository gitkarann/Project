
// Script for getting weather data for a user-input city
var input = document.querySelector('.input_text');//user input field
var main = document.querySelector('#name');//HTML element for city name
var temp = document.querySelector('.temp');//element for temperature
var wind = document.querySelector('.wind');//element for wind speed
var humid = document.querySelector('.humid');//element for humidity
var desc = document.querySelector('.desc');//element for weather brief discription
var clouds = document.querySelector('.clouds');//element for cloud covers
var button= document.querySelector('.submit');// select submit button element

button.addEventListener('click', function(name){
    // When the button is clicked, this function will run
fetch('https://api.openweathermap.org/data/2.5/weather?q='+input.value+'&appid=9251fd367cbb3b3dd7495b1ddd664b90&units=metric')
// This line fetches weather data from the OpenWeatherMap API for the city entered in the input field
.then(response => response.json())
//Relevent weather data is sotred in variabless after fetching data
.then(data => {
var tempValue = data['main']['temp'];
var nameValue = data['name'];
var humidValue=data['main']['humidity'];
var windValue=data['wind']['speed'];
var descValue = data['weather'][0]['description'];
//Setting the collected data for weather to the corresponding HTML elements
main.innerHTML = nameValue;
temp.innerHTML = "Temperature : "+tempValue +"°C";
humid.innerHTML= "Humidity : "+humidValue +"gm³";
wind.innerHTML="Wind : "+windValue +"m/s";
desc.innerHTML = "Description : "+descValue;
input.value ="";//After the weather data is displayed, clear the input field 

})
//Catch block for error hanlding if the input city does not exist
.catch(err => alert("The Written City Doesn't Exist. Please Input Valid City Name!"));

});


// Script for getting weather data for the city of Bolton
var boltonName = document.querySelector('#bolton-name');
var boltonTemp = document.querySelector('#bolton-temp');
var boltonWind = document.querySelector('#bolton-wind');
var boltonHumid = document.querySelector('#bolton-humid');
var boltonDesc = document.querySelector('#bolton-desc');
var boltonClouds = document.querySelector('#bolton-clouds');

fetch('https://api.openweathermap.org/data/2.5/weather?q=bolton&appid=9251fd367cbb3b3dd7495b1ddd664b90&units=metric')
// This line fetches weather data from the OpenWeatherMap API for the city entered in the input field
.then(response => response.json())
.then(data => {
    //Temperature, city name, wind speed, humidity, weather description is extracted for the response of API
var tempValue = data['main']['temp'];
var nameValue = data['name'];
var humidValue=data['main']['humidity'];
var windValue=data['wind']['speed'];
var descValue = data['weather'][0]['description'];
//Weather data for Bolton city is shown in HTML elements
boltonName.innerHTML = nameValue;
boltonTemp.innerHTML = "Temperature : "+tempValue +"°C";
boltonHumid.innerHTML= "Humidity : "+humidValue +"gm³";
boltonWind.innerHTML="Wind : "+windValue +"m/s";
boltonDesc.innerHTML = "Description : "+descValue;
input.value ="";// Input field is cleared after displaying the weather data

})
.catch(err => console.log(err));//Log errors in console after catching errors

