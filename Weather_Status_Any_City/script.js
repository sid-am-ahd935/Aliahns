let weatherInfo = [];

function showWeather() {

    let cityName = document.getElementById("cityName").value;
    let APIkey = `https://api.openweathermap.org/data/2.5/weather?q=${cityName}&units=metric&APPID=6b91d536d89d7feed22418f9101f1b8b`
    fetch(APIkey, { method: 'GET' })
        .then(Response => Response.json())
        .then(data => {
            weatherInfo = data;
            if (weatherInfo.name == undefined) {
                alert(`This city is not found :(`)
            }
            else {
                weather(weatherInfo)
            }


        })
        .catch("Server has some problem")
}
function weather(weatherInfo) {

    // City Name
    let city = document.getElementById('city')
    city.innerHTML = `Weather in ${weatherInfo.name}`;

    // Temparature
    let cityTemp = document.getElementById('cityTemp')
    cityTemp.innerHTML = `${weatherInfo.main.temp}°C`;

    //Description
    const cityWeatherDescpValue1 = weatherInfo.weather[0].description;
    const cityWeatherDescpValue2 = cityWeatherDescpValue1.charAt(0).toUpperCase() + cityWeatherDescpValue1.slice(1);
    let cityWeatherDescp = document.getElementById('cityWeatherDescp')
    cityWeatherDescp.innerHTML = `${cityWeatherDescpValue2}`;

    //Humidity
    let cityHumidity = document.getElementById('cityHumidity')
    cityHumidity.innerHTML = `Humidity: ${weatherInfo.main.humidity}%`;

    //Wind Speed
    let cityWindSpeed = document.getElementById('cityWindSpeed')
    cityWindSpeed.innerHTML = `Wind Speed: ${weatherInfo.wind.speed}km/h`;


}
