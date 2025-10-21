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


    document.getElementById("submitb").onclick = function (e) {
        const inputs = document.querySelectorAll("#signupmenu input");
        const emaillog = inputs[0].value.trim();
        const password = inputs[1].value.trim();
        const confirmpassword = inputs[2].value.trim();

        if (!emaillog || !password || !confirmpassword) {
            alert("Fill in all fields");
        } else if (password !== confirmpassword) {
            alert("Passwords do not match.");
        }
        else if (!emaillog.endsWith("@gmail.com") || !emaillog.includes("@")) {
            alert("Email must be a valid Gmail address (e.g. abc@gmail.com).");
        }
        else {
            const name = getemail(emaillog);
            goTodo(name);
            alert("Account created successfully!!");
            inputs[0].value = "";
            inputs[1].value = "";
            inputs[2].value = "";
        }
    };
    function getemail(em)
     {
        return em.split('@')[0];
    }

    function goTodo(name) {
    window.location.href = "todo.html?name=" + name;
}