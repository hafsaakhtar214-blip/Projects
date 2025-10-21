document.addEventListener("DOMContentLoaded", function () {
    const today = new Date();
    const dateString = today.toDateString();
    document.getElementById("todayDate").textContent = "Today's Date: " + dateString;
    document.querySelector(".btn").addEventListener("click", function () 
    {
        document.body.classList.toggle("dark");
    });
});

function calculateAge() {
    const birthInput = document.getElementById("birthdate").value;
    const result = document.getElementById("result");

    if (!birthInput) {
        result.style.color = "red";
        result.textContent = "Please select your birth date.";
        return;
    }
    
    const birthDate = new Date(birthInput);
    const today = new Date();

    let years = today.getFullYear() - birthDate.getFullYear();
    let months = today.getMonth() - birthDate.getMonth();
    let days = today.getDate() - birthDate.getDate();

    if (birthDate > today) {
        result.style.color = "red";
        result.textContent = "Birth date cannot be in the future!";
        return;
    }
    if (days < 0) 
    {
        months--;
        const prevMonth = new Date(today.getFullYear(), today.getMonth(), 0);
        days += prevMonth.getDate();
    }

    if (months < 0) 
    {
        years--;
        months += 12;
    }

    result.textContent = `You are ${years} years, ${months} months, and ${days} days old.`;
}
