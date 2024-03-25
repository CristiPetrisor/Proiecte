// imi definesc o functie care imi returneaza iconita de la Open Weather pe baza codului primit de la API
function getWeatherIcon (iconCode) {
    return `https://openweathermap.org/img/wn/${iconCode}.png`;
}

// primim viteza vantului in m/s si noi vrem sa ii convertim in km/h
function windToKmPerHour(meterPerSec) {
    return (meterPerSec * 3600) / 1000;
  }