
const API_KEY = "4f4c6690a9b0c995b5f414bf3a434db5";

// Construim link-urile (endpoint-urile) catre care noi o sa facem request-urile cu JS 

function getCurrentWeatherEndpoint(city){
    return `https://api.openweathermap.org/data/2.5/weather?q=${city}&lang=ro&units=metric&appid=${API_KEY}`;
};

// Declaram a doua functie pe care o vom folosi pt a lua API ul ce ne returneaza date despre vremea pe 5 zile

function getForecastWeatherEndpoint(city) {
    return `https://api.openweathermap.org/data/2.5/forecast?q=${city}&unit=metric&lang=ro&appid=${API_KEY}`;
};