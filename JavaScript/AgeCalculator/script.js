let btn = document.getElementById("btn");
let inputDate = document.getElementById("inputDate");
let result = document.getElementById("result");

inputDate.max = new Date().toISOString().split("T")[0];

btn.addEventListener("click", () => {
  let today = new Date();
  let birthDate = new Date(inputDate.value);

  //calculate year
  let years;
  if (
    today.getMonth() > birthDate.getMonth() ||
    (today.getMonth() == birthDate.getMonth() &&
      today.getDate() >= birthDate.getDate())
  ) {
    years = today.getFullYear() - birthDate.getFullYear();
  } else {
    years = today.getFullYear() - birthDate.getFullYear() - 1;
  }

  //calculate months
  let months;
  if (today.getDate() >= birthDate.getDate()) {
    months = today.getMonth() - birthDate.getMonth();
  } else if (today.getDate() < birthDate.getDate()) {
    months = today.getMonth() - birthDate.getMonth() - 1;
  }
  // make month positive
  months = months < 0 ? months + 12 : months;

  // Calculate days
  let days;
  // days of months in a year
  let monthDays = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
  if (today.getDate() >= birthDate.getDate()) {
    days = today.getDate() - birthDate.getDate();
  } else {
    days =
      today.getDate() - birthDate.getDate() + monthDays[birthDate.getMonth()];
  }

  // Display result
  result.innerHTML = `<p> <span>Born on :</span>  ${birthDate.toDateString()}.</p>`;
  result.innerHTML += `<p><span>Age : </span> ${years} years, ${months} months and ${days} days</p>`;
  if (months == 0 && days == 0) {
    result.innerHTML += `<p>Happy Birthday!🎂🎈🎈</p>`;
  }
});
