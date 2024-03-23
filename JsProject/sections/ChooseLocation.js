const bucharest = document.querySelector(".dropdown-menu .bucharest");
const timisoara = document.querySelector(".dropdown-menu .timisoara");
const oradea = document.querySelector(".dropdown-menu .oradea");

function updateCurrentCity(city) {
  const currentCityElem = document.querySelector(".current-city");
  currentCityElem.innerHTML = city;
}

function updateWeather(city) {
    localStorage.setItem('city', city);
  displayCurrentWeather(city);
  updateCurrentCity(city);
  displayWeatherForecast(city);
}

bucharest.addEventListener("click", function () {
  updateWeather("București");
});
timisoara.addEventListener("click", function () {
  updateWeather("Timișoara");
});
oradea.addEventListener("click", function () {
  updateWeather("Oradea");
});
