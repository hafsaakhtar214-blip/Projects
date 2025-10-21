document.getElementById("m").onclick = function ()
{
    const menu = document.querySelector(".menu");
    if (menu.style.display === "none" || menu.style.display === "") {
        menu.style.display = "flex";
    } else {
        menu.style.display = "none";
    }
};

function hideAll() 
{
    document.getElementById("d").style.display = "none";
    document.getElementById("r").style.display = "none";
    document.getElementById("p").style.display = "none";
    document.getElementById("s").style.display = "none";
}

document.getElementById("dashboard").onclick = function () 
{
    hideAll();
    document.getElementById("d").style.display = "block";
};

document.getElementById("report").onclick = function () {
    hideAll();
    document.getElementById("r").style.display = "block";
};

document.getElementById("profile").onclick = function () {
    hideAll();
    document.getElementById("p").style.display = "block";
};

document.getElementById("setting").onclick = function () {
    hideAll();
    document.getElementById("s").style.display = "block";
};
document.getElementById("logout").onclick = function()
{
    alert("You have been successfully Log out!!");
};

document.getElementById("signin").onclick = function () {
    const signBox = document.querySelector(".sign");
    const container = document.querySelector(".signcenter");
    signBox.style.display = "flex";
    container.style.display = "flex";
};

document.getElementById("signin").onclick = function ()
 {
    const signBox = document.querySelector(".sign");
    const signContainer = document.querySelector(".signcenter");
    const emailInput = document.querySelector(".sign input[type='text']");
    const passwordInput = document.querySelector(".sign input[type='password']");

    if (signBox.style.display === "none" || signBox.style.display === "")
     {
        signBox.style.display = "flex";
        signContainer.style.display = "flex";
        emailInput.value = "";
        passwordInput.value = "";
    } 
    else
    {
        signBox.style.display = "none";
        signContainer.style.display = "none";
    }
};

document.querySelector(".enterbtn").onclick = function ()
 {
    const email = document.querySelector(".sign input[type='text']").value.trim();
    const password = document.querySelector(".sign input[type='password']").value.trim();

    if (email === "" || password === "") 
    {
        alert("Incorrect: Please fill in both fields.");
    } 
    else 
     {
        alert("Successfully Entered!");
        document.querySelector(".sign").style.display = "none";
        document.querySelector(".signcenter").style.display = "none";
    }
};
