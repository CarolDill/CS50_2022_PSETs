const toggle = document.getElementById("toggle");
const theme = window.localStorage.getItem("theme");

//verify if the theme  in localStorage is dark, if yes, apply it to the body
if (theme === "dark") document.body.classList.add("dark");

// event listener for when the button is clicked
toggle.addEventListener("click", () => {
  document.body.classList.toggle("dark");
  if (theme === "dark") {
    window.localStorage.setItem("theme", "light");
  } else window.localStorage.setItem("theme", "dark");
});
