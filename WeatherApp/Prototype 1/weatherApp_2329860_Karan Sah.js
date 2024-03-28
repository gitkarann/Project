
// Script for getting weather data for a user-input city
var input = document.querySelector('.input_text');
var main = document.querySelector('#name');
var temp = document.querySelector('.temp');
var wind = document.querySelector('.wind');
var humid = document.querySelector('.humid');
var desc = document.querySelector('.desc');
var clouds = document.querySelector('.clouds');
var button= document.querySelector('.submit');

button.addEventListener('click', function(name){
fetch('https://api.openweathermap.org/data/2.5/weather?q='+input.value+'&appid=9251fd367cbb3b3dd7495b1ddd664b90&units=metric')
.then(response => response.json())
.then(data => {
var tempValue = data['main']['temp'];
var nameValue = data['name'];
var humidValue=data['main']['humidity'];
var windValue=data['wind']['speed'];
var descValue = data['weather'][0]['description'];

main.innerHTML = nameValue;
temp.innerHTML = "Temperature : "+tempValue +"°C";
humid.innerHTML= "Humidity : "+humidValue +"gm³";
wind.innerHTML="Wind : "+windValue +"m/s";
desc.innerHTML = "Description : "+descValue;
input.value ="";

})
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
.then(response => response.json())
.then(data => {
var tempValue = data['main']['temp'];
var nameValue = data['name'];
var humidValue=data['main']['humidity'];
var windValue=data['wind']['speed'];
var descValue = data['weather'][0]['description'];

boltonName.innerHTML = nameValue;
boltonTemp.innerHTML = "Temperature : "+tempValue +"°C";
boltonHumid.innerHTML= "Humidity : "+humidValue +"gm³";
boltonWind.innerHTML="Wind : "+windValue +"m/s";
boltonDesc.innerHTML = "Description : "+descValue;
input.value ="";

})
.catch(err => console.log(err));

