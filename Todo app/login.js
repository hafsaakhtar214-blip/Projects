const createRipple = (e) => {
    const button = e.currentTarget;

    const ripple = document.createElement("span");
    ripple.classList.add("ripple");

    const rect = button.getBoundingClientRect();
    const size = Math.max(rect.width, rect.height);
    ripple.style.width = ripple.style.height = size + "px";

    const x = e.clientX - rect.left - size / 2;
    const y = e.clientY - rect.top - size / 2;
    ripple.style.left = `${x}px`;
    ripple.style.top = `${y}px`;

    button.appendChild(ripple);

    ripple.addEventListener("animationend", () => {
        ripple.remove();
    });
};


    document.getElementById("enterb").onclick = function (e) {
        const inputs = document.querySelectorAll("#signmenu input");
        const emaillog = inputs[0].value.trim();
        const password = inputs[1].value.trim();

        if (!emaillog || !password) {
            alert("Fill in all fields");
        }
        if (!emaillog.endsWith("@gmail.com") || !emaillog.includes("@")) {
            alert("Email must be a valid Gmail address (e.g. abc@gmail.com).");
        }
        else {
            const name = getemail(emaillog);
            goTodo(name);
            document.getElementById("signmenu").style.display = "none";
            alert("You got successfully login!");
            inputs[0].value = "";
            inputs[1].value = "";
        }
    };
   function goTodo(name) {
    window.location.href = "todo.html?name=" + name;
}

    function getemail(em)
     {
        return em.split('@')[0];
    }