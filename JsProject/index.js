let currentCityFromLs = localStorage.getItem("city");
// actualizam orasul afisat pe ecran daca avem cheia city in localStorage
const currentCityTag = document.querySelector(".current-city");
// Afisam vremea curenta folosind o functie din alt fisier
if (currentCityFromLs) {
  currentCityTag.innerHTML = currentCityFromLs;
}

if (!currentCityFromLs) {
  localStorage.setItem("city", "Bucharest");
}
// Afisam vremea curenta folosind o functie din alt fisier
displayCurrentWeather(currentCityFromLs);

// Afisam vremea pe urmatoarele 5 zile
displayWeatherForecast (currentCityFromLs);