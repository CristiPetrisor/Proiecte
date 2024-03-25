const scrollToTopButton = document.querySelector("#scroll-to-top");

scrollToTopButton.addEventListener("click", function () {
    window.scrollTo({
      top: 0,
      behavior: "smooth",
    });
  });

document.addEventListener("scroll", function () {
  const halfViewportHeight = window.innerHeight / 2;
  if (window.scrollY > halfViewportHeight) {
    scrollToTopButton.style.visibility = "visible";
  } else {
    scrollToTopButton.style.visibility = "hidden";
  }
});

