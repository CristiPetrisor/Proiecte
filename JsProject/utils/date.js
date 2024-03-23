// Aici vom avea logica pt a ne extrage intr-un mod citibil data primita de la API (proprietatea dt de la OpenWeather)

function getDayOfTheWeek(utc) {
    // Pt ca data de la API este in UTC foramat trebuie sa o transform folosind obiectul Date din JS
    const date = new Date(utc * 1000);
    const dayIndex = date.getDay();
    switch (dayIndex) {
        case 0:
          day = "Duminică";
          break;
        case 1:
          day = "Luni";
          break;
        case 2:
          day = "Marți";
          break;
        case 3:
          day = "Miercuri";
          break;
        case 4:
          day = "Joi";
          break;
        case 5:
          day = "Vineri";
          break;
        case 6:
          day = "Sâmbătă";
          break;
        default:
          // Aruncam o eroare daca index-ul nu este valid (nu ar trebui sa se ajunga vreodata aici).
          throw new Error("Indexul trebuie sa fie intre 0 si 6.");
      }
    return day;
}

function getHour(dateInUtc) {
    const date = new Date(dateInUtc * 1000);
    // extragem ora folosind metoda getHours() a obiectului Date
    // daca ora este mai mica decat 10 o sa ii adaugam noi un 0 in fata
    let hours = date.getHours();
    if(hours < 10) {
        hours = `0${hours}`;
    }
    // extragem minutele folosind o metoda de pe obiectul Date 
    let minutes = date.getMinutes();
    if(minutes < 10) {
        minutes =   `0${minutes}`;
    }
    // returnam ora
    return `${hours}:${minutes}`;
}
